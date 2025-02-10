#include <iostream>
#include <thread>
#include <mutex>        
#include <atomic>
#include <vector>
#include <chrono>
#include <ctime>
#include "variant2.h"
#include "../utilities.h"

static std::mutex coutMutex; // prints a full line at a time
static std::atomic<long> currentNum2(1);
static long globalLimit2;

//  each thread fetches the next integer via atomic, checks prime, prints immediately
static void workerVariant2(long threadIndex) {
    while (true) {
        long num = currentNum2.fetch_add(1);
        if (num > globalLimit2) {
            break; 
        }
        if (isPrime(num)) {
            std::lock_guard<std::mutex> lock(coutMutex);    // Acquire lock so one thread prints a full line at a time
            // print with timestamp + thread ID + prime found
            std::cout << getTimeStamp() << " | Thread ID: " << threadIndex << " | Found Prime: " << num << "\n";
        }
    }
}

void runVariant2(long numThreads, long limit) {
    // capture start 
    auto startTime = std::chrono::high_resolution_clock::now();
    std::cout << "\n=== Variant 2 (Immediate Print + Linear Distribution) ===\n";
    std::cout << "Search started at: " << getTimeStamp() << "\n\n";

    globalLimit2 = limit;
    currentNum2.store(1);

    // create + launch threads
    std::vector<std::thread> threads;
    threads.reserve(numThreads);
    for (long i = 0; i < numThreads; ++i) {
        threads.emplace_back(workerVariant2, i);
    }

    // join threads
    for (auto &t : threads) {
        t.join();
    }

    // capture end time  & print final info
    auto endTime   = std::chrono::high_resolution_clock::now();
    auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "\nSearch completed at: " << getTimeStamp() << "\n";
    std::cout << "Elapsed time: " << elapsedMs << " milliseconds\n\n";
}
