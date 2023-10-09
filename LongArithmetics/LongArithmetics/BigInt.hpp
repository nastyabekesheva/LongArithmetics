//
//  BigInt.hpp
//  LongArithmetics
//
//  Created by Nastya Bekesheva on 26.09.2023.
//
#pragma once

#ifndef BigInt_hpp
#define BigInt_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class BigInt
{
private:
    std::vector<uint64_t> _num;
    
public:
    BigInt();
    BigInt(std::string &num_in_hex);
    BigInt(const BigInt &other);
    BigInt(std::vector<uint64_t> num);
    //~BigInt();
    BigInt& operator=(const BigInt &other);
    BigInt& operator=(std::string &num_in_hex); // idk if this is necessary
    
    friend std::ostream & operator << (std::ostream &out, const BigInt &BI);
    
    BigInt operator+(BigInt &other);
    BigInt operator-(BigInt &other);
    BigInt operator*(BigInt &other);
    BigInt operator/(BigInt &other);
    
    BigInt operator<<(std::size_t i);
    
    
    bool operator>(BigInt &other);
    bool operator>=(BigInt &other);
    bool operator<(BigInt &other);
    bool operator<=(BigInt &other);
    bool operator==(BigInt &other);
    bool operator!=(BigInt &other);
    
    
    void swap(BigInt &other);
    
private:
    int comp(BigInt &other) const;
    BigInt LongMulOneDigit(std::size_t other);
    void LongShiftDigitsToHigh(std::size_t i);
    BigInt karatsuba(BigInt &other);
    void split(std::size_t pos, BigInt &high, BigInt &low);
};

#endif /* BigInt_hpp */
