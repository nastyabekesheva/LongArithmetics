//
//  main.cpp
//  LongArithmetics
//
//  Created by Nastya Bekesheva on 26.09.2023.
//

#include <iostream>

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <cstdlib>

#include "BigInt.hpp"
#include "BigInt.cpp"
#define SYSTEM_SIZE 64
#define HEX_ALPH "0123456789ABCDEF"
#define HEX_MAX_SIZE 16

//110919427519970072630961530469
//95073794954398275251332343397



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    std::string s = "CCCCCCCCCCCCCCCCCCCC";
    std::vector<uint32_t> m = {43690};
    BigInt a(s);
    s = "BBBBBBBBBBBBBBBBBBBB";
    BigInt b(s);
    BigInt c = a*b;
    std:: cout << a << std::endl << b << std::endl << c << std::endl;
    
    return 0;
}
