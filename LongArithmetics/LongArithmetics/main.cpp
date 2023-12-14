//
//  main.cpp
//  LongArithmetics
//
//  Created by Nastya Bekesheva on 26.09.2023.
//

#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>

#include "BigInt.hpp"
#include "BigInt.cpp"


// Assuming BigInt is defined somewhere in your code.

void test(BigInt &a, BigInt &b) {
    std::vector<double> addition_times, subtraction_times, multiplication_times, division_times, power_times, total_times;

    for (int i = 0; i < 10; ++i)
    {
        auto start = std::chrono::high_resolution_clock::now();

        // Addition
        auto addition_start = std::chrono::high_resolution_clock::now();
        BigInt addition_result = a + b;
        auto addition_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> addition_duration = addition_end - addition_start;
        addition_times.push_back(addition_duration.count());
        std::cout << "Addition Result: " << addition_result << std::endl;
        std::cout << "Addition Execution Time: " << addition_duration.count() << " seconds" << std::endl;

        // Subtraction
        auto subtraction_start = std::chrono::high_resolution_clock::now();
        BigInt subtraction_result = a - b;
        auto subtraction_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> subtraction_duration = subtraction_end - subtraction_start;
        subtraction_times.push_back(subtraction_duration.count());
        std::cout << "Subtraction Result: " << subtraction_result << std::endl;
        std::cout << "Subtraction Execution Time: " << subtraction_duration.count() << " seconds" << std::endl;

        // Multiplication
        auto multiplication_start = std::chrono::high_resolution_clock::now();
        BigInt multiplication_result = a * b;
        auto multiplication_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> multiplication_duration = multiplication_end - multiplication_start;
        multiplication_times.push_back(multiplication_duration.count());
        std::cout << "Multiplication Result: " << multiplication_result << std::endl;
        std::cout << "Multiplication Execution Time: " << multiplication_duration.count() << " seconds" << std::endl;

        // Division
        auto division_start = std::chrono::high_resolution_clock::now();
        BigInt division_result = a / b;
        auto division_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> division_duration = division_end - division_start;
        division_times.push_back(division_duration.count());
        std::cout << "Division Result: " << division_result << std::endl;
        std::cout << "Division Execution Time: " << division_duration.count() << " seconds" << std::endl;

        // Power
        std::string s = "2";
        BigInt c(s);
        auto power_start = std::chrono::high_resolution_clock::now();
        BigInt power_result = a.pow(c);
        auto power_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> power_duration = power_end - power_start;
        power_times.push_back(power_duration.count());
        std::cout << "Square Result: " << power_result << std::endl;
        std::cout << "Square Execution Time: " << power_duration.count() << " seconds" << std::endl;

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        total_times.push_back(duration.count());
        std::cout << "Total Execution Time for All Operations: " << duration.count() << " seconds" << std::endl;
    }
    
    auto min_addition_time = *std::min_element(addition_times.begin(), addition_times.end());
    auto max_addition_time = *std::max_element(addition_times.begin(), addition_times.end());
    auto avg_addition_time = std::accumulate(addition_times.begin(), addition_times.end(), 0.0) / addition_times.size();

    auto min_subtraction_time = *std::min_element(subtraction_times.begin(), subtraction_times.end());
    auto max_subtraction_time = *std::max_element(subtraction_times.begin(), subtraction_times.end());
    auto avg_subtraction_time = std::accumulate(subtraction_times.begin(), subtraction_times.end(), 0.0) / subtraction_times.size();

    auto min_multiplication_time = *std::min_element(multiplication_times.begin(), multiplication_times.end());
    auto max_multiplication_time = *std::max_element(multiplication_times.begin(), multiplication_times.end());
    auto avg_multiplication_time = std::accumulate(multiplication_times.begin(), multiplication_times.end(), 0.0) / multiplication_times.size();

    auto min_division_time = *std::min_element(division_times.begin(), division_times.end());
    auto max_division_time = *std::max_element(division_times.begin(), division_times.end());
    auto avg_division_time = std::accumulate(division_times.begin(), division_times.end(), 0.0) / division_times.size();

    auto min_power_time = *std::min_element(power_times.begin(), power_times.end());
    auto max_power_time = *std::max_element(power_times.begin(), power_times.end());
    auto avg_power_time = std::accumulate(power_times.begin(), power_times.end(), 0.0) / power_times.size();

    // Output results for each operation
    std::cout << "Addition - Min: " << min_addition_time * 1000 << "ms Max: " << max_addition_time * 1000 << "ms Avg: " << avg_addition_time * 1000 << "ms" << std::endl;
    std::cout << "Subtraction - Min: " << min_subtraction_time * 1000 << "ms Max: " << max_subtraction_time * 1000 << "ms Avg: " << avg_subtraction_time * 1000 << "ms" << std::endl;
    std::cout << "Multiplication - Min: " << min_multiplication_time * 1000 << "ms Max: " << max_multiplication_time * 1000 << "ms Avg: " << avg_multiplication_time * 1000 << "ms" << std::endl;
    std::cout << "Division - Min: " << min_division_time * 1000 << "ms Max: " << max_division_time * 1000 << "ms Avg: " << avg_division_time * 1000 << "ms" << std::endl;
    std::cout << "Power - Min: " << min_power_time * 1000 << "ms Max: " << max_power_time * 1000 << "ms Avg: " << avg_power_time * 1000 << "ms" << std::endl;

    // Output results for other operations...
}


