#include <iostream>
#include <stdexcept>
#include <sstream>
#include <map>
#include <iomanip>

int factorial(const int n) {
    if (n < 0) {
        std::stringstream ss;
        ss << "factorial of " << n << " is undefined, use only non-negative numbers";
        throw std::logic_error(ss.str());
    }

    int result = 1;
    for(int i = 2; i <= n; i++)
        result *= i;

    return result;
}

int main() {
    std::map<int, int> map_with_standard_allocator;
    for(int i = 0; i <= 9; i++) {
        map_with_standard_allocator[i] = factorial(i);
    }

    std::map<int, int> map_with_custom_allocator;
    for(int i = 0; i <= 9; i++) {
        map_with_custom_allocator[i] = factorial(i);
    }

    for(const auto& [k, v]: map_with_custom_allocator) {
        std::cout << k << "! = " << std::setw(6) << v << std::endl;
    }



    return 0;
}