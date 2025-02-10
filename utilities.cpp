#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include "utilities.h"

bool isPrime(long n) {
    // prime-checking
    if (n < 2) return false;
    for (long i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

std::string getTimeStamp() {
    auto now = std::chrono::system_clock::now();

    // Break it into a time_t (seconds) plus a remainder in milliseconds
    auto millis      = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000; 
    std::time_t tt   = std::chrono::system_clock::to_time_t(now);
    std::tm localTm  = *std::localtime(&tt);

    // YYYY-MM-DD HH:MM:SS.mmm
    std::ostringstream oss;
    oss << std::put_time(&localTm, "%Y-%m-%d %H:%M:%S") << '.' << std::setw(3) << std::setfill('0') << millis.count();
    return oss.str();
}

