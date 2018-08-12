#include <iostream>
#include <stdexcept>
#include <sstream>
#include <map>

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
    std::map<int, int> container1;
    for(int i = 0; i < 9; i++)
        container1[i] = factorial(i);



    return 0;
}