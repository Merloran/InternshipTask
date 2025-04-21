#include <iostream>
#include "compress.hpp"


int main()
{
    Array2D<uint32_t> data =
    {
        0, 0, 0, 1, 1, 2, 3,
        0, 0, 4, 4, 4, 2, 2,
        2, 2, 2, 2, 2, 1, 2
    };

    CompressedData<uint32_t> result = compress_data(data);

    if (result.has_value() == false)
    {
        std::cout << "Compressed is bigger than original data!";
        return 0;
    }

    for (auto [value, count] : result.value())
    {
        std::cout << "{" << value << "," << int32_t(count) << "},";
    }
    return 0;
}