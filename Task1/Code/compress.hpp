#pragma once
#include <array>
#include <optional>
#include <vector>

template <typename Type>
concept Numeric = std::is_arithmetic_v<Type>;

template <typename Type>
struct Data
{
    Type value;
    uint8_t count;
};

constexpr size_t SIZE_X{ 7 };
constexpr size_t SIZE_Y{ 3 };

template <typename Type>
using Array2D = std::array<std::array<Type, SIZE_X>, SIZE_Y>;

template <typename Type>
using CompressedData = std::optional<std::vector<Data<Type>>>;

template <Numeric Type>
CompressedData<Type> compress_data(const Array2D<Type> &input)
{
    CompressedData<Type> compressed;

    constexpr size_t PREDICTED_MEMORY_USAGE = SIZE_X * SIZE_Y / 4;
    compressed.emplace();
    compressed->reserve(PREDICTED_MEMORY_USAGE);

    for (size_t y = 0; y < SIZE_Y; ++y)
    {
        Type currentValue = input[y][0];
        uint8_t currentCount = 1UI8;
        for (size_t x = 1; x < SIZE_X; ++x)
        {
            if (input[y][x] == currentValue || 
                currentCount == std::numeric_limits<uint8_t>::max())
                // The second case cannot happen because the maximum size is 21,
                // but I keep it if the input changes
            {
                ++currentCount;
                continue;
            }

            compressed->push_back(Data{ currentValue, currentCount });
            currentValue = input[y][x];
            currentCount = 1UI8;
        }
        compressed->push_back(Data{ currentValue, currentCount });
    }

    size_t compressedByteSize = compressed->size()
                              * sizeof(compressed->at(0)); // I ignore additional std::vector fields
    size_t inputByteSize = SIZE_X * SIZE_Y * sizeof(Type);
    if (compressedByteSize > inputByteSize)
    {
        compressed.reset();
    }

    return compressed;
}