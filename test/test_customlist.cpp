#include "gtest/gtest.h"
#include "custom_list.h"
#include "permament_allocator.h"
#include <sstream>

TEST(TestList, TestWithStandardAllocator) {
    CustomList<int> my_list;
    for(int i = 0; i <= 9; i++) {
        my_list.add_element(i);
    }

    std::stringstream ss;
    for(const auto& elem: my_list) {
        ss << elem << " ";
    }
    ASSERT_EQ(ss.str(), "0 1 2 3 4 5 6 7 8 9 ");
}

TEST(TestList, TestWithCustomAllocator) {
    CustomList<int, permanent_allocator<int, 10>> my_list;
    for(int i = 0; i <= 9; i++) {
        my_list.add_element(i);
    }

    std::stringstream ss;
    for(const auto& elem: my_list) {
        ss << elem << " ";
    }
    ASSERT_EQ(ss.str(), "0 1 2 3 4 5 6 7 8 9 ");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
