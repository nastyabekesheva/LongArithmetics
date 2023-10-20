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
    std::vector<uint32_t> _num;
    
public:
    BigInt();
    BigInt(std::string &num_in_hex);
    BigInt(const BigInt &other);
    BigInt(std::vector<uint32_t> num);
    //~BigInt();
    BigInt& operator=(const BigInt &other);
    BigInt& operator=(std::string &num_in_hex); 
    
    friend std::ostream & operator << (std::ostream &out, const BigInt &BI);
    
    BigInt operator+(BigInt &other);
    BigInt operator-(BigInt &other);
    BigInt operator*(BigInt &other);
    BigInt operator/(BigInt &other);
    
    BigInt pow(BigInt &other);
    
    BigInt operator<<(std::size_t i);
    std::pair<BigInt, BigInt> LongDivMod(const BigInt& B) const;
    
    bool operator>(BigInt &other) const;
    bool operator>=(BigInt &other) const;
    bool operator<(BigInt &other) const;
    bool operator<=(BigInt &other) const;
    bool operator==(BigInt &other) const;
    bool operator!=(BigInt &other) const;
    
    
    void swap(BigInt &other);
    
    void displayhex();

private:
    int comp(BigInt &other) const;
    BigInt LongMulOneDigit(std::size_t other);
    //void LongShiftDigitsToHigh(std::size_t i);
    BigInt karatsuba(BigInt &other);
    std::size_t BitLenght() const;

    void split(std::size_t pos, BigInt &high, BigInt &low);
    std::vector<uint> to_binary() const;
    
};

#endif /* BigInt_hpp */
