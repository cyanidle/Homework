#pragma once
#include "common.hpp"
#include "predicates.hpp"
#include <algorithm>

namespace subtasks_5
{

void a()
{
    constexpr auto MAX = 10'001;
    unsigned array[MAX];
    auto count = populate_array(array);
    bool has_prime = std::any_of(array, array + count, isPrime);
    if (!has_prime) {
        std::sort(array, array + count);
    }
    print_array(array, count);
}

void b()
{
    constexpr auto MAX = 1'001;
    unsigned array[MAX];
    auto count = populate_array(array);
    auto predicate = [](unsigned lhs, unsigned rhs){
        auto lSum = digitsSum(lhs);
        auto rSum = digitsSum(rhs);
        if (lSum < rSum) {
            return true;
        } else if (lSum == rSum) {
            auto lMul = digitsMul(lhs);
            auto rMul = digitsMul(rhs);
            if (lMul < rMul) {
                return true;
            } else if (lMul == rMul) {
                return lhs < rhs;
            }
        }
        return false;
    };
    std::sort(array, array + count, predicate);
    print_array(array, count);
}



}

void DZ_5()
{
    Desctiption{"А"} << subtasks_5::a;
    Desctiption{"Б"} << subtasks_5::b;
}
