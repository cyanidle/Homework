#include <iostream>
#include <cstdint>

// Вариант 6: Площадь пирамиды по основанию и высоте (целые числа)

int main()
{
    uint16_t S, h;
    std::cin >> S >> h;
    std::cout << S / 3 * h << std::endl;
    return 0;
}