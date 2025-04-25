#include <iostream>

#include "calculate.hpp"

int main()
{
    Int x = 5;
    std::cout << "calculate(3, x, f) = " << calculate(3, x, f).val << "\n";
    std::cout << "f(f(x, x), x) = " << f(f(x, x), x).val << "\n\n";

    std::cout << "calculate(3, x, g) = " << calculate(3, x, g).val << "\n";
    std::cout << "g(g(x, x), x) = " << g(g(x, x), x).val << "\n";

    return 0;
}
