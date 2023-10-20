//
//  BigInt.cpp
//  LongArithmetics
//
//  Created by Nastya Bekesheva on 26.09.2023.
//

#include "BigInt.hpp"

#define SYSTEM_SIZE 32
#define HEX_ALPH "0123456789ABCDEF"

std::vector<uint32_t> str_to_hex(std::string &str)
{
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    unsigned long size = str.length();
    std::vector<uint32_t> hex;
    
    for (size_t i = 0; i < size; ++i)
    {
        hex.push_back(std::string(HEX_ALPH).find(str[i]));
    }
    
    return hex;
}


std::vector<uint32_t> hex_to_uint32(std::string &num_in_hex)
{
    //reverse(num_in_hex.begin(), num_in_hex.end());
    std::vector<uint32_t> num;
    std::size_t size_hex = num_in_hex.length();

    
    std::vector<uint32_t> hex = str_to_hex(num_in_hex);
    std::size_t i = 0;
    std::size_t j = size_hex - 1;
    
    
    while (j > 8)
    {
        
        num.push_back(0);
        for (std::size_t k = 0; k < 8; ++k)
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
    

    //std::reverse(num.begin(), num.end());
    
    return num;
}

std::string uint32_to_hex(uint32_t &num)
{
    std::string num_in_hex = "";
    for (int i = 7; i >= 0; --i)
    {
        unsigned int n = (num >> (4 * i)) & 0xF;
        num_in_hex += HEX_ALPH[n];
    }
    

    size_t pos = num_in_hex.find_first_not_of('0');
    if (pos != std::string::npos) {
        return num_in_hex.substr(pos);
    } else {
        return "0"; 
    }
    
    return num_in_hex;
}

std::string vec_uint32_to_hex(std::vector<uint32_t> &num)
{
    std::string hex = "";
    std::reverse(num.begin(), num.end());
    
    for (size_t i = 0; i < num.size(); ++i)
    {
        hex += uint32_to_hex(num[i]);
    }
    
    //reverse(hex.begin(), hex.end());
    
    return hex;
}

void BigInt::displayhex()
{
    std::cout << vec_uint32_to_hex(_num) << std::endl;
}

BigInt::BigInt()
{
    _num = {};
}

BigInt::BigInt(std::string &num_in_hex)
{
    _num = hex_to_uint32(num_in_hex);
    
}

BigInt::BigInt(const BigInt &other)
{
    _num.resize(other._num.size());

    for (std::size_t i = 0; i < _num.size(); ++i)
    {
        _num[i] = other._num[i];
    }
}

BigInt::BigInt(std::vector<uint32_t> num)
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
    std::vector<uint32_t> new_num;
    
    if (_num.size() < other._num.size())
    {
        _num.resize(other._num.size());
    }
    else if (_num.size() > other._num.size())
    {
        other._num.resize(other._num.size());
    }
    
    uint32_t carry = 0;
    uint32_t tmp;
    
    for (std::size_t i = 0; i < _num.size(); ++i)
    {
        tmp = _num[i] + other._num[i] + carry ;
        new_num.push_back((tmp & (uint32_t)((std::pow(2, SYSTEM_SIZE) - 1))));
        carry = (_num[i] > (std::pow(2, SYSTEM_SIZE) - 1) - other._num[i]);
    }
    if (carry > 0)
        new_num.push_back(1);
    
    BigInt res(new_num);
    
    return res;

}

BigInt BigInt::operator-(BigInt &other)
{
    std::vector<uint32_t> new_num;
    
    if (_num.size() < other._num.size())
    {
        _num.resize(other._num.size());
    }
    else if (_num.size() > other._num.size())
    {
        other._num.resize(other._num.size());
    }

    
    uint64_t borrow = 0;
    int32_t tmp;
    for (std::size_t i = 0; i < _num.size(); ++i)
    {
        tmp = _num[i] - other._num[i] - borrow;
        if (tmp >= 0)
        {
            new_num.push_back(tmp);
            borrow = 0;
        }
        else
        {
            int64_t buf = std::pow(2, SYSTEM_SIZE) + tmp;
            new_num.push_back(buf);
            borrow = 1;
        }
    }
    BigInt res(new_num);
    return res;
}

BigInt BigInt::operator*(BigInt &other)
{
    BigInt result, tmp;
    for (std::size_t i = 0; i < _num.size(); ++i)
    {
        tmp = LongMulOneDigit(other._num[i]);
        tmp = tmp << i;
        result = result + tmp;
    }
    return result;
}

BigInt BigInt::operator/(BigInt &other)
{
    BigInt quotient({0}), remainder(*this), result;
    std::size_t k = other.BitLenght();
    
    while (remainder >= other)
    {
        std::size_t t = remainder.BitLenght();
        result = other << (t-k);
        if (t == 1)
            std::cout << "1" << std::endl;
        while (remainder < result)
        {
            --t;
            result = other << (t-k);
        }
        //BigInt h({8318}), l({8316});
        //if (l <= quotient && quotient <= h)
            //std::cout << "2" << std::endl;
        

        remainder = remainder - result;
        BigInt bit({static_cast<uint32_t>(std::pow(2, t - k))});
        quotient = quotient + bit;
    }
    
    std::cout << "q=" << quotient << " r=" << remainder << std::endl;
    
    return result;
}

BigInt BigInt::pow(BigInt &other)
{
    BigInt result({1});
    std::vector<uint> bin_other = other.to_binary();
    for (int i = bin_other.size() - 1; i >= 0; --i)
    {
        if (bin_other[i] == 1)
            result = result * (*this);
        if (i != 0)
        {
            result = result * result;
        }
    }
    
    
    return result;
    
}

BigInt BigInt::operator<<(std::size_t i)
{
    BigInt result(*this);
    for (int j = 0; j < i; ++j)
    {
        result._num.insert(result._num.begin(), 0);
        //result._num.pop_back();
    }
    
    return result;
}

bool BigInt::operator<(BigInt &other) const
{
    return (this->comp(other) == -1);
}

bool BigInt::operator>(BigInt &other) const
{
    return (this->comp(other) == 1);
}

bool BigInt::operator<=(BigInt &other) const
{
    return (this->comp(other) == -1 || this->comp(other) == 0);
}

bool BigInt::operator>=(BigInt &other) const
{
    return (this->comp(other) == 1 || this->comp(other) == 0);
}

bool BigInt::operator==(BigInt &other) const
{
    return (this->comp(other) == 0);
}

bool BigInt::operator!=(BigInt &other) const
{
    return !(this->comp(other) == 0);
}

BigInt BigInt::LongMulOneDigit(std::size_t other)
{
    std::vector<uint32_t> new_num;
    
    uint64_t carry = 0;
    uint64_t tmp;
    
    for (std::size_t i = 0; i < _num.size(); ++i)
    {
        tmp = (uint64_t)_num[i] * (uint64_t)other + carry ;
        new_num.push_back((uint32_t)(tmp & (uint32_t)((std::pow(2, SYSTEM_SIZE) - 1))));
        carry = tmp >> SYSTEM_SIZE;
    }
    if (carry > 0)
        new_num.push_back((uint32_t)carry);
    
    BigInt res(new_num);
    
    return res;
    
}

int BigInt::comp(BigInt &other) const
{
    if (_num.size() > other._num.size())
    {
        /*for(std::size_t i = _num.size(); i >= _num.size() - other._num.size() - 1; --i)
        {
            if (_num[i] > 0)
                return 1;
        }*/
        return 1;
    }
    else if (_num.size() < other._num.size())
    {
        /*for(std::size_t i = _num.size(); i >= other._num.size() - _num.size() - 1; --i)
        {
            if (other._num[i] > 0)
                return -1;
        }*/
        return -1;
    }
    
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

std::vector<uint> BigInt::to_binary() const {
     if (_num.empty())
     {
         return std::vector<uint>{0};
     }
     else
     {
         std::vector<uint> bin;
         for (std::size_t i = _num.size(); i > 0; --i) {
             uint32_t num = _num[i - 1];
             while (num > 0)
             {
                 bin.insert(bin.begin(), num % 2);
                 num /= 2;
             }
         }
         reverse(bin.begin(), bin.end());
         return bin;
     }
    
};

/*
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
 */

std::size_t BigInt::BitLenght() const
{
    BigInt tmp({_num[_num.size()-1]});
    std::vector<uint> bin = tmp.to_binary();
    return ((_num.size() - 1) * 32) + bin.size();
}


void BigInt::swap(BigInt &other)
{
    std::swap(*this, other);
}


