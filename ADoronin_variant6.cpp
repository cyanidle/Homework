#include <iostream>
#include <cstdint>
#include <array>
#include <vector>

void DZ_1()
{
    // Площадь пирамиды по основанию и высоте (целые числа)
    uint16_t S, h;
    std::cin >> S >> h;
    std::cout << S / 3 * h << std::endl;
}

void DZ_2()
{
    uint32_t x, i;
    std::cin >> x >> i;
    std::cout << (x & (1 << i)) << std::endl;
}

void DZ_3()
{
    auto subtask_A = []{
        int A, B, C;
        std::cin >> A >> B >> C;
        if (C < A && A < B) {
            std::cout << (B + A - C);
        } else if (B % C == 0) {
            std::cout << (B / C - B);
        } else {
            std::cout << (A * B - C);
        }
    };
    auto subtask_B = []{
        int N;
        std::cin >> N;
        switch (N)
        {
        case 0: std::cout << "Январь"; break;
        case 1: std::cout << "Февраль"; break;
        case 2: std::cout << "Март"; break;
        case 3: std::cout << "Апрель"; break;
        case 4: std::cout << "Май"; break;
        case 5: std::cout << "Июнь"; break;
        case 6: std::cout << "Июль"; break;
        case 7: std::cout << "Август"; break;
        case 8: std::cout << "Сентябрь"; break;
        case 9: std::cout << "Октябрь"; break;
        case 10: std::cout << "Ноябрь"; break;
        case 11: std::cout << "Декабрь"; break;
        default: std::cout << "Введено неправильно число (Должно быть 0 < N < 12)";
        }
    };
    auto subtask_C = []{
        int x;
        std::cin >> x;
        if (x == 1) {
            std::cout << "Positive number";
        } else if (x == -1) {
            std::cout << "Negative number";
        } else {
            std::cout << "Error";
        }
    };
    subtask_A();
    subtask_B();
    subtask_C();
}

void DZ_4()
{
    auto subtask_A = [](const std::vector<int>& numbers){
        int sum = 0;
        for (auto num: numbers) {
            if (num < 0 && num % 7 == 0) {
                sum += num;
            }
        }
        std::cout << sum;
    };
    auto subtask_B = []{
        uint32_t N;
        std::cin >> N;
        uint32_t sum = 0;
        while(N) {
            sum += N % 10;
            N /= 10;
        }
        std::cout << sum;
    };  
    //subtask_A()
    subtask_B();
}

using Task = void(*)(void);
auto tasks = std::vector<Task>{DZ_1, DZ_2, DZ_3, DZ_4};

int main()
{
    uint16_t task;
    std::cout << "Введите номер домашнего задания: ";
    std::cin >> task;
    if (task < tasks.size()) {
        tasks[task]();
    } else {
        std::cout << "Такого Домашнего задания нет" << std::endl;
    }
    return 0;
}