STDISCM 
P1 - Threaded Prime Number Search
Kaitlyn P. Tighe S12



Variants
- All four variants rely on the same basic “prime‐checking” routine but differ in 
(A) when they print results (immediate vs. after all threads) and 
(B) how the work is divided among threads (static chunk vs. dynamic “linear” distribution).

    Combinations
        A.1: Print immediately with thread ID & timestamp.
        A.2: Wait until all threads finish, then print everything.
        B.1: Straight division of search range.
        B.2: Linear search with threads handling divisibility testing.

    The four combinations are:
        Variant 1 → (A.1 + B.1)
        Variant 2 → (A.1 + B.2)
        Variant 3 → (A.2 + B.1)
        Variant 4 → (A.2 + B.2)

Project Structure
- Coded with C++ in MacOs. 
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

Input Validations
- Only positive numbers are accepted. No negative numbers or special characters.
    - numThreads >= 1
    - limit >= 2
    - variant between 1 and 4
- Invalid inputs will result in an error message.


Build/Compilation Instructions
    Type in terminal the following:

        rm -rf *.o primes
        g++ -std=c++11 -pthread -o primes main.cpp \
            variant1/variant1.cpp variant2/variant2.cpp \
            variant3/variant3.cpp variant4/variant4.cpp \
            utilities.cpp
        ./primes

