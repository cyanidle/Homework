#pragma once
#include "common.hpp"

bool isPrime(long int n)
{
    if (n <= 1)
        return false;
    for (long int i = 2; i <= n / 2; i++)
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
    size_t aggr = 0;
    forEachDigit(num, [&](int digit){
        if (aggr) aggr *= digit;
        else aggr = digit;
    });
    return aggr;
}


template<typename T>
size_t digitsSum(T num)
{
    size_t aggr = 0;
    forEachDigit(num, [&](int digit){
        if (aggr) aggr += digit;
        else aggr = digit;
    });
    return aggr;
}
