#include "LongNumber.h"
#include <algorithm>
LongNumber operator"" _L(long double from)
{
}
int get(const std::vector<int> &vec, size_t ind)
{
    return 0 <= ind && ind < vec.size() ? vec[ind] : 0;
}
int LongNumber::getOffset(const std::vector<int> &vec, const size_t ind, const size_t offset) const
{
    return (static_cast<long long>(get(vec, ind + (offset / BASEEXP))) * pow10[offset % BASEEXP]) % BASE +
           static_cast<long long>(get(vec, ind + (offset / BASEEXP)) - 1) / pow10[BASEEXP - offset % BASEEXP];
}
const LongNumber LongNumber::operator-() const
{
    LongNumber result = LongNumber(*this);
    result._is_negative = !result._is_negative;
    return result;
}
const LongNumber LongNumber::operator+(const LongNumber &number) const
{
    LongNumber result;
    result._accuracy = std::max(this->_accuracy, number._accuracy);
    result._data.resize(std::max(this->_data.size() + (result._accuracy - this->_accuracy) / BASEEXP, number._data.size() + (result._accuracy - number._accuracy) / BASEEXP) + 1);
    bool overflow = 0;
    if (number._is_negative == this->_is_negative)
    {
        result._is_negative = number._is_negative;
        for (size_t i = 0; i < result._data.size(); i++)
        {
            result._data[i] = (getOffset(this->_data, i, result._accuracy - this->_accuracy) + getOffset(this->_data, i, result._accuracy - number._accuracy) + static_cast<int>(overflow)) % BASE;
            overflow = getOffset(this->_data, i, result._accuracy - this->_accuracy) + getOffset(this->_data, i, result._accuracy - number._accuracy) + static_cast<int>(overflow) >= BASE;
        }
        if (overflow)
        {
            result._data.push_back(1);
        }
    }
    else
    {
        const LongNumber *bigger, *less;
        if (abs(*this) > abs(number))
        {
            bigger = this;
            less = &number;
        }
        else
        {
            bigger = &number;
            less = this;
        }
        result._is_negative = bigger->_is_negative;
        for (size_t i = 0; i < result._data.size(); i++)
        {
            result._data[i] = (getOffset(this->_data, i, result._accuracy - this->_accuracy) - getOffset(this->_data, i, result._accuracy - number._accuracy) - static_cast<int>(overflow) + BASE) % BASE;
            overflow = getOffset(this->_data, i, result._accuracy - this->_accuracy) - getOffset(this->_data, i, result._accuracy - number._accuracy) - static_cast<int>(overflow) < 0;
        }
        if (overflow)
        {
            throw "IDK"; // FIXME:Musn't happen
        }
    }
    while (result._data.size() > 1 && result._data.back() == 0)
    {
        result._data.pop_back();
    }
    return result;
}
const LongNumber LongNumber::operator-(const LongNumber &number) const
{
    return *this + (-number);
}

const LongNumber LongNumber::abs(const LongNumber &number) const
{
    LongNumber result = LongNumber(number);
    return result < 0.0_L ? -result : result;
}