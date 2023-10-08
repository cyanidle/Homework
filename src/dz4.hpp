#pragma once
#include "common.hpp"
#include "predicates.hpp"

void DZ_4()
{
    Desctiption{"Подзадание A"} << []{
        std::vector<int> numbers;
        auto len = get_input<uint16_t>("Количество чисел.");
        std::cout << "Введите " << len << " чисел через пробел или с новой строки" << std::endl;
        numbers.resize(len);
        for (uint16_t i = 0; i < len; ++i) {
            std::cin >> numbers[i];
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
            print("Нет ни одного отрицательного числа кратного 7");
        } else {
            print("Сумма отрицательных чисел, кратных 7", sum);
            print("Маскимальное из этих чисел", max);
            print("Индекс этого числа", max_index);
        }

    };
    Desctiption{"Подзадание B"} << []{
        auto N = get_input<uint32_t>("Число");
        print("Произведение цифр", digitsMul(N));
    };
}
