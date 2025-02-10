#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
#include <fstream>
#include "variant1/variant1.h"
#include "variant2/variant2.h"
#include "variant3/variant3.h"
#include "variant4/variant4.h"
#include "utilities.h"


std::mutex print_mutex;
int num_threads;
int limit;
int variant;

// Function to check if a number is prime
bool is_prime(int n) {
    if (n < 2) return false; // anything less than 2 is not a prime

    // check all divisors from 2 up to squareroot of n
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false; // if 'n' is divisible by 'i', then 'n' is not prime
    }
    return true; // if no divisors in loop, 'n' is prime
}

// Function to start threads based on selected variant
void start_threads() {
    std::vector<std::thread> threads;
    int range = limit / num_threads;

    for (int i = 0; i < num_threads; ++i) {
        int start = i * range + 1;
        int end = (i == num_threads - 1) ? limit : (i + 1) * range;
    }

    // wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }
}

int main() {
    long numThreads;
    long limit;
    int variant; // variant 1/2/3/4

    // open config.txt for inputs
    std::ifstream config("config.txt"); // read
    if (!config) {
        std::cerr << "Could not open config.txt. Please check config.txt for valid inputs.\n";
        return 1;
    }

    // attempt to read 3 inputs (threads, limit, variant)
    if (!(config >> numThreads >> limit >> variant)) {
        std::cerr << "Error parsing config.txt. Please check the file for valid inputs.\n";
        return 1;
    }

    // validation checking for inputs
    if (numThreads < 1 || limit < 2 || variant < 1 || variant > 4) {
        std::cerr << "Invalid values in config.txt. Please ensure:\n"
                     " - numThreads >= 1\n"
                     " - limit >= 2\n"
                     " - variant between 1 and 4\n"
                     "Then try again.\n";
        return 1;
    }

    // if program reaches here, input is valid
    // prints input read from config.txt
    std::cout << "Using config:\n" 
            << "numThreads = " << numThreads  << " limit = " << limit << " variant = " << variant << "\n";

    // take variant input to run specific variant
    switch (variant) {
        case 1: runVariant1(numThreads, limit); break;
        case 2: runVariant2(numThreads, limit); break;
        case 3: runVariant3(numThreads, limit); break;
        case 4: runVariant4(numThreads, limit); break;
        default: return 1;
    }
    return 0;
}