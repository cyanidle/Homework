#pragma once
#include <iostream>
#include <cstdint>
#include <array>
#include <vector>
#include <string>
#include <type_traits>
#include <codecvt>
#include <locale>
#include <string>

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
        //auto wdesc = std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.from_bytes(desc);
        static_assert(std::is_same<std::result_of_t<Func()>, TaskStatus>::value, 
            "Function must return TaskStatus");
        std::cout << "=======\n";
start:
        std::cout << desc << std::endl;
        if (func() != TaskOk) {
            std::cout << "Условия задачи не соблюдены. Заново" << std::endl;
            goto start;
        }
    }
};