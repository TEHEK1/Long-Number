#include "LongNumber.h"
#include <iostream>
#include <algorithm>
LongNumber countPi(int accuracy){
    LongNumber pow16 = 1._LN;
    LongNumber ln4 = 4._LN;
    LongNumber ln2 = 2._LN;
    LongNumber ln16 = 16._LN;
    LongNumber ln1 = 1._LN;
    LongNumber result = 0._LN;
    for (int i = 0; i < accuracy; i++) {
        LongNumber res1 = ln4/ LongNumber(8 * i + 1);
        LongNumber res2 = ln2/ LongNumber(8 * i + 4);
        LongNumber res3 = ln1/ LongNumber(8 * i + 5);
        LongNumber res4 = ln1/ LongNumber(8 * i + 6);
        result += pow16 * ( res1 - res2 - res3 - res4);
        pow16/=ln16;
    }
    return  result;
}
int main() {
    std::cout << std::string(countPi(100));
}