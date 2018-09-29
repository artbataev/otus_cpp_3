#include "gtest/gtest.h"
#include "permament_allocator.h"
#include <map>

TEST(TestAllocator, TestEmpty) {
    std::map<int, int, std::less<>,
            permanent_allocator<std::pair<const int, int>, 10>> map_with_custom_allocator;
    ASSERT_EQ(map_with_custom_allocator.size(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
