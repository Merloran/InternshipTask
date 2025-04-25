#include <gtest/gtest.h>
#include "calculate.hpp"

TEST(CalculateTest, XorFunction)
{
    const Int value(3);
    EXPECT_EQ(calculate(1, value, f).val, value.val);
    EXPECT_EQ(calculate(2, value, f).val, f(value, value).val);
    EXPECT_EQ(calculate(3, value, f).val, f(f(value, value), value).val);
    EXPECT_EQ(calculate(4, value, f).val, f(f(f(value, value), value), value).val);
}

TEST(CalculateTest, ShiftFunction)
{
    const Int value(1);
    EXPECT_EQ(calculate(1, value, g).val, value.val);
    EXPECT_EQ(calculate(2, value, g).val, g(value, value).val);
    EXPECT_EQ(calculate(3, value, g).val, g(g(value, value), value).val);
    EXPECT_EQ(calculate(4, value, g).val, g(g(g(value, value), value), value).val);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}