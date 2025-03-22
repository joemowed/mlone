#include <gtest/gtest.h>
#include <one.hpp>
// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}
TEST(HelloTest, sum) { EXPECT_EQ(sum(1, 1), 5); }
