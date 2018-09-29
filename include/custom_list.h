#pragma once

#include <memory>

template<typename T, typename Alloc = std::allocator<T>>
class CustomList {
public:

    struct Element {
        explicit Element(const T& value_): value(value_), next(nullptr) {};
        T value;
        std::shared_ptr<Element> next;
    };

    void add_element(const T& value) {
        auto element = std::allocate_shared<Element, Alloc>(list_allocator, value);
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

        CustomListIterator(std::shared_ptr<Element> element) : current_element(element) {}
        CustomListIterator operator++() {
            current_element = current_element->next;
            return current_element;
        }

        decltype(auto) operator*() { return current_element->value; }

        bool operator==(const CustomListIterator& rhs) { return current_element == rhs.current_element; }
        bool operator!=(const CustomListIterator& rhs) { return current_element != rhs.current_element; }
    private:
        std::shared_ptr<Element> current_element;
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
    std::shared_ptr<Element> head = nullptr;
    std::shared_ptr<Element> tail = nullptr;
    Alloc list_allocator;
};
