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

template<typename Stream, typename...Args>
Stream open(Args&&...args) {
    Stream str;
    str.exceptions(std::ios::badbit | std::ios::failbit);
    str.open(std::forward<Args>(args)...);
    return str;
}

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
    bool repeat = true;
    Desctiption& Confirm(bool state) {
        confirm = state;
        return *this;
    }
    Desctiption& Repeat(bool state) {
        repeat = state;
        return *this;
    }
    template<typename Func>
    void operator<<(Func&& func) {
        using namespace std;
        cout << "=======" << endl;
        cout << desc << endl;
        if (confirm) {
            cout << "Приступить? [Y/n]: " << flush;
            cin.clear();
            char ok;
            cin >> ok;
            if (ok != 'Y' && ok != 'y') {
                return;
            }
        }
        while (true) {
            try {
                func();
                break;
            } catch (exception& exc) {
                cout << "Условия задачи не соблюдены. Причина: " << exc.what();
                if (!repeat) {
                    return;
                }
                cout << "Заново." << endl;
                cout << "=======" << endl;
            }
        }
    }
};

std::wstring ToWide(const char* str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
    return cvt.from_bytes(str);
}

template<typename Iter, typename Unary>
Iter remove_all_if(Iter begin, Iter end, Unary predicate)
{
    while (true) {
        auto newEnd = std::remove_if(begin, end, std::ref(predicate));
        if (newEnd == end) {
            return end;
        } else {
            end = newEnd;
        }
    }
}

template<typename Iter, typename Unary>
Iter duplicate_if(Iter iter, Iter end, Iter maxEnd, Unary predicate)
{
    for(;iter != end; ++iter) {
        if (predicate(*iter)) {
            if (end == maxEnd) {
                return end;
            }
            for (auto sub = end; sub != iter; --sub) {
                std::swap(*(sub - 1), *sub);
            }
            *iter = *(iter + 1);
            end++;
            iter++;
        }
    }
    return end;
}
