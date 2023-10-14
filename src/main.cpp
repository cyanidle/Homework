#include "common.hpp"
#include "dz1.hpp"
#include "dz2.hpp"
#include "dz3.hpp"
#include "dz4.hpp"
#include "dz5.hpp"
#include "dz6.hpp"

using Task = void(*)(void);
auto tasks = std::vector<Task>{DZ_1, DZ_2, DZ_3, DZ_4, DZ_5, DZ_6};

int main()
{
    std::locale::global(std::locale("ru_RU.cp1251"));
    uint16_t task;
    std::cout << "Введите номер домашнего задания [1 - " << tasks.size() << "]: ";
    std::cin >> task;
    task -= 1;
    if (task < tasks.size()) {
        Desctiption{"Домашнее задание: " + std::to_string(task + 1)}.Confirm(false) << tasks[task];
        return 0;
    } else {
        print("Такого домашнего задания нет");
        return 1;
    }
}
