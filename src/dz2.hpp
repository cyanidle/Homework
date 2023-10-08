#pragma once
#include "common.hpp"

void DZ_2()
{
    auto number = get_input<uint32_t>(L"Число");
    auto i = get_input<uint32_t>(L"Номер бита");
    uint32_t bitMask = 1u << (i - 1);
    std::wcout << i;
    print(L"-ый бит числа: ", (number & bitMask) ? 1 : 0);
}
