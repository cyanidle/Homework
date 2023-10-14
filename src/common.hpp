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
#include <algorithm>
#include <numeric>
#include <string.h>
#include <limits>
#include <fstream>

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

template<typename T>
void get_input(T& val, const char* query)
{
    std::cout << "Введите ['" << query << "'] ==> ";
    std::cin >> val;
    if (std::cin.bad()) {
        throw std::runtime_error("Введено некорретное значение.");
    }
}

template<typename T>
T get_input(const char* query) {
    T value;
    get_input(value, query);
    return value;
}

template<typename T, typename Validate>
T get_input(const char* query, Validate validate) {
    auto value = get_input<T>(query);
    validate(value);
    return value;
}

template<typename T>
inline void populate_array(T* arr, size_t size)
{
    std::cout << "Введите ['Элементов массива: ("<< size<<")'] ==> ";
    for (size_t i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }
}

template<typename T, size_t N>
size_t populate_array(T (&arr)[N])
{
    auto count = get_input<size_t>("Количество элементов массива");
    if (count >= N) {
        throw std::runtime_error(
            "Количество ["+std::to_string(count)+"] превышает максимальное ["+std::to_string(N)+']');
    }
    populate_array(arr, count);
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

template<typename Int, Int Min, Int Max>
struct ValidateRange {
    void operator()(Int i) const {
        if (Min <= i && i <= Max) {
            return;
        } else {
            throw std::runtime_error(
                "Число выходит за диапазон: ["+std::to_string(Min)+" - "+std::to_string(Max)+']');
        }
    }
};

struct Desctiption {
    std::string desc;
    bool confirm = true;
    Desctiption& Confirm(bool state) {
        confirm = state;
        return *this;
    }
    template<typename Func>
    void operator<<(Func&& func) {
        std::cout << "=======" << std::endl;
        std::cout << desc << std::endl;
        if (confirm) {
            std::cout << "Приступить? [Y/n]: " << std::flush;
            char ok;
            std::cin >> ok;
            if (ok != 'Y' && ok != 'y') {
                return;
            }
        }
        while (true) {
            try {
                func();
                break;
            } catch (std::exception& exc) {
                std::cout << "Условия задачи не соблюдены. Причина: " << exc.what();
                std::cout << "Заново." << std::endl;
                std::cout << "=======" << std::endl;
            }
        }
    }

};
