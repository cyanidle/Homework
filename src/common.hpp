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
#include <stdint.h>
#include <stddef.h>

template<typename T>
T get_input(const char* query) {
    T value;
    std::cout << "Введите ['" << query << "'] ==> ";
    std::cin >> value;
    return value;
}

template<typename T, size_t N>
size_t populate_array(T (&arr)[N])
{
    auto count = get_input<size_t>("Количество элементов массива");
    if (count >= N) {
        throw std::runtime_error(
            "Количество ["+std::to_string(count)+"] превышает максимальное ["+std::to_string(N)+']');
    }
    std::cout << "Введите ['Элементы через пробел или новую строку'] ==> ";
    for (unsigned i = 0; i < count; ++i) {
        std::cin >> arr[i];
    }
    return count;
}

template<typename T>
void print(const char* desc, T&& data) {
    std::cout << desc << ": " << data << std::endl;
}

template<typename T>
void print(T&& data) {
    std::cout << data << std::endl;
}

template<typename T>
void print_array(const T* arr, size_t size) {
    std::cout << "[ ";
    for (unsigned i = 0; i < size; ++i) {
        std::cout << arr[i] << ", ";
    }
    std::cout << "]" << std::endl;
}

struct Desctiption {
    std::string desc;

    template<typename Func>
    void operator<<(Func&& func) {
        std::cout << "=======\n";
start:
        std::cout << desc << std::endl;
        try {
            func();
        } catch (std::exception& exc) {
            std::cout << "Условия задачи не соблюдены." << std::endl;
            std::cout << exc.what() << std::endl;
            std::cout << "Заново." << std::endl;
            goto start;
        }
    }
};
