#include <iostream>
#include <map>
#include <iomanip>
#include "factorial.h"
#include "permament_allocator.h"
#include "custom_list.h"

int main() {
    // Map with standard allocator
    std::map<int, int> map_with_standard_allocator;
    for(int i = 0; i <= 9; i++) {
        map_with_standard_allocator[i] = factorial(i);
    }

    // Map with custom allocator
    std::map<int, int, std::less<>,
            permanent_allocator<std::pair<const int, int>, 10>> map_with_custom_allocator;
    for(int i = 0; i <= 9; i++) {
        map_with_custom_allocator[i] = factorial(i);
    }

    for(const auto& elem: map_with_custom_allocator) {
        std::cout << elem.first << " " << elem.second << std::endl;
    }

    // Custom container (List) with standard allocator
    CustomList<int> custom_list_with_standard_allocator;
    for(int i = 0; i <= 9; i++) {
        custom_list_with_standard_allocator.add_element(i);
    }

    // Custom container (List) with custom allocator
    CustomList<int, permanent_allocator<int, 10>> custom_list_with_permanent_allocator;
    for(int i = 0; i <= 9; i++) {
        custom_list_with_permanent_allocator.add_element(i);
    }

    for(const auto& elem: custom_list_with_permanent_allocator) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
