#pragma once
#include "common.hpp"

std::pair<int, int> first_last_digit(int num)
{
    //123 -> "123" -> {'1' - '0', '3' - '0'} -> {1, 3};
    auto str = std::to_string(num);
    return {(num < 0 ? str[1]: str.front()) - '0', str.back() - '0'};
}

bool isPrime(size_t n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    for (size_t i = 2; i <= n / 2; i++)
        if (n % i == 0)
            return false;
    return true;
}

template<typename T, typename Call>
void forEachDigit(T num, Call call)
{
    while(num) {
        call(num % 10);
        num /= 10;
    }
}

template<typename T>
size_t digitsMul(T num)
{
    size_t aggr = 1;
    forEachDigit(num, [&](int digit){
        aggr *= digit;
    });
    return aggr;
}


template<typename T>
size_t digitsSum(T num)
{
    size_t aggr = 0;
    forEachDigit(num, [&](int digit){
        aggr += digit;
    });
    return aggr;
}

bool isVowel(wchar_t ch)
{
    constexpr wchar_t vowels[] = {
        L"аеояёуыюАЕОУЯИЫЁЮ"
    };
    auto end = vowels + ARRAY_SIZE(vowels);
    return std::find(vowels, end, ch) != end;
}

template<typename Ch, typename Call>
void ForEachWord(Ch* arr, Call call)
{
    size_t offset = 0;
    size_t len = 0;
    Ch ch;
    while ((ch = *arr++)) {
        if (ch == ' ') {
            call(arr + offset, len);
            offset = len + 1;
        }
        len++;
    }
    if (len) {
        call(arr + offset, len);
    }
}

using DigitsCount_t = std::array<uint8_t, 10>;

template<typename Num>
DigitsCount_t digitsCount(Num num)
{
    std::array<uint8_t, 10> hits = {};
    forEachDigit(num, [&](int dig){
        hits[dig]++;
    });
    return hits;
}
