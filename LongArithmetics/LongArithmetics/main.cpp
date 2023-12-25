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

void test2(BigInt &a, BigInt &b, BigInt &m) {
    std::vector<double> addition_times, subtraction_times, multiplication_times, square_times, gcd_times, lcm_times, barret_times, total_times;

    for (int i = 0; i < 10; ++i)
    {
        auto start = std::chrono::high_resolution_clock::now();

        // Addition
        auto addition_start = std::chrono::high_resolution_clock::now();
        BigInt addition_result = a.addmod(b, m);
        auto addition_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> addition_duration = addition_end - addition_start;
        addition_times.push_back(addition_duration.count());
        std::cout << "Addition Result: " << addition_result << std::endl;
        std::cout << "Addition Execution Time: " << addition_duration.count() << " seconds" << std::endl;

        // Subtraction
        auto subtraction_start = std::chrono::high_resolution_clock::now();
        BigInt subtraction_result = a.submod(b, m);
        auto subtraction_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> subtraction_duration = subtraction_end - subtraction_start;
        subtraction_times.push_back(subtraction_duration.count());
        std::cout << "Subtraction Result: " << subtraction_result << std::endl;
        std::cout << "Subtraction Execution Time: " << subtraction_duration.count() << " seconds" << std::endl;

        // Multiplication
        auto multiplication_start = std::chrono::high_resolution_clock::now();
        BigInt multiplication_result = a.mulmod(b, m);
        auto multiplication_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> multiplication_duration = multiplication_end - multiplication_start;
        multiplication_times.push_back(multiplication_duration.count());
        std::cout << "Multiplication Result: " << multiplication_result << std::endl;
        std::cout << "Multiplication Execution Time: " << multiplication_duration.count() << " seconds" << std::endl;

        // SQuare
        auto square_start = std::chrono::high_resolution_clock::now();
        BigInt square_result = a.sqmod(m);
        auto square_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> square_duration = square_end - square_start;
        square_times.push_back(square_duration.count());
        std::cout << "Square Result: " << square_result << std::endl;
        std::cout << "Square Execution Time: " << square_duration.count() << " seconds" << std::endl;

        // GCD
        auto gcd_start = std::chrono::high_resolution_clock::now();
        BigInt gcd_result = a.GCD(b);
        auto gcd_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> gcd_duration = gcd_end - gcd_start;
        gcd_times.push_back(gcd_duration.count());
        std::cout << "GCD Result: " << gcd_result << std::endl;
        std::cout << "GCD Execution Time: " << gcd_duration.count() << " seconds" << std::endl;
        
        // LCM
        auto lcm_start = std::chrono::high_resolution_clock::now();
        BigInt lcm_result = a.LCM(b);
        auto lcm_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> lcm_duration = lcm_end - lcm_start;
        lcm_times.push_back(gcd_duration.count());
        std::cout << "LCM Result: " << lcm_result << std::endl;
        std::cout << "LCM Execution Time: " << lcm_duration.count() << " seconds" << std::endl;
        
        // Barret
        auto barret_start = std::chrono::high_resolution_clock::now();
        BigInt barret_result = a.LongModPowerBarrett(b, m);
        auto barret_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> barret_duration = barret_end - barret_start;
        barret_times.push_back(gcd_duration.count());
        std::cout << "Barret Result: " << barret_result << std::endl;
        std::cout << "Barret Execution Time: " << barret_duration.count() << " seconds" << std::endl;

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

    auto min_square_time = *std::min_element(square_times.begin(), square_times.end());
    auto max_square_time = *std::max_element(square_times.begin(), square_times.end());
    auto avg_square_time = std::accumulate(square_times.begin(), square_times.end(), 0.0) / square_times.size();

    auto min_gcd_time = *std::min_element(gcd_times.begin(), gcd_times.end());
    auto max_gcd_time = *std::max_element(gcd_times.begin(), gcd_times.end());
    auto avg_gcd_time = std::accumulate(gcd_times.begin(), gcd_times.end(), 0.0) / gcd_times.size();
    
    auto min_lcm_time = *std::min_element(lcm_times.begin(), lcm_times.end());
    auto max_lcm_time = *std::max_element(lcm_times.begin(), lcm_times.end());
    auto avg_lcm_time = std::accumulate(lcm_times.begin(), lcm_times.end(), 0.0) / lcm_times.size();
    
    auto min_barret_time = *std::min_element(barret_times.begin(), barret_times.end());
    auto max_barret_time = *std::max_element(barret_times.begin(), barret_times.end());
    auto avg_barret_time = std::accumulate(barret_times.begin(), barret_times.end(), 0.0) / barret_times.size();

    // Output results for each operation
    std::cout << "Addition - Min: " << min_addition_time * 1000 << "ms Max: " << max_addition_time * 1000 << "ms Avg: " << avg_addition_time * 1000 << "ms" << std::endl;
    std::cout << "Subtraction - Min: " << min_subtraction_time * 1000 << "ms Max: " << max_subtraction_time * 1000 << "ms Avg: " << avg_subtraction_time * 1000 << "ms" << std::endl;
    std::cout << "Multiplication - Min: " << min_multiplication_time * 1000 << "ms Max: " << max_multiplication_time * 1000 << "ms Avg: " << avg_multiplication_time * 1000 << "ms" << std::endl;
    std::cout << "SQUARE - Min: " << min_square_time * 1000 << "ms Max: " << max_square_time * 1000 << "ms Avg: " << avg_square_time * 1000 << "ms" << std::endl;
    std::cout << "GCD - Min: " << min_gcd_time * 1000 << "ms Max: " << max_gcd_time * 1000 << "ms Avg: " << avg_gcd_time * 1000 << "ms" << std::endl;
    std::cout << "LCM - Min: " << min_lcm_time * 1000 << "ms Max: " << max_lcm_time * 1000 << "ms Avg: " << avg_lcm_time * 1000 << "ms" << std::endl;
    std::cout << "Barret - Min: " << min_barret_time * 1000 << "ms Max: " << max_barret_time * 1000 << "ms Avg: " << avg_barret_time * 1000 << "ms" << std::endl;

    // Output results for other operations...
}


int main(int argc, const char * argv[]) {
    std::string s = "658ec5e5d8f126d692936c196bc1be68fdbc7483d7f1035c8e636c36ed5d4d0f0f69a0fa8158f4d0967e3ebd23aa4081f14540fb4f4724140e38ab2a40d33e807028b2f40b1e5362c392348d7cd81dde9ec6a79e1f4abb8b706ea0d63d30f0663a2ca1ff673d8889bc315853fca663a2c05f46c87657f0fea4ec2aafe8bbf3ac";
    //std::string s = "10001";
    BigInt a(s);
    s = "f5aa1bd307eedf96db133a218aa605a0edb6de4fa9d43d100cd75990b3c9b72347ff83796c2f886b4a58f312b8bdbdbcaf500790eee9add7165837032d2bd268e9a73cb50dca7a065abb515a18f8783c9f1bdaa5400a2b2f06cc42a2b38f41599d5bab219aaff407f6c283d479de944f8d039233709e21e30aa380b98026ac33";
    //s="873287aa2";
    BigInt b(s);
    //s = "10";
    //s="10000000000000000";
    //s="FEDCBA9876543210FEDCBA9876543210";
    //s = "68A94B93FC4C9F33E5A180F02B7C6C9200C2B74AC8E3B780579E1B5082BDBA399C62B8B71ECB100835F46872EFABA3373";
    //s="12211221";
    //BigInt a(s);
    //s = "23454236";
    //s = "D41FADD65BC8DDC4224FF788548934FE64C997EB7C0098D55C8196995BBAE8D4F30EE5AF27F0915B17D41ECE74A55B5F";
    //s = "2";
    //BigInt b(s);
    s = "5bffd2ad88c901a224caba35ba09c26ae6be9c06dae976a0fc91b7e6f5076559813cb94d2b33e86c9bf1afabc4598e769fd3e7c27bc45bbeab5e78ce48fabe89ef514ff65c64da6e6858a91600de5b4091b219b88ff502fd166ea1ef805e37bc0695d17348823898c0a7bfe217d7980ca93b724b2aecec6c4f0165e9b30002e2";
    //s = "D41FADD65BC8DDC4224FF788548934FE64C997EB7C0098D55C8196995BBAE8D4F30EE5AF27F0915B17D41ECE74A55B5F";
    //s = "2";
    BigInt m(s);

    //a = a*b;
    //std::cout << 
    //std::cout << "barret(a, b) = " << a.LongModPowerBarrett(b, m) << std::endl;
    test2(a, b, m);
    return 0;
}


