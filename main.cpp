#include "LongNumber.h"
#include <iostream>
#include <algorithm>

int main(int argc, char *argv[]) {
    LongNumber f = LongNumber("1.0");
    int accuracy = 100;
    LongNumber pow16 = LongNumber("1.0");
    LongNumber ln4 = LongNumber("4.0");
    LongNumber ln2 = LongNumber("2.0");
    LongNumber ln16 = LongNumber("16.0");
    LongNumber ln1 = LongNumber("1.0");
    LongNumber result = LongNumber("0.0");
    if (argc >= 2) {
        accuracy = std::stoi(argv[1]);
    }
    for (long long i = 0; i < 100; i++) {
        LongNumber res1 = ln4/ LongNumber(8 * i + 1);
        LongNumber res2 = ln2/ LongNumber(8 * i + 4);
        LongNumber res3 = ln1/ LongNumber(8 * i + 5);
        LongNumber res4 = ln1/ LongNumber(8 * i + 6);
        LongNumber current = pow16 * ( res1 - res2 - res3 - res4);
        result += current;
        pow16/=ln16;
    }
    std::cout << std::string(result);
}