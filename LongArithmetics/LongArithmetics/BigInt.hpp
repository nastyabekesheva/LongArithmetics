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
    BigInt& operator=(const BigInt &other) = default;
    BigInt& operator=(std::string &num_in_hex); 
    
    friend std::ostream & operator << (std::ostream &out, const BigInt &BI);
    
    BigInt operator+(BigInt &other);
    BigInt operator-(BigInt &other);
    BigInt operator*(BigInt &other);
    BigInt operator/(BigInt &other);
    BigInt operator%(BigInt &other);
    
    BigInt pow(BigInt &other);
    
    BigInt operator<<(std::size_t i);
    BigInt operator>>(std::size_t i);
    std::pair<BigInt, BigInt> LongDivMod(const BigInt& B) const;
    
    bool operator>(BigInt &other) const;
    bool operator>=(BigInt &other) const;
    bool operator<(BigInt &other) const;
    bool operator<=(BigInt &other) const;
    bool operator==(BigInt &other) const;
    bool operator!=(BigInt &other) const;
    bool operator!=(int other) const;
    
    BigInt addmod(BigInt &other, BigInt &m);
    BigInt submod(BigInt &other, BigInt &m);
    BigInt mulmod(BigInt &other, BigInt &m);
    BigInt sqmod(BigInt &m);
    BigInt GCD(BigInt &other);
    BigInt LCM(BigInt &other);
    BigInt BarrettReduction(BigInt &n, BigInt &mu);
    BigInt KillLastDigits(std::size_t i) const;
    BigInt LongModPowerBarrett(BigInt &b, BigInt &n);
    
    void swap(BigInt &other);
    
    void displayhex();
    std::vector<uint32_t> num();
    std::vector<uint> to_binary() const;
    bool is_even();
    BigInt shift(std::size_t i);
    BigInt min(BigInt &other) const;
    


private:
    int comp(BigInt &other) const;
    BigInt LongMulOneDigit(std::size_t other);
    //void LongShiftDigitsToHigh(std::size_t i);
    //BigInt karatsuba(BigInt &other);
    std::size_t BitLenght() const;

    void split(std::size_t pos, BigInt &high, BigInt &low);
    void remove_zeros();
    
};

#endif /* BigInt_hpp */
