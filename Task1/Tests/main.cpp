#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include "compress.hpp"

TEST(CompressionTest, CompressesCorrectly)
{
    Array2D<uint32_t> input =
    {
        0, 0, 0, 1, 1, 2, 3,
        0, 0, 4, 4, 4, 2, 2,
        2, 2, 2, 2, 2, 1, 2
    };

    const CompressedData<uint32_t> result = compress_data(input);
    ASSERT_TRUE(result.has_value());

    const std::vector<Data<uint32_t>> expected = 
    {
        {0, 3}, {1, 2}, {2, 1}, {3, 1},
        {0, 2}, {4, 3}, {2, 2},
        {2, 5}, {1, 1}, {2, 1}
    };

    ASSERT_EQ(result->size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        EXPECT_EQ(result->at(i).value, expected[i].value);
        EXPECT_EQ(result->at(i).count, expected[i].count);
    }
}

TEST(CompressionTest, ReturnsNulloptIfCompressedIsBigger)
{
    Array2D<uint8_t> input = 
    {
         1,  2,  3,  4,  5,  6,  7,
         8,  9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21
    };

    CompressedData<uint8_t> result = compress_data(input);
    EXPECT_FALSE(result.has_value());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}