#pragma once
#include "common.hpp"
#include "predicates.hpp"

namespace subtasks_5
{

void a()
{
    unsigned array[10'000];
    auto count = populate_array(array);
    bool has_prime = std::any_of(array, array + count, isPrime);
    if (!has_prime) {
        std::sort(array, array + count);
    }
    print_array(array, count);
}

void b()
{
    unsigned array[1'000];
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

void c()
{
    auto n = get_input<int>("n (строки)");
    auto m = get_input<int>("m (столбцы)");
    int mat[101][101];
    std::cout << "Далее необходимо будет ввести строки матрицы." << std::endl;
    auto maxRow = -1;
    auto maxMul = std::numeric_limits<int>::min();
    for (auto i = 0; i < n; ++i) {
        populate_array(mat[i], m);
        auto mul = std::accumulate(mat[i], mat[i] + m, 1, std::multiplies<int>{});
        if (mul >= maxMul) {
            maxRow = i;
            maxMul = mul;
        }
    }
    auto& row = mat[maxRow];
    for (auto j = 0; j < m; ++j) {
        row[j] = maxMul;
    }
    for (auto i = 0; i < n; ++i) {
        print_array(mat[i], m);
    }
}

bool isEqToCube(unsigned num)
{
    unsigned n = 1;
    unsigned nextCube = 1;
    while(nextCube <= num) {
        if (nextCube == num) {
            return true;
        }
        n++;
        nextCube = n*n*n;
    }
    return false;
}

void d()
{
    unsigned arr[10'000];
    auto end = arr + populate_array(arr);
    end = remove_all_if(arr, end, isPrime);
    end = duplicate_if(arr, end, std::end(arr), isEqToCube);
    print_array(arr, std::distance(arr, end));
}

}

void DZ_5()
{
    Desctiption{"Подзадание A"} << subtasks_5::a;
    Desctiption{"Подзадание B"} << subtasks_5::b;
    Desctiption{"Подзадание C"} << subtasks_5::c;
    Desctiption{"Подзадание D"} << subtasks_5::d;
}
