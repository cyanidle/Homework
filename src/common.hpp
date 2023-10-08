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

inline int wc_collate(wchar_t a, wchar_t b) {
    return wcscoll((wchar_t[2]){a, 0}, (wchar_t[2]){b, 0});
}

template<typename T>
void get_input(T& val, const wchar_t* query)
{
    std::wcout << L"Введите ['" << query << L"'] ==> ";
    std::wcin >> val;
    if (std::wcin.bad()) {
        throw std::runtime_error("Введено некорретное значение.");
    }
}

template<typename T>
T get_input(const wchar_t* query) {
    T value;
    get_input(value, query);
    return value;
}

template<typename T, typename Validate>
T get_input(const wchar_t* query, Validate validate) {
    auto value = get_input<T>(query);
    validate(value);
    return value;
}

template<typename T>
inline void populate_array(T* arr, size_t size)
{
    std::wcout << L"Введите ['Элементов массива: (L"<< size<<")'] ==> ";
    for (size_t i = 0; i < size; ++i) {
        std::wcin >> arr[i];
    }
}

template<typename T, size_t N>
size_t populate_array(T (&arr)[N])
{
    auto count = get_input<size_t>(L"Количество элементов массива");
    if (count >= N) {
        throw std::runtime_error(
            L"Количество ["+std::to_wstring(count)+L"] превышает максимальное ["+std::to_wstring(N)+L']');
    }
    populate_array(arr, count);
    return count;
}

template<typename T>
void print(const wchar_t* desc, T&& data) {
    std::wcout << desc << L": " << data << std::endl;
}

template<typename T>
void print(T&& data) {
    std::wcout << data << std::endl;
}

template<typename T>
void print_array(const T* arr, size_t size) {
    std::wcout << L"[ ";
    for (unsigned i = 0; i < size; ++i) {
        std::wcout << arr[i] << L", ";
    }
    std::wcout << L"]" << std::endl;
}

template<typename Int, Int Min, Int Max>
struct ValidateRange {
    void operator()(Int i) const {
        if (Min <= i && i <= Max) {
            return;
        } else {
            throw std::runtime_error(
                "Число выходит за диапазон: ["+std::to_wstring(Min)+" - "+std::to_wstring(Max)+']');
        }
    }
};

struct Desctiption {
    std::wstring desc;
    bool confirm = true;
    Desctiption& Confirm(bool state) {
        confirm = state;
        return *this;
    }
    template<typename Func>
    void operator<<(Func&& func) {
        std::wcout << L"=======" << std::endl;
        std::wcout << desc << std::endl;
        if (confirm) {
            std::wcout << L"Приступить? [Y/n]: " << std::flush;
            wchar_t ok;
            std::wcin >> ok;
            if (ok != 'Y' && ok != 'y') {
                return;
            }
        }
        while (true) {
            try {
                func();
                break;
            } catch (std::exception& exc) {
                std::wcout << L"Условия задачи не соблюдены. Причина: " << exc.what();
                std::wcout << L"Заново." << std::endl;
                std::wcout << L"=======" << std::endl;
            }
        }
    }

};
