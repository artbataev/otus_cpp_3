#include "gtest/gtest.h"
#include "permament_allocator.h"
#include <map>

TEST(TestAllocator, TestEmpty) {
    std::map<int, int, std::less<>,
            permanent_allocator<std::pair<const int, int>, 10>> map_with_custom_allocator;
    ASSERT_EQ(map_with_custom_allocator.size(), 0);
}

TEST(TestAllocator, TestElements) {
    std::map<int, int, std::less<>,
            permanent_allocator<std::pair<const int, int>, 20>> map_with_custom_allocator;
    for(int i = 0; i < 20; i++) {
        map_with_custom_allocator[i] = i * 100;
    }
    for(int i = 0; i < 20; i++) {
        ASSERT_EQ(map_with_custom_allocator[i], i * 100);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
