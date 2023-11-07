//
//  main.cpp
//  LongArithmetics
//
//  Created by Nastya Bekesheva on 26.09.2023.
//

#include <iostream>
#include <vector>
#include <chrono>

#include "BigInt.hpp"
#include "BigInt.cpp"

void test(BigInt &a, BigInt &b)
{

    auto start = std::chrono::high_resolution_clock::now();

    auto addition_start = std::chrono::high_resolution_clock::now();
    BigInt addition_result = a + b;
    auto addition_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> addition_duration = addition_end - addition_start;
    std::cout << "Addition Result: " << addition_result << std::endl;
    std::cout << "Addition Execution Time: " << addition_duration.count() << " seconds" << std::endl;

    auto subtraction_start = std::chrono::high_resolution_clock::now();
    BigInt subtraction_result = a - b;
    auto subtraction_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> subtraction_duration = subtraction_end - subtraction_start;
    std::cout << "Subtraction Result: " << subtraction_result << std::endl;
    std::cout << "Subtraction Execution Time: " << subtraction_duration.count() << " seconds" << std::endl;

    auto multiplication_start = std::chrono::high_resolution_clock::now();
    BigInt multiplication_result = a * b;
    auto multiplication_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> multiplication_duration = multiplication_end - multiplication_start;
    std::cout << "Multiplication Result: " << multiplication_result << std::endl;
    std::cout << "Multiplication Execution Time: " << multiplication_duration.count() << " seconds" << std::endl;
    
    auto division_start = std::chrono::high_resolution_clock::now();
    BigInt division_result = a / b;
    auto division_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> division_duration = division_end - division_start;
    std::cout << "Division Result: " << division_result << std::endl;
    std::cout << "Division Execution Time: " << division_duration.count() << " seconds" << std::endl;
    
    std::string s = "2";
    BigInt c(s);
    auto power_start = std::chrono::high_resolution_clock::now();
    BigInt power_result = a.pow(c);
    auto power_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> power_duration = power_end - power_start;
    std::cout << "Square Result: " << power_result << std::endl;
    std::cout << "Square Execution Time: " << power_duration.count() << " seconds" << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Total Execution Time for All Operations: " << duration.count() << " seconds" << std::endl;
}


int main(int argc, const char * argv[]) {
    std::string s = "ffffffffffffffff";
    BigInt a(s);
    s = "7fffffffffffffff";
    BigInt b(s);
    s = "2";
    BigInt c(s);
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << a << std::endl;
    std::cout << "a+b = " << a + b << std::endl;
    std::cout << "a-b = " << a - b << std::endl;
    std::cout << "a*b = " << a * b << std::endl;
    std::cout << "a/b = " << a / b << std::endl;
    std::cout << "a%b = " << a % b << std::endl;
    std::cout << "a^2 = " << a.pow(c) << std::endl;
    test(a, b);
    return 0;
}
