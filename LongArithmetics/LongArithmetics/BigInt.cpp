//
//  BigInt.cpp
//  LongArithmetics
//
//  Created by Nastya Bekesheva on 26.09.2023.
//

#include "BigInt.hpp"

#define SYSTEM_SIZE 64
#define HEX_ALPH "0123456789ABCDEF"

std::vector<uint64_t> str_to_hex(std::string &str)
{
    unsigned long size = str.length();
    std::vector<uint64_t> hex;
    
    for (size_t i = 0; i < size; ++i)
    {
        hex.push_back(std::string(HEX_ALPH).find(str[i]));
    }
    
    return hex;
}


std::vector<uint64_t> hex_to_uint64(std::string &num_in_hex)
{
    reverse(num_in_hex.begin(), num_in_hex.end());
    std::vector<uint64_t> num;
    std::size_t size_hex = num_in_hex.length();

    
    std::vector<uint64_t> hex = str_to_hex(num_in_hex);
    std::size_t i = 0;
    std::size_t j = size_hex - 1;
    
    
    while (j > 16)
    {
        
        num.push_back(0);
        for (std::size_t k = 0; k < 16; ++k)
        {

            num[i] |= (hex[j] << (4 * k));
            --j;
        }
        ++i;
    }
    
    
    std::size_t k = 0;
    num.push_back(0);
    while (j >= 0 && j < std::numeric_limits<size_t>::max())
    {
        num[i] |= (hex[j] << (4 * k));
        --j;
        ++k;
    }
    

    
    
    return num;
}

BigInt::BigInt()
{
    _num = {};
}

BigInt::BigInt(std::string &num_in_hex)
{
    _num = hex_to_uint64(num_in_hex);
    
}

BigInt::BigInt(const BigInt &other)
{
    _num.resize(other._num.size());

    for (std::size_t i = 0; i < _num.size(); ++i)
    {
        _num[i] = other._num[i];
    }
}

BigInt::BigInt(std::vector<uint64_t> num)
{
    _num.resize(num.size());
    for (std::size_t i = 0; i < _num.size(); ++i)
    {
        _num[i] = num[i];
    }
}

BigInt& BigInt::operator=(const BigInt &other)
{
    
    _num.resize(other._num.size());

    
    for (std::size_t i = 0; i < _num.size(); ++i)
    {
        _num[i] = other._num[i];
    }
    
    return *this;
}

std::ostream & operator << (std::ostream &out, const BigInt &BI)
{
    for (std::size_t i = 0; i < BI._num.size(); ++i)
    {
        std::cout << "num[" << i << "] = " << BI._num[i] << std::endl;
    }
    
    return out;
}


BigInt BigInt::operator+(BigInt &other)
{
    std::vector<uint64_t> new_num;
    
    if (_num.size() < other._num.size())
    {
        _num.resize(other._num.size());
    }
    else if (_num.size() > other._num.size())
    {
        other._num.resize(other._num.size());
    }
    
    uint64_t carry = 0;
    uint64_t tmp;
    
    for (std::size_t i = 0; i < _num.size(); ++i)
    {
        tmp = _num[i] + other._num[i] + carry ;
        new_num.push_back((tmp & (uint64_t)((pow(2, SYSTEM_SIZE) - 1))));
        carry = (_num[i] > (pow(2, SYSTEM_SIZE) - 1) - other._num[i]);
    }
    if (carry > 0)
        new_num.push_back(1);
    
    BigInt res(new_num);
    
    return res;

}

BigInt BigInt::operator-(BigInt &other)
{
    std::vector<uint64_t> new_num;
    
    if (_num.size() < other._num.size())
    {
        _num.resize(other._num.size());
    }
    else if (_num.size() > other._num.size())
    {
        other._num.resize(other._num.size());
    }
    
    //uint64_t borrow = 0;
    uint64_t tmp;
    for (std::size_t i = 0; i < _num.size(); ++i)
    {
        tmp = _num[i] - other._num[i];
        new_num.push_back(tmp);
        //borrow = 0;
    }
    BigInt res(new_num);
    return res;
}

