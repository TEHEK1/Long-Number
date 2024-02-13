#include "LongNumber.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
int get(const std::vector<int> &vec, size_t ind)
{
    return 0 <= ind && ind < vec.size() ? vec[ind] : 0;
}
int LongNumber::getOffset(const std::vector<int> &vec, const size_t ind, const size_t offset) const
{
    return (static_cast<long long>(get(vec, ind + (offset / BASEEXP))) * pow10[offset % BASEEXP]) % BASE +
           static_cast<long long>(get(vec, ind + (offset / BASEEXP)) - 1) / pow10[BASEEXP - offset % BASEEXP];
}
const LongNumber &LongNumber::operator+=(const LongNumber &rhs)
{
    _data.resize(std::max(_data.size(), rhs._data.size()));
    bool overflow = 0;
    if (_is_negative == rhs._is_negative)
    {
        for (size_t i = 0; i < _data.size(); i++)
        {
            long long result = get(_data, i) + get(rhs._data, i) + static_cast<int>(overflow);
            _data[i] = (result) % BASE;
            overflow = result >= BASE;
        }
    }
    else
    {
        char sign = 1;
        if (abs(*this) < abs(rhs))
        {
            sign = -1;
            _is_negative = rhs._is_negative;
        }
        for (size_t i = 0; i < _data.size(); i++)
        {
            long long result = (get(_data, i) * sign - get(rhs._data, i)) * sign - static_cast<int>(overflow);
            _data[i] = (result + BASE) % BASE;
            overflow = result < 0;
        }
    }
    if (overflow)
    {
        _data.push_back(1);
    }
    while (_data.size() > 1 && _data.back() == 0)
    {
        _data.pop_back();
    }
    return *this;
}
const LongNumber &LongNumber::operator-=(const LongNumber &rhs)
{
    return *this += (-rhs);
}
const LongNumber &LongNumber::operator*=(const LongNumber &rhs)
{
    LongNumber copy = LongNumber(*this);
    _data = std::vector<int>(_data.size() + rhs._data.size(), 0);
    _is_negative = _is_negative ^ rhs._is_negative;
    for (size_t i = 0; i < copy._data.size(); i++)
    {
        for (size_t j = 0, overflow = 0; j < rhs._data.size() || overflow; ++j)
        {
            long long result = _data[i + j] + static_cast<long long>(copy._data[i]) * rhs._data[j] + overflow;
            _data[i + j] = int(result % BASE);
            overflow = int(result / BASE);
        }
    }
    long long diffaccuracy = _accuracy;
    _data.erase(_data.begin(), _data.begin() + _accuracy / BASEEXP);
    for (long long i = 0; i < _data.size(); i++)
    {
        _data[i] = _data[i] / pow10[_accuracy % BASEEXP] +
                   (get(_data, i + 1) % pow10[_accuracy % BASEEXP]) * pow10[BASEEXP - _accuracy % BASEEXP];
    }
    while (_data.size() > 1 && _data.back() == 0)
    {
        _data.pop_back();
    }
    return *this;
}
const LongNumber &LongNumber::operator/=(const LongNumber &rhs)
{
    if(rhs == 0.0_L){
        throw std::runtime_error("Can't divide by zero");
    }
    bool is_negative =_is_negative;
    _is_negative = 0;
    LongNumber l, r, mid, eps;
    r._data = _data;
    l._data = std::vector<int>(1, 0);
    eps._data = std::vector<int>(1, 1);
    while (l + eps < r)
    {
        mid = (l + r);
        bool overflow = false;
        for (long long i = mid._data.size() - 1; i >= 0; i--)
        {
            bool overflowCopy = overflow;
            overflow = mid._data[i] % 2 == 1;
            mid._data[i] = mid._data[i] / 2 + static_cast<int>(overflowCopy) * pow10[BASEEXP] / 2;
        }
        LongNumber multResult = mid * rhs;
        /*multResult._data.resize(mid._data.size() + rhs._data.size(), 0);
        for (size_t i = 0; i < mid._data.size(); i++)
        {
            for (size_t j = 0, overflow = 0; j < rhs._data.size() || overflow; ++j)
            {
                long long result = multResult._data[i + j] + mid._data[i] * rhs._data[j] + overflow;
                multResult._data[i + j] = int(result % BASE);
                overflow = int(result / BASE);
            }
        }*/
        if (multResult <= *this)
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    _data = l._data;
    is_negative = is_negative;
    return *this;
}
bool operator<(const LongNumber &l, const LongNumber &r)
{
    int lsign = l._is_negative ? -1 : 1;
    int rsign = r._is_negative ? -1 : 1;
    for (long long i = std::max(l._data.size(), r._data.size()) - 1; i >= 0; i--)
    {
        if (get(l._data, i) * lsign != get(r._data, i) * rsign)
        {
            return get(l._data, i) * lsign < get(r._data, i) * rsign;
        }
    }
    return false;
}
bool operator==(const LongNumber &l, const LongNumber &r)
{
    int lsign = l._is_negative ? -1 : 1;
    int rsign = r._is_negative ? -1 : 1;
    for (long long i = std::max(l._data.size(), r._data.size()) - 1; i >= 0; i--)
    {
        if (get(l._data, i) * lsign != get(r._data, i) * rsign)
        {
            return false;
        }
    }
    return true;
}
const LongNumber LongNumber::abs(const LongNumber &number) const
{
    return number._is_negative ? -number : number;
}
LongNumber::operator std::string()
{
    std::stringstream ss;
    for (long long i = _data.size() - 1; i >= 0 || ss.str().size() <= DEFAULT_ACCURACY; i--)
    {
        ss << std::setw(BASEEXP) << std::setfill('0') << get(_data, i);
    }
    std::string result = ss.str();

    result.insert(result.begin() + result.size() - DEFAULT_ACCURACY, '.');
    long long nullsToRemove = 0;
    for (long long i = 0; i + 1 < result.size() && result[i + 1] != '.' && result[i] == '0'; i++)
    {
        nullsToRemove = i + 1;
    }
    result.erase(result.begin(), result.begin() + nullsToRemove);
    return result;
}
const LongNumber operator""_L(const long double number)
{
    std::ostringstream sstream;
    sstream << std::fixed << std::setprecision(DEFAULT_ACCURACY) << number;
    std::string numberstr = sstream.str();
    numberstr.erase(std::remove(numberstr.begin(), numberstr.end(), '.'), numberstr.end());
    LongNumber result = LongNumber();
    result._accuracy = DEFAULT_ACCURACY;
    for (long long i = numberstr.size(); i >= 0; i -= BASEEXP)
    {
        result._data.push_back(stoll(numberstr.substr(std::max(0ll, i - BASEEXP), std::min(BASEEXP, i))));
    }
    return result;
}