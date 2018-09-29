#include <iostream>
#include <map>
#include <iomanip>
#include "factorial.h"
#include "permament_allocator.h"

int main() {
    std::map<int, int> map_with_standard_allocator;
    for(int i = 0; i <= 9; i++) {
        map_with_standard_allocator[i] = factorial(i);
    }

    std::map<int, int, std::less<>,
            permanent_allocator<std::pair<const int, int>, 10>> map_with_custom_allocator;
    for(int i = 0; i <= 9; i++) {
        map_with_custom_allocator[i] = factorial(i);
    }

    for(const auto& elem: map_with_custom_allocator) {
        std::cout << elem.first << " " << elem.second << std::endl;
    }

    return 0;
}
