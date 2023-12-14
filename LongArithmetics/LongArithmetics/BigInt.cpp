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
    
    
    while (j >= 8)
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

std::string uint32_to_hex(uint32_t &num, bool align)
{
    std::string res = "";
    std::string num_in_hex = "";
    for (int i = 7; i >= 0; --i)
    {
        unsigned int n = (num >> (4 * i)) & 0xF;
        num_in_hex += HEX_ALPH[n];
    }
    

    size_t pos = num_in_hex.find_first_not_of('0');
    if (pos != std::string::npos)
    {
        res = num_in_hex.substr(pos);
    }
    else
    {
        res = "0";
    }
    if (align)
    {
        while (res.size() < 8)
        {
            res = "0" + res;
        }
    }
    
    return res;
}

std::string vec_uint32_to_hex(std::vector<uint32_t> &num)
{
    std::string hex = "";
    std::reverse(num.begin(), num.end());
    
    for (size_t i = 0; i < num.size(); ++i)
    {
        hex += uint32_to_hex(num[i], i != 0);
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

/*BigInt& BigInt::operator=(const BigInt &other)
{
    
    _num.resize(other._num.size());

    
    for (std::size_t i = 0; i < _num.size(); ++i)
    {
        _num[i] = other._num[i];
    }
    
    return *this;
}*/

std::vector<uint32_t> BigInt::num()
{
    return _num;
}

std::ostream & operator << (std::ostream &out, const BigInt &BI)
{
    std::vector<uint32_t> num = BI._num;
    std::cout << vec_uint32_to_hex(num) << std::endl;
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
    res.remove_zeros();
    return res;
}

BigInt BigInt::operator-(BigInt &other)
{
    std::vector<uint32_t> new_num;
    
    if ((*this) < other)
    {
        throw std::runtime_error("((((((;");
    }
    
    if (_num.size() < other._num.size())
    {
        _num.resize(other._num.size(), 0);
    }
    else if (_num.size() > other._num.size())
    {
        other._num.resize(_num.size(), 0);
    }

    
    int64_t borrow = 0;
    int64_t tmp;
    for (std::size_t i = 0; i < _num.size(); ++i)
    {
        int64_t a = _num[i];
        int64_t b = other._num[i];
        tmp = (a - b) - borrow;
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
    other.remove_zeros();
    res.remove_zeros();
    return res;
}

BigInt BigInt::operator*(BigInt &other)
{
    BigInt result, tmp;
    for (std::size_t i = 0; i < _num.size(); ++i)
    {
        tmp = LongMulOneDigit(other._num[i]);
        tmp = tmp.shift(i);
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

        if (remainder < result)
        {
            --t;
            result = other << (t-k);
        }

        remainder = remainder - result;
        //std::cout << remainder << std::endl;
        BigInt bit({(1)});
        bit = bit << (t - k);
        quotient = quotient + bit;
    }
    
    
    return quotient;
}

BigInt BigInt::operator%(BigInt &other)
{
    BigInt quotient({0}), remainder(*this), result;
    std::size_t k = other.BitLenght();
    
    while (remainder >= other)
    {
        std::size_t t = remainder.BitLenght();
        result = other.shift(t-k);

        while (remainder < result)
        {
            --t;
            result = other.shift(t-k);
        }
        

        remainder = remainder - result;
        BigInt bit({static_cast<uint32_t>(std::pow(2, t - k))});
        quotient = quotient + bit;
    }
    //BigInt c({remainder._num[remainder._num.size()-1]});
    return remainder;
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

BigInt BigInt::shift(std::size_t i)
{
    BigInt result(*this);
    for (int j = 0; j < i; ++j)
    {
        result._num.insert(result._num.begin(), 0);
        //result._num.pop_back();
    }
    return result;
}

BigInt BigInt::operator<<(std::size_t i)
{
    
    std::size_t i_1 = i / SYSTEM_SIZE;
    std::size_t i_2 = i % SYSTEM_SIZE;
    BigInt a(*this);
    a = a.shift(i_1);
    BigInt result(a);
    result._num[0] = (a._num[0] << i_2) & 0xFFFFFFFF;
    
    for (int j = 1; j <= a._num.size() - 1; ++j)
    {
        result._num[j] = (a._num[j] << i_2) | (((a._num[j-1] >> (SYSTEM_SIZE - i_2)) & ((1 << i_2) - 1)) & 0xFFFFFFFF);
    }
    //result._num[1] = (_num[1] << i) ^ ((_num[0] >> (SYSTEM_SIZE - i)) & i );
    result._num.push_back((a._num[a._num.size() - 1] >> (SYSTEM_SIZE - i_2)) & (1 << i_2) - 1);
    
    result.remove_zeros();
    
    return result;
}

BigInt BigInt::operator>>(std::size_t i)
{
    BigInt result(*this);
    //std::size_t i_1 = i / SYSTEM_SIZE;
    std::size_t i_2 = i % SYSTEM_SIZE;
    
    if (_num.size() == 1)
    {
        result._num[_num.size() - 1] = (_num[_num.size() - 1] >> i_2);
        return result;
    }
    
    for (std::size_t j = 0; j < _num.size() - 2; ++j)
    {
        result._num[j] = (_num[j] >> i_2) | ((_num[j+1] & ((1 << i_2) - 1)) << ((SYSTEM_SIZE) - i_2));
    }
    result._num[_num.size() - 1] = (_num[_num.size() - 1] >> i_2);
    
    result.remove_zeros();
    
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

bool BigInt::operator!=(int other) const
{
    if (_num.size() > 1)
        return true;
    if (_num.size() == 0)
        return false;
    else
        return _num[0] != other;
}

BigInt BigInt::LongMulOneDigit(std::size_t other)
{
    std::vector<uint32_t> new_num;
    
    uint64_t carry = 0;
    uint64_t tmp;
    
    for (std::size_t i = 0; i < _num.size(); ++i)
    {
        tmp = ((uint64_t)_num[i] * (uint64_t)other) + carry ;
        //new_num.push_back((uint32_t)(tmp & (uint32_t)((std::pow(2, SYSTEM_SIZE) - 1))));
        new_num.push_back((uint32_t)(tmp & 0xFFFFFFFF));
        carry = tmp >> SYSTEM_SIZE;
    }
    if (carry > 0)
        new_num.push_back((uint32_t)carry);
    
    BigInt res(new_num);
    res.remove_zeros();
    return res;
    
}

int BigInt::comp(BigInt &other) const
{
    if (_num.size() > other._num.size())
    {
        return 1;
    }
    else if (_num.size() < other._num.size())
    {

        return -1;
    }
    
    int i;
    for(i = _num.size() - 1; i >= 0; i--)
    {
        if ((_num[i] != other._num[i]))
            break;
    }
    
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

BigInt BigInt::GCD(BigInt &other)
{
    BigInt d({1});
    BigInt zero({0});
    BigInt a(*this);
    BigInt b(other);
    BigInt tmp({0});
    if (b > a)
    {
        std::swap(a, b);
    }

    
    while (a.is_even() && b.is_even())
    {
        a = a >> 1;
        b = b >> 1;
        d = d << 1;
    }
    
    
    while (a.is_even())
    {
        
        a = a >> 1;
    }
    
    
    while (b != zero)
    {
        while (b.is_even())
        {
            b = b >> 1;
            //std::cout << 2 << std::endl;
        }
        BigInt ac(a);
        BigInt bc(b);
        a = ac.min(bc);
        if (ac > bc)
        {
            b = ac - bc;
        }
        else
            b = bc - ac;
        
    }
    d = d * a;
    
    return d;
}


BigInt BigInt::BarrettReduction(BigInt &n, BigInt &mu)
{
    BigInt q = this->KillLastDigits(n._num.size() - 1);
    q = q * mu;
    q = q.KillLastDigits(n._num.size() + 1);
    BigInt tmp = q * n;
    BigInt r = (*this) - tmp;
    while (r >= n)
    {
        //std::cout << r << std::endl;
        r = r - n;
        
    }
    
    
    return r;
}

BigInt BigInt::LongModPowerBarrett(BigInt &b, BigInt &n)
{
    BigInt C({1});
    BigInt A(*this);
    std::size_t tmp = 2*n._num.size();
    BigInt mu = (BigInt({1}).shift(tmp)) / n;
    std::vector<uint> B = b.to_binary();
    
    
    for (std::size_t i = 0; i < B.size(); ++i)
    {
        if (B[i] == 1)
        {
            BigInt tmp = C * A;
            C = tmp.BarrettReduction(n, mu);
        }
        BigInt tmp = A * A;
        A = tmp.BarrettReduction(n, mu);
            
    }
    
    return C;
    
}

BigInt BigInt::KillLastDigits(std::size_t i)
{
    if (_num.size() < i)
    {
        return (*this);
    }
    for (std::size_t j = 0; j < i; ++j)
    {
        _num.erase(_num.begin());
    }
    if (_num.size() == 0)
        _num.push_back(0);
    
    return (*this);
}

bool BigInt::is_even()
{
    if (_num.size() == 1 && _num[0] == 0)
        return false;
    else
        return (_num[0] % 2 == 0);
}

BigInt BigInt::min(BigInt &other) const
{
    if (*this > other)
        return other;
    else
        return *this;
}

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

void BigInt::remove_zeros()
{
    int64_t j = _num.size()-1;
    if (j <= 0)
        return;
    
    while (_num[j] == 0 && j > 0)
    {
        _num.pop_back();
        j--;
    }
}
