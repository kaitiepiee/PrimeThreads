# Threaded Prime Number Search for STDISCM

## Overview  
This project implements a **multi-threaded prime number search** in C++, using four different **variants** that adjust **when** results are printed and **how** tasks are divided among threads.  

## Variants  
All four variants rely on the same **prime-checking algorithm** but differ in:  
(A) **When results are printed:**  
   - **A.1:** Print immediately (includes thread ID & timestamp).  
   - **A.2:** Wait until all threads finish, then print everything.  

(B) **How tasks are divided among threads:**  
   - **B.1:** Straight division of the search range (each thread gets a fixed range).  
   - **B.2:** Linear search with dynamic task assignment (threads pick numbers dynamically).  

### Variant Combinations:  
| Variant | Print Mode         | Task Division           |
|---------|--------------------|-------------------------|
| **1**   | A.1 (Immediate)    | B.1 (Straight Division) |
| **2**   | A.1 (Immediate)    | B.2 (Linear Search)     |
| **3**   | A.2 (Wait & Print) | B.1 (Straight Division) |
| **4**   | A.2 (Wait & Print) | B.2 (Linear Search)     |

---

## Project Structure  
Coded in C++ and tested on macOS.  
    PrimeThreads/
    │── main.cpp
    │── utilities.h
    │── utilities.cpp
    │── config.txt
    │── readme.txt
    │
    ├── variant1/
    │   ├── variant1.cpp
    │   ├── variant1.h
    │
    ├── variant2/
    │   ├── variant2.cpp
    │   ├── variant2.h
    │
    ├── variant3/
    │   ├── variant3.cpp
    │   ├── variant3.h
    │
    └── variant4/
        ├── variant4.cpp
        ├── variant4.h

---

## Input Validations  
- The program accepts only **positive numbers**.  
- Invalid inputs will result in an error message.  
- Constraints:  
  - `numThreads >= 1`  
  - `limit >= 2`  
  - `variant` must be between `1` and `4`  

---

## Build and Compilation Instructions  
To compile and run the program, use the following terminal commands:  

```
rm -rf *.o primes
g++ -std=c++11 -pthread -o primes main.cpp \
    variant1/variant1.cpp variant2/variant2.cpp \
    variant3/variant3.cpp variant4/variant4.cpp \
    utilities.cpp
./primes
```