int main(int argc, const char * argv[]) {
    std::string s = "cbe75e23d145c3dc78d76739b63d337cc33268e08ce4ea7319c38b7d057b1747d59010759f3b015858dc5a9d05ddbbd3ef41a368ba1ca6d8a6d967f2fed6b7033e7f56d46beae7c259cce870e0879f49849c956b6b6810be90d0c50c54daaef41b2b1c6e3c7b2ed35da549a7c95fd551841ea90e4196e8272b42ea3dba7cdcef";
    /*BigInt a(s);
    s = "d0a166bef0f8cd687a755ce64c4736e2621fe749af3c4170354c55a2728037612cf3b134550036e2de888e049ee782ab82ab99ba3442a3b4b8eb21c9f79778cff4ce0c2109a02fd18163e5155146d156b92176c03ba2b87ee53ba78217529616eea6e8432b0f736b09e30e89f3ceeaea11fb94dacd994e1fd8a6059cc14a58b2";
    BigInt b(s);*/
    s = "10";
    //s="10000000000000000";
    //s = "68A94B93FC4C9F33E5A180F02B7C6C9200C2B74AC8E3B780579E1B5082BDBA399C62B8B71ECB100835F46872EFABA3373";
    //s="12211221";
    BigInt a(s);
    s = "23454236";
    //s="4352525";
    //s = "D41FADD65BC8DDC4224FF788548934FE64C997EB7C0098D55C8196995BBAE8D4F30EE5AF27F0915B17D41ECE74A55B5F";
    //s = "2";
    BigInt b(s);
    s = "4352525";
    //s = "D41FADD65BC8DDC4224FF788548934FE64C997EB7C0098D55C8196995BBAE8D4F30EE5AF27F0915B17D41ECE74A55B5F";
    //s = "2";
    BigInt m(s);
    //std::cout << "a-b = " << a - b << std::endl;
    //std::cout << "t = " << b / a << std::endl;
    //std::cout << "a / b = " << a / b << std::endl;
    std::cout << "Barret(t, c) = " << b.LongModPowerBarrett(a, m) << std::endl;
    //std::vector<uint> bin = t.to_binary();
    /*"       5B6750B696901157A37C8177A633D9421A761DCC1123ADF301D601E6ED020BAC4D31CA5C1C4C06F284772685F8614D814"
    "2192B465B6750B696901157A37C8177A633D9421A761DCC1123ADF301D601E6ED020BAC4D31CA5C1C4C06F284772685F8614D814"*/
    
    
    //test(a, b);
    return 0;
}


