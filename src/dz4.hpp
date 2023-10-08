#pragma once
#include "common.hpp"
#include "predicates.hpp"

void DZ_4()
{
    Desctiption{L"Подзадание A"} << []{
        std::vector<int> numbers;
        auto len = get_input<uint16_t>(L"Количество чисел.");
        std::wcout << L"Введите " << len << L" чисел через пробел или с новой строки" << std::endl;
        numbers.resize(len);
        for (uint16_t i = 0; i < len; ++i) {
            std::wcin >> numbers[i];
        }
        int sum = 0;
        int max = 0;
        int counter = 0;
        int max_index = -1;
        for (auto num: numbers) {
            if (num < 0 && num % 7 == 0) {
                if (max_index == -1) {
                    max = num;
                    sum = num;
                    max_index = counter;
                } else {
                    sum += num;
                    if (num > max) {
                        max = num;
                        max_index = counter;
                    }
                }
            }
            counter++;
        }
        if (max_index == -1) {
            print(L"Нет ни одного отрицательного числа кратного 7");
        } else {
            print(L"Сумма отрицательных чисел, кратных 7", sum);
            print(L"Маскимальное из этих чисел", max);
            print(L"Индекс этого числа", max_index);
        }

    };
    Desctiption{L"Подзадание B"} << []{
        auto N = get_input<uint32_t>(L"Число");
        print(L"Произведение цифр", digitsMul(N));
    };
}
