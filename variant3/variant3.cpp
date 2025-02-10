#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>     
#include <ctime>      // for std::time_t, std::ctime
#include <iomanip>    // for std::setw
#include "variant3.h"
#include "../utilities.h"

static std::mutex coutMutex;  // prints a full line at a time

// Worker function: each thread collects its primes in localPrimes
static void workerVariant3(long threadIndex, long start, long end, std::vector<long>& localPrimes) {
    for (long num = start; num <= end; ++num) {
        if (isPrime(num)) {
            localPrimes.push_back(num);
        }
    }
    {   // Once current thread has no more numbers to process, print that it is complete
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Thread " << threadIndex << " complete.\n";
    }
}

void runVariant3(long numThreads, long limit) {
    // capture start 
    std::cout << "\n=== Variant 3 (Straight Division + Wait & Print) ===\n";
    auto startTime = std::chrono::high_resolution_clock::now();
    std::cout << "Search started at: " << getTimeStamp() << "\n\n";

    // thread collects its own primes
    std::vector<std::vector<long>> allThreadPrimes(numThreads);

    // launch threads with chunk division
    std::vector<std::thread> threads;
    threads.reserve(numThreads);

    long chunkSize = limit / numThreads;
    long startVal = 1;

    for (long i = 0; i < numThreads; ++i) {
        long endVal = (i == numThreads - 1)
                        ? limit
                        : (startVal + chunkSize - 1);

        threads.emplace_back(workerVariant3, i, startVal, endVal, std::ref(allThreadPrimes[i]));
        startVal = endVal + 1;
    }

    // wait for threads to finish
    for (auto& t : threads) {
        t.join();
    }

    // combine all primes into a vector (using no sort)
    std::vector<long> combined;
    for (auto& vec : allThreadPrimes) {
        combined.insert(combined.end(), vec.begin(), vec.end());
    }

    // print found primes in table, currently set 8 per row
    std::cout << "\n=================== All Primes Found ===================\n";
    const int PRIMES_PER_ROW = 8; 
    const int COLUMN_WIDTH   = 6; 
    int count = 0;

    for (auto prime : combined) {
        std::cout << std::setw(COLUMN_WIDTH) << prime << " ";
        if (++count % PRIMES_PER_ROW == 0) {
            std::cout << "\n";
        }
    }
    if (count % PRIMES_PER_ROW != 0) {
        std::cout << "\n";
    }
    std::cout << "========================================================\n";

    // stop timing & print final info
    auto endTime = std::chrono::high_resolution_clock::now();
    auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "\nSearch completed at: " << getTimeStamp() << "\n";
    std::cout << "Elapsed time: " << elapsedMs << " ms\n\n";
}
