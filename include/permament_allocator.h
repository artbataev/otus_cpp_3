#pragma once

#include <memory>
#include <array>

// https://en.cppreference.com/w/cpp/named_req/Allocator#Allocator_completeness_requirements - requirements
template<typename T, size_t NElements>
struct permanent_allocator {
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = permanent_allocator<U, NElements>;
    };

    permanent_allocator(): memory_idx(0) {};
    ~permanent_allocator() = default;

    template<typename U>
    permanent_allocator(const permanent_allocator<U, NElements>&) {

    }

    pointer allocate(size_t n) {
        if (n == 0) // nothing to allocate
            return nullptr;
        if (memory_idx + n > NElements)
            throw std::bad_alloc();

        pointer current_pointer = &memory[memory_idx];
        memory_idx += n;
        return current_pointer;
    }

    void deallocate(pointer p, size_t n) {
        memory_idx -= n;
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args){
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) {
        p->~T();
    }

private:
    std::array<value_type, NElements> memory;
    size_t memory_idx = 0;
};
