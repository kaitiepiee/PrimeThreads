#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <ctime>
#include <mutex>        
#include "variant1.h"
#include "../utilities.h"

static std::mutex coutMutex;  // prints a full line at a time

static void workerVariant1(long threadIndex, long start, long end) {
    for (long num = start; num <= end; ++num) {
        if (isPrime(num)) {
            std::lock_guard<std::mutex> lock(coutMutex); // Protect this block with a lock

            // print immediately timestampt, thread id, prime number found
            std::cout << "" << getTimeStamp() << " | "<< "Thread ID: " << threadIndex << " | Found Prime: " << num<< std::endl;
        }
    }
}

void runVariant1(long numThreads, long limit) {
    // capture start 
    auto startTime = std::chrono::high_resolution_clock::now();
    std::time_t startTimeT = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "\n=== Variant 2 (Wait & Print + Linear Distribution) ===\n";
    std::cout << "Search started at: " << getTimeStamp() << "\n";


    std::vector<std::thread> threads;
    threads.reserve(numThreads);

    // simple chunk division
    long chunkSize = limit / numThreads;
    long start = 1;
    for (long i = 0; i < numThreads; ++i) {
        long end = (i == numThreads - 1) ? limit : (start + chunkSize - 1);
        threads.emplace_back(workerVariant1, i, start, end);
        start = end + 1;
    }

    // join all threads
    for (auto& t : threads) {
        t.join();
    }

    // capture end time  & print final info
    auto endTime = std::chrono::high_resolution_clock::now();
    std::time_t endTimeT = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "\nSearch completed at: " << getTimeStamp() << "\n";
    std::cout << "Elapsed time: " << elapsedMs << " milliseconds\n\n";
}
