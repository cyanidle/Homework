#pragma once
#include "common.hpp"

TaskStatus DZ_2()
{
    auto number = get_input<uint32_t>("Число");
    auto i = get_input<uint32_t>("Номер бита");
    uint32_t bitMask = 1u << (i - 1);
    std::cout << i;
    print("-ый бит числа: ", (number & bitMask) ? 1 : 0);
    return TaskOk;
}