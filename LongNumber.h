#pragma once
#include <vector>
#include <string>
#include <list>
#define BASEEXP 9ll
#define BASE 1000000000
#define DEFAULT_ACCURACY 100

class LongNumber
{
private:
    std::vector<int> _data;
    long long _accuracy;
    bool _is_negative;
    int getOffset(const std::vector<int> &, const size_t, const size_t) const;
    static constexpr int pow10[] = {1, 10, 100, 1000, 10000, 1000000, 10000000, 10000000, 100000000, 1000000000};
    LongNumber() : _is_negative(false), _accuracy(DEFAULT_ACCURACY){};

public:
    LongNumber(const LongNumber &) = default;
    friend LongNumber operator-(LongNumber lhs)
    {
        lhs._is_negative = !lhs._is_negative;
        return lhs;
    }
    const LongNumber &operator+=(const LongNumber &);
    const LongNumber &operator-=(const LongNumber &);
    const LongNumber &operator*=(const LongNumber &);
    const LongNumber &operator/=(const LongNumber &);
    friend LongNumber operator+(LongNumber lhs, const LongNumber &rhs)
    {
        lhs += rhs;
        return lhs;
    }
    friend LongNumber operator-(LongNumber lhs, const LongNumber &rhs)
    {
        lhs -= rhs;
        return lhs;
    }
    friend LongNumber operator*(LongNumber lhs, const LongNumber &rhs)
    {
        lhs *= rhs;
        return lhs;
    }
    friend LongNumber operator/(LongNumber lhs, const LongNumber &rhs)
    {
        lhs /= rhs;
        return lhs;
    }
    friend bool operator==(const LongNumber &, const LongNumber &);
    friend bool operator<(const LongNumber &, const LongNumber &);
    friend const LongNumber operator"" _L(const long double);
    operator std::string();
    const LongNumber abs(const LongNumber &) const;
};
inline bool operator>(const LongNumber &lhs, const LongNumber &rhs) { return rhs < lhs; }
inline bool operator<=(const LongNumber &lhs, const LongNumber &rhs) { return !(lhs > rhs); }
inline bool operator>=(const LongNumber &lhs, const LongNumber &rhs) { return !(lhs < rhs); }
inline bool operator!=(const LongNumber &lhs, const LongNumber &rhs) { return !(lhs == rhs); }
const LongNumber operator""_L(const long double);