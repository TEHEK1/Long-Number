#pragma once
#include <vector>
#include <string>
#include <list>
#define BASEEXP 9ll
#define DEFAULT_ACCURACY 110

class LongNumber
{
private:
    std::vector<int> _data;
    long long _accuracy;
    bool _is_negative;
    static constexpr long long pow10[] = {1, 10, 100, 1000, 10000,
                                    100000, 1000000, 10000000, 100000000, 1000000000};
    static constexpr long long base = pow10[BASEEXP];
    LongNumber();
public:
    explicit LongNumber(std::string);
    explicit LongNumber(double);
    friend LongNumber operator""_LN(const char *);
    explicit operator std::string() const;
    explicit operator double() const;
    static LongNumber abs(const LongNumber &);
    LongNumber &operator+=(const LongNumber &);
    LongNumber &operator-=(const LongNumber &);
    LongNumber &operator*=(const LongNumber &);
    LongNumber &operator/=(const LongNumber &);
    friend LongNumber operator-(LongNumber lhs);
    friend LongNumber operator+(LongNumber, const LongNumber &);
    friend LongNumber operator-(LongNumber, const LongNumber &);
    friend LongNumber operator*(LongNumber, const LongNumber &);
    friend LongNumber operator/(LongNumber, const LongNumber &);
    friend bool operator==(const LongNumber &, const LongNumber &);
    friend bool operator<(const LongNumber &, const LongNumber &);
};
inline bool operator>(const LongNumber &lhs, const LongNumber &rhs) {return rhs < lhs;}
inline bool operator<=(const LongNumber &lhs, const LongNumber &rhs) {return !(lhs > rhs);}
inline bool operator>=(const LongNumber &lhs, const LongNumber &rhs) {return !(lhs < rhs);}
inline bool operator!=(const LongNumber &lhs, const LongNumber &rhs) {return !(lhs == rhs);}
LongNumber operator""_LN(const char *);