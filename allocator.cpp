#include <iostream>
#include <map>
#include <iomanip>
#include "factorial.h"

template<typename T>
struct permanent_allocator {
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = permanent_allocator<U>;
    };

    permanent_allocator() = default;
    ~permanent_allocator() = default;

    template<typename U>
    permanent_allocator(const permanent_allocator<U>&) {

    }

    T* allocate(std::size_t n) {
        auto p = std::malloc(n * sizeof(T));
        if (!p)
            throw std::bad_alloc();
        return reinterpret_cast<T *>(p);
    }

    void deallocate(T *p, std::size_t n) {
        std::free(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args){
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {
        p->~T();
    }
};

int main() {
    std::map<int, int> map_with_standard_allocator;
    for(int i = 0; i <= 9; i++) {
        map_with_standard_allocator[i] = factorial(i);
    }

    std::map<int, int, std::less<>,
            permanent_allocator<std::pair<const int, int>>> map_with_custom_allocator;
    for(int i = 0; i <= 9; i++) {
        map_with_custom_allocator[i] = factorial(i);
    }

    for(const auto& elem: map_with_custom_allocator) {
        std::cout << elem.first << "! = " << std::setw(6) << elem.second << std::endl;
    }

    return 0;
}