#include "common.hpp"
#include "dz1.hpp"
#include "dz2.hpp"
#include "dz3.hpp"
#include "dz4.hpp"
#include "dz5.hpp"
#include "dz6.hpp"
#include "dz7.hpp"

using subtask = int;
using Task = void(*)(int);
auto tasks = std::vector<Task>{DZ_1, DZ_2, DZ_3, DZ_4, DZ_5, DZ_6, DZ_7};

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");
    int dzNum = AnyHomework;
    int subTask = AllSubtasks;
    if (argc == 3) {
        dzNum = strtol(argv[1], nullptr, 10);
        subTask = strtol(argv[2], nullptr, 10);
    }
    if (dzNum != AnyHomework) {
        if (dzNum >= 0 && dzNum < tasks.size()) {
            tasks[dzNum](subTask);
            return 0;
        } else {
            return 1;
        }
    }
    uint16_t task;
    std::cout << "Введите номер домашнего задания [1 - " << tasks.size() << "]: ";
    std::cin >> task;
    task -= 1;
    if (task < tasks.size()) {
        Desctiption{"Домашнее задание: " + std::to_string(task + 1)}
            .Confirm(false)
            .Call(tasks[task], subTask);
        return 0;
    } else {
        print("Такого домашнего задания нет");
        return 1;
    }
}
