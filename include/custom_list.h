#pragma once

#include <memory>

template<typename T, typename _Alloc = std::allocator<T>>
class CustomList {
public:
    struct Element {
        Element() = default;
        explicit Element(const T& value_): value(value_), next(nullptr) {};
        T value;
        Element* next;
    };

    using Alloc = typename _Alloc::template rebind<Element>::other;
    CustomList(): head(nullptr), tail(nullptr), list_allocator(Alloc()) {};

    void add_element(const T& value) {
        auto element = list_allocator.allocate(1);
        element->value = value;
        if (element) {
            if (head) {
                tail->next = element;
                tail = element;
            } else {
                head = element;
                tail = element;
            }
        }
    }

    class CustomListIterator
    {
    public:
        using value_type = CustomList;
        using pointer = CustomList* ;
        using difference_type = int;

        CustomListIterator(Element* element) : current_element(element) {}
        CustomListIterator operator++() {
            current_element = current_element->next;
            return current_element;
        }

        decltype(auto) operator*() { return current_element->value; }

        bool operator==(const CustomListIterator& rhs) { return current_element == rhs.current_element; }
        bool operator!=(const CustomListIterator& rhs) { return current_element != rhs.current_element; }
    private:
        Element* current_element;
    };

    CustomListIterator begin()
    {
        return CustomListIterator(this->head);
    }

    CustomListIterator end()
    {
        if (tail)
            return CustomListIterator(this->tail->next);
        return CustomListIterator(nullptr);
    }

private:
    Element* head = nullptr;
    Element* tail = nullptr;
    Alloc list_allocator;
};