BigInt BigInt::operator*(BigInt &other)
{
    return karatsuba(other);
}
/*
BigInt BigInt::operator/(BigInt &other)
{
    BigInt Q({0}), R(*this);
    std::size_t k = other._num.size();
    
}*/

BigInt BigInt::operator<<(std::size_t i)
{
    BigInt result(*this);
    for (int j = 0; j < i; ++j)
    {
        result._num.insert(_num.begin(), 0);
        result._num.pop_back();
    }
    
    return result;
}

bool BigInt::operator<(BigInt &other)
{
    return (this->comp(other) == -1);
}

bool BigInt::operator>(BigInt &other)
{
    return (this->comp(other) == 1);
}

bool BigInt::operator<=(BigInt &other)
{
    return (this->comp(other) == -1 || this->comp(other) == 0);
}

bool BigInt::operator>=(BigInt &other)
{
    return (this->comp(other) == 1 || this->comp(other) == 0);
}

bool BigInt::operator==(BigInt &other)
{
    return (this->comp(other) == 0);
}

bool BigInt::operator!=(BigInt &other)
{
    return !(this->comp(other) == 0);
}

BigInt BigInt::LongMulOneDigit(std::size_t other)
{
    std::vector<uint64_t> new_num;
    
    uint64_t carry = 0;
    uint64_t tmp;
    
    for (std::size_t i = 0; i < _num.size(); ++i)
    {
        tmp = _num[i] * other + carry ;
        new_num.push_back((tmp & (uint64_t)((pow(2, SYSTEM_SIZE) - 1))));
        carry = tmp >> (SYSTEM_SIZE / 2);
        carry >>= SYSTEM_SIZE - (SYSTEM_SIZE / 2);
    }
    if (carry > 0)
        new_num.push_back(1);
    
    BigInt res(new_num);
    
    return res;
    
}

int BigInt::comp(BigInt &other) const
{
    if (_num.size() > other._num.size())
        return 1;
    else if (_num.size() < other._num.size())
        return -1;
    
    unsigned long i = _num.size() - 1;
    while (_num[i] == other._num[i])
        --i;
    
    if (i == -1)
        return 0;
    else
    {
        if (_num[i] > other._num[i])
            return 1;
        else
            return -1;
    }
}

void BigInt::LongShiftDigitsToHigh(std::size_t i)
{
    
}

BigInt BigInt::karatsuba(BigInt &other)
{
    if (_num.size() == 1 && other._num.size() == 1 )
    {
        BigInt result;
        uint32_t low, high, low_other, high_other;
        
        low = static_cast<uint32_t>(_num[0] >> 32);
        high = static_cast<uint32_t>(_num[0]);
        low_other = static_cast<uint32_t>(other._num[0] >> 32);
        high_other = static_cast<uint32_t>(other._num[0]);
        
        
    }
    
    if (_num.size() < other._num.size())
    {
        _num.resize(other._num.size());
    }
    else if (_num.size() > other._num.size())
    {
        other._num.resize(other._num.size());
    }
    
    std::size_t m = std::max(_num.size(), other._num.size())/ 2;
    BigInt high, low, high_other, low_other;
    split(m, high, low);
    other.split(m, high_other, low_other);
    
    BigInt z0 = low.karatsuba(low_other);
    BigInt sum = low + high;
    BigInt sum_other = low_other + high_other;
    BigInt z1 = sum.karatsuba(sum_other);
    BigInt z2 = high.karatsuba(high_other);


    BigInt result1 = (z2 << (2 * m)) ;
    BigInt result2 = ((z1 - z2 - z0) << m) + z0;
    BigInt result = result1+result2;
    return result;
}

void BigInt::split(std::size_t pos, BigInt &high, BigInt &low)
{
    high._num.clear();
    low._num.clear();
    
    if (pos < _num.size())
    {
        high._num.assign(_num.begin() + pos, _num.end());
        low._num.assign(_num.begin(), _num.begin() + pos);
    }
    else
    {
        low = *this;
        high._num.resize(pos);
    }
}

void BigInt::swap(BigInt &other)
{
    std::swap(*this, other);
}


