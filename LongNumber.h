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
    static constexpr int pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    LongNumber() : _is_negative(false), _accuracy(DEFAULT_ACCURACY){};
    LongNumber(long double);
public:
    LongNumber(const LongNumber &) = default;
    friend LongNumber operator-(LongNumber lhs)
    {
        lhs._is_negative = !lhs._is_negative;
        return lhs;
    }
    LongNumber &operator+=(const LongNumber &);
    LongNumber &operator-=(const LongNumber &);
    LongNumber &operator*=(const LongNumber &);
    LongNumber &operator/=(const LongNumber &);
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
    friend LongNumber operator"" _L(long double);
    explicit operator std::string() const;
    static LongNumber abs(const LongNumber &) ;
};
inline bool operator>(const LongNumber &lhs, const LongNumber &rhs) { return rhs < lhs; }
inline bool operator<=(const LongNumber &lhs, const LongNumber &rhs) { return !(lhs > rhs); }
inline bool operator>=(const LongNumber &lhs, const LongNumber &rhs) { return !(lhs < rhs); }
inline bool operator!=(const LongNumber &lhs, const LongNumber &rhs) { return !(lhs == rhs); }
LongNumber operator""_L(long double);