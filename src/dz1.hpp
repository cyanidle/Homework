#pragma once
#include "common.hpp"

TaskStatus DZ_1()
{
    // Площадь пирамиды по основанию и высоте (целые числа 0 < x < 100)
    auto S = get_input<uint16_t>("Площадь основания пирамиды S [0 - 100]");
    auto h = get_input<uint16_t>("Высота пирамиды h [0 - 100]");
    uint16_t V = S / 3 * h; // V <= 3`000
    print("Площадь пирамиды", V);
    return TaskOk;
}