#include <iostream>
#include <thread>
#include <mutex>        
#include <atomic>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>      // for std::setw
#include "variant4.h"
#include "../utilities.h"

// Shared atomic counter
static std::atomic<long> currentNum(1);
static long globalLimit;
static std::mutex coutMutex;  // prints a full line at a time

void workerVariant4(long threadIndex, std::vector<long>& localPrimes) {
    while (true) {
        long num = currentNum.fetch_add(1);
        if (num > globalLimit) {
            break;
        }
        if (isPrime(num)) {
            localPrimes.push_back(num);
        }
    }

    {    // Once current thread has no more numbers to process, print that it is complete
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Thread " << threadIndex << " complete.\n";
    }
}

void runVariant4(long numThreads, long limit) {
    // capture start 
    auto startTime = std::chrono::high_resolution_clock::now();
    std::time_t startTimeT = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "\n=== Variant 2 (Wait & Print + Linear Distribution) ===\n";
    std::cout << "Search started at: " << getTimeStamp() << "\n";

    globalLimit = limit;
    currentNum.store(1);

    // thread collects its own primes
    std::vector<std::vector<long>> allThreadPrimes(numThreads);

    // create + launch threads
    std::vector<std::thread> threads;
    threads.reserve(numThreads);
    for (long i = 0; i < numThreads; ++i) {
        threads.emplace_back(workerVariant4, i, std::ref(allThreadPrimes[i]));
    }

    // join all threads
    for (auto &t : threads) {
        t.join();
    }

    // combine all primes into a vector (using no sort)
    std::vector<long> combined;
    for (auto &vec : allThreadPrimes) {
        combined.insert(combined.end(), vec.begin(), vec.end());
    }

    // print found primes in table, currently set 8 per row
    const int PRIMES_PER_ROW = 8;
    const int COLUMN_WIDTH   = 6;  
    int count = 0;

    std::cout << "\n=================== All Primes Found ===================\n";
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
    auto endTime   = std::chrono::high_resolution_clock::now();
    std::time_t endTimeT = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "\nSearch completed at: " << getTimeStamp() << "\n";
    std::cout << "Elapsed time: " << elapsedMs << " ms\n\n";
}
