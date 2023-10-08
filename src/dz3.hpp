#pragma once

#include "common.hpp"


void DZ_3()
{
    Desctiption{L"Подзадание A"} << []{
        auto A = get_input<int>(L"A");
        auto B = get_input<int>(L"B");
        auto C = get_input<int>(L"C");
        int answer;
        if (A < B && B > C) {
            answer = B + A - C;
        } else if (B % C == 0) {
            answer = B / C - B;
        } else {
            answer = A * B - C;
        }
        print(L"Результат", answer);
    };
    Desctiption{L"Подзадание B"} << []{
        auto N = get_input<int>(L"Номер месяца");
        switch (N)
        {
        case 0: print(L"Январь"); break;
        case 1: print(L"Февраль"); break;
        case 2: print(L"Март"); break;
        case 3: print(L"Апрель"); break;
        case 4: print(L"Май"); break;
        case 5: print(L"Июнь"); break;
        case 6: print(L"Июль"); break;
        case 7: print(L"Август"); break;
        case 8: print(L"Сентябрь"); break;
        case 9: print(L"Октябрь"); break;
        case 10: print(L"Ноябрь"); break;
        case 11: print(L"Декабрь"); break;
        default:
            throw std::runtime_error("Введено неправильное число-месяц (Должно быть 0 <= N <= 11)");
        }
    };
    Desctiption{L"Подзадание C"} << []{
        auto x = get_input<int>(L"Number [1/-1]");
        if (x == 1) {
            print(L"Positive number");
        } else if (x == -1) {
            print(L"Negative number");
        } else {
            print(L"Error");
        }
    };
}
