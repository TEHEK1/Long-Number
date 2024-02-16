#include "LongNumber.h"
#include <iostream>
#include <chrono>
#include <ctime>
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
int main(int argc, char* argv[]) {
    int accuracy = 100;
    if(argc >=2){
        accuracy = std::stoi(argv[1]);
    }
    const std::clock_t c_start = std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();
    std::cout<<std::string(countPi(accuracy)).substr(0,accuracy + 2);
    const std::clock_t c_end = std::clock();
    const auto t_end = std::chrono::high_resolution_clock::now();

    std::cout << "\nCPU time used: "
              << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << "ms\n"
              << "Wall clock time passed: " << std::chrono::duration<double, std::milli>(t_end - t_start).count() << "ms" << '\n';
}