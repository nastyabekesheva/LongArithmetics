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

    // Test addition.
    auto additionStart = std::chrono::high_resolution_clock::now();
    BigInt additionResult = a + b;
    auto additionEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> additionDuration = additionEnd - additionStart;
    std::cout << "Addition Result: " << additionResult << std::endl;
    std::cout << "Addition Execution Time: " << additionDuration.count() << " seconds" << std::endl;

    // Test subtraction.
    auto subtractionStart = std::chrono::high_resolution_clock::now();
    BigInt subtractionResult = a - b;
    auto subtractionEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> subtractionDuration = subtractionEnd - subtractionStart;
    std::cout << "Subtraction Result: " << subtractionResult << std::endl;
    std::cout << "Subtraction Execution Time: " << subtractionDuration.count() << " seconds" << std::endl;

    // Test multiplication.
    auto multiplicationStart = std::chrono::high_resolution_clock::now();
    BigInt multiplicationResult = a * b;
    auto multiplicationEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> multiplicationDuration = multiplicationEnd - multiplicationStart;
    std::cout << "Multiplication Result: " << multiplicationResult << std::endl;
    std::cout << "Multiplication Execution Time: " << multiplicationDuration.count() << " seconds" << std::endl;
    
    // Test power operation.
    auto powerStart = std::chrono::high_resolution_clock::now();
    BigInt powerResult = a.pow(b);  // Square num1, for example.
    auto powerEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> powerDuration = powerEnd - powerStart;
    std::cout << "Power Result: " << powerResult << std::endl;
    std::cout << "Power Execution Time: " << powerDuration.count() << " seconds" << std::endl;

    // Measure the end time for all operations.
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Total Execution Time for All Operations: " << duration.count() << " seconds" << std::endl;
}


int main(int argc, const char * argv[]) {
    std::string s = "10";
    BigInt a(s);

    s = "5";
    BigInt b(s);
    test(a, b);
    
    return 0;
}
