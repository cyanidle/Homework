#include <iostream>
#include <cstdint>
#include <array>
#include <vector>
#include <string>
#include <type_traits>

enum TaskStatus {
    TaskOk = true,
    TaskFail = false,
};

template<typename T>
T get_input(const char* query) {
    T value;
    std::cout << "Введите '" << query << "' : ";
    std::cin >> value;
    return value;
}

template<typename T>
void print(const char* desc, T&& data) {
    std::cout << desc << ": " << data << std::endl;
}

template<typename T>
void print(T&& data) {
    std::cout << data << std::endl;
}

struct Desctiption {
    std::string desc;

    template<typename Func>
    void operator<<(Func&& func) {
        std::cout << "=======\n";
start:
        std::cout << desc << std::endl;
        if (func() != TaskOk) {
            std::cout << "Условия задачи не соблюдены. Заново" << std::endl;
            goto start;
        }
    }
};

TaskStatus DZ_1()
{
    // Площадь пирамиды по основанию и высоте (целые числа 0 < x < 100)
    auto S = get_input<uint16_t>("Площадь основания пирамиды S [0 - 100]");
    auto h = get_input<uint16_t>("Высота пирамиды h [0 - 100]");
    uint16_t V = S / 3 * h; // V <= 3`000
    print("Площадь пирамиды", V);
    return TaskOk;
}

TaskStatus DZ_2()
{
    auto number = get_input<uint32_t>("Число");
    auto i = get_input<uint32_t>("Номер бита");
    uint32_t bitMask = 1 << (i + 1);
    print("i бит числа: ", number & bitMask);
    return TaskOk;
}

TaskStatus DZ_3()
{
    auto subtask_A = []{
        auto A = get_input<int>("A");
        auto B = get_input<int>("B");
        auto C = get_input<int>("C");
        int answer;
        if (A < B && B > C) {
            answer = B + A - C;
        } else if (B % C == 0) {
            answer = B / C - B;
        } else {
            answer = A * B - C;
        }
        print("Результат", answer);
        return TaskOk;
    };
    auto subtask_B = []{
        auto N = get_input<int>("Номер месяца");
        switch (N)
        {
        case 0: print("Январь"); break;
        case 1: print("Февраль"); break;
        case 2: print("Март"); break;
        case 3: print("Апрель"); break;
        case 4: print("Май"); break;
        case 5: print("Июнь"); break;
        case 6: print("Июль"); break;
        case 7: print("Август"); break;
        case 8: print("Сентябрь"); break;
        case 9: print("Октябрь"); break;
        case 10: print("Ноябрь"); break;
        case 11: print("Декабрь"); break;
        default: 
            print("Введено неправильное число-месяц (Должно быть 0 <= N <= 11)");
            return TaskFail;
        }
        return TaskOk;
    };
    auto subtask_C = []{
        auto x = get_input<int>("Number [1/-1]");
        if (x == 1) {
            print("Positive number");
        } else if (x == -1) {
            print("Negative number");
        } else {
            print("Error");
            return TaskFail;
        }
        return TaskOk;
    };
    Desctiption{"Подзадание A"} << subtask_A;
    Desctiption{"Подзадание B"} << subtask_B;
    Desctiption{"Подзадание C"} << subtask_C;
    return TaskOk;
}

TaskStatus DZ_4()
{
    auto subtask_A = []{
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
        return TaskOk;

    };
    auto subtask_B = []{
        auto N = get_input<uint32_t>("Число");
        uint32_t aggr = 0;
        bool start = true;
        while(N) {
            auto digit = N % 10;
            if (start) {
                start = false;
                aggr = digit;
            } else {
                aggr *= N % 10;
            }
            N /= 10;
        }
        print("Произведение цифр", aggr);
        return TaskOk;
    };  
    Desctiption{"Подзадание A"} << subtask_A;
    Desctiption{"Подзадание B"} << subtask_B;
    return TaskOk;
}

using Task = TaskStatus(*)(void);
auto tasks = std::vector<Task>{DZ_1, DZ_2, DZ_3, DZ_4};

int main()
{
    uint16_t task;
    std::cout << "Введите номер домашнего задания [1 - " << tasks.size() << "]: ";
    std::cin >> task;
    task -= 1;
    if (task < tasks.size()) {
        Desctiption{"Домашнее задание: " + std::to_string(task + 1)} << tasks[task];
        return 0;
    } else {
        print("Такого домашнего задания нет");
        return 1;
    }
}