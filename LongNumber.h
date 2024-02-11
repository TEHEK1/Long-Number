#pragma once
#include <vector>
#include <string>
#define BASEEXP 9
#define BASE 1000000000

class LongNumber;
LongNumber operator"" _L(long double);

class LongNumber
{
private:
    friend LongNumber operator"" _L(long double);
    std::vector<int> _data;
    long long _accuracy;
    bool _is_negative;
    LongNumber();
    LongNumber(const LongNumber &) = default;
    int getOffset(const std::vector<int> &, const size_t, const size_t) const;
    static constexpr int pow10[] = {1, 10, 100, 1000, 10000, 1000000, 10000000, 10000000, 100000000, 1000000000};

public:
    LongNumber operator-() const;
    LongNumber operator+(const LongNumber &) const;
    LongNumber operator-(const LongNumber &) const;
    LongNumber operator*(const LongNumber &) const;
    LongNumber operator/(const LongNumber &) const;
    bool operator==(const LongNumber &) const;
    bool operator!=(const LongNumber &) const;
    bool operator<(const LongNumber &) const;
    bool operator>(const LongNumber &) const;
    operator std::string();
    LongNumber abs(const LongNumber &) const;
};