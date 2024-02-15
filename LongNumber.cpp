#include "LongNumber.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <exception>

int get(const std::vector<int> &vec, unsigned long long ind) {
    return ind < vec.size() ? vec.at(ind) : 0;
}

LongNumber::LongNumber(std::string numberStr) {
    _is_negative = numberStr.at(0) == '-';
    _accuracy = DEFAULT_ACCURACY;
    if (numberStr.at(0) == '-') {
        numberStr.erase(numberStr.begin());
    }
    if (std::find(numberStr.begin(), numberStr.end(), '.') == numberStr.end()) {
        numberStr.push_back('.');
    }
    unsigned long long accuracy = numberStr.size() -
                                  std::distance(numberStr.begin(), std::find(numberStr.begin(), numberStr.end(), '.')) -
                                  1;
    if (accuracy > _accuracy) {
        numberStr.erase(numberStr.size() - (accuracy - _accuracy), accuracy - _accuracy);
    }
    numberStr.erase(std::remove(numberStr.begin(), numberStr.end(), '.'), numberStr.end());
    _data = std::vector<int>((_accuracy - accuracy) / BASEEXP, 0);
    _data.push_back(0);
    for (auto i = static_cast<long long>(numberStr.size()); i > 0; i -= BASEEXP) {
        _data.back() += static_cast<int>((stoll(numberStr.substr(std::max(0ll, i - BASEEXP), std::min(BASEEXP, i))) *
                                          pow10[(_accuracy - accuracy) % BASEEXP]) %
                                         BASE);
        _data.push_back(static_cast<int>(stoll(numberStr.substr(std::max(0ll, i - BASEEXP), std::min(BASEEXP, i))) /
                                         pow10[BASEEXP - (_accuracy - accuracy) % BASEEXP]));
    }
    if (_data.size() * BASEEXP > _accuracy + BASEEXP) {
        _data.pop_back();
    }
}

LongNumber &LongNumber::operator+=(const LongNumber &rhs) {
    _data.resize(std::max(_data.size(), rhs._data.size()));
    bool overflow = false;
    if (_is_negative == rhs._is_negative) {
        for (size_t i = 0; i < _data.size(); i++) {
            long long result = get(_data, i) + get(rhs._data, i) + static_cast<long long>(overflow);
            _data.at(i) = static_cast<int>((result) % BASE);
            overflow = result >= BASE;
        }
    } else {
        char sign = 1;
        if (abs(*this) < abs(rhs)) {
            sign = -1;
            _is_negative = rhs._is_negative;
        }
        for (size_t i = 0; i < _data.size(); i++) {
            long long result = sign * (static_cast<long long>(get(_data, i)) - get(rhs._data, i)) -
                               static_cast<long long>(overflow);
            _data.at(i) = static_cast<int>((result + BASE) % BASE);
            overflow = result < 0;
        }
    }
    if (overflow) {
        _data.push_back(1);
    }
    while (_data.size() > 1 && _data.back() == 0) {
        _data.pop_back();
    }
    return *this;
}

LongNumber &LongNumber::operator-=(const LongNumber &rhs) {
    return *this += (-rhs);
}

LongNumber &LongNumber::operator*=(const LongNumber &rhs) {
    LongNumber copy = LongNumber(*this);
    _data = std::vector<int>(_data.size() + rhs._data.size() + 1, 0);
    _is_negative = _is_negative ^ rhs._is_negative;
    for (size_t i = 0; i < copy._data.size(); i++) {
        for (size_t j = 0, overflow = 0; j < rhs._data.size() || overflow; ++j) {
            unsigned long long result = get(_data, i + j) + static_cast<unsigned long long>(copy._data.at(i)) *
                                                            get(rhs._data, j) + overflow;
            _data.at(i + j) = int(result % BASE);
            overflow = int(result / BASE);
        }
    }
    _data.erase(_data.begin(), _data.begin() + _accuracy / BASEEXP);
    for (long long i = 0; i < _data.size(); i++) {
        _data.at(i) = _data.at(i) / pow10[_accuracy % BASEEXP] +
                      (get(_data, i + 1) % pow10[_accuracy % BASEEXP]) * pow10[BASEEXP - _accuracy % BASEEXP];
    }
    while (_data.size() > 1 && _data.back() == 0) {
        _data.pop_back();
    }
    return *this;
}

LongNumber &LongNumber::operator/=(const LongNumber &rhs) {
    if (rhs == 0.0_L) {
        throw std::runtime_error("Can't divide by zero");
    }
    bool is_negative = _is_negative;
    _is_negative = false;
    LongNumber firstLeftGate = 0.1_L, leftGate = 0.5_L, rightGate = 1.0_L, two = 2.0_L, rCopy(rhs);
    while (rCopy < firstLeftGate) {
        rCopy._data.insert(rCopy._data.begin(), 0);
        _data.insert(_data.begin(), 0);
    }
    {
        LongNumber rightGateMultiplied = rightGate;
        rightGateMultiplied._data.insert(rightGateMultiplied._data.begin(), 0);
        while (rCopy > rightGateMultiplied) {
            rCopy._data.erase(rCopy._data.begin());
            _data.erase(_data.begin());
        }
    }
    while (rCopy > rightGate) {
        rCopy *= firstLeftGate;
        *this *= firstLeftGate;
    }
    while (rCopy < leftGate) {
        rCopy *= two;
        *this *= two;
    }
    LongNumber reverse = LongNumber(48.0 / 17.0) - LongNumber(32.0 / 17.0) * rCopy;
    for (long long i = 1; i < 4 * _accuracy; i *= 2) {
        reverse *= (two - reverse * rCopy);
    }
    _data = (*this * reverse)._data;
    _is_negative = is_negative ^ rhs._is_negative;
    return *this;
}

bool operator<(const LongNumber &l, const LongNumber &r) {
    int lSign = l._is_negative ? -1 : 1;
    int rSign = r._is_negative ? -1 : 1;
    for (long long i = static_cast<long long>(std::max(l._data.size(), r._data.size())) - 1; i >= 0; i--) {
        if (get(l._data, i) * lSign != get(r._data, i) * rSign) {
            return get(l._data, i) * lSign < get(r._data, i) * rSign;
        }
    }
    return false;
}

bool operator==(const LongNumber &l, const LongNumber &r) {
    int lSign = l._is_negative ? -1 : 1;
    int rSign = r._is_negative ? -1 : 1;
    for (long long i = static_cast<long long>(std::max(l._data.size(), r._data.size())) - 1; i >= 0; i--) {
        if (get(l._data, i) * lSign != get(r._data, i) * rSign) {
            return false;
        }
    }
    return true;
}

LongNumber LongNumber::abs(const LongNumber &number) {
    return number._is_negative ? -number : number;
}

LongNumber::operator std::string() const {
    std::stringstream ss;
    for (long long i = static_cast<long long>(_data.size()) - 1; (i + 1) * BASEEXP < _accuracy; i++) {
        ss << std::setw(BASEEXP) << std::setfill('0') << 0;
    }
    for (long long i = static_cast<long long>(_data.size()) - 1; i >= 0; i--) {
        ss << std::setw(BASEEXP) << std::setfill('0') << get(_data, i);
    }
    std::string result = ss.str();
    result.insert(result.begin() + static_cast<long>(result.size()) - DEFAULT_ACCURACY, '.');
    long long nullsToRemove = 0;
    for (long long i = 0; i + 1 < result.size() && result.at(i + 1) != '.' && result.at(i) == '0'; i++) {
        nullsToRemove = i + 1;
    }
    result.erase(result.begin(), result.begin() + nullsToRemove);
    if (_is_negative) { result.insert(result.begin(), '-'); }
    return result;
}

LongNumber operator ""_L(const long double number) {
    return LongNumber(number);
}