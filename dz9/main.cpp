#include "containers/list.hpp"
#include "common.hpp"
#include <cassert>
#include "predicates.hpp"

bool hasTwoSameDigits(int num)
{
    DigitsCount_t hits = digitsCount(num);
    for (auto digit: hits) {
        if (digit >= 2) {
            return true;
        }
    }
    return false;
}

bool startsWithEven(int num)
{
    return !(first_last_digit(num).first & 1);
}

int main()
{
    linked_list<int> list{};
    auto n = get_input<uint>("количество натуральных чисел");
    std::cout << "Числа: ";
    for (auto i = 0u; i < n; ++i) {
        int val;
        std::cin >> val;
        list.append(val);
    }
    auto hasAny = std::find_if(list.begin(), list.end(), hasTwoSameDigits) != list.end();
    if (hasAny) {
        list.bubble_sort([](int lhs, int rhs){
            auto l = first_last_digit(lhs).second;
            auto r = first_last_digit(rhs).second;
            return l > r;
        });
    } else {
        for (auto it = list.begin(); it != list.end();) {
            if (startsWithEven(*it)) {
                it = list.erase(it);
            } else {
                ++it;
            }
        }
        for (auto it = list.begin(); it != list.end(); ++it) {
            it = list.insert(it, *it);
            ++it;
        }
    }
    std::cout << "Результат: [";
    for (auto val: list) {
        std::cout << val << " ,";
    }
    std::cout << ']' << std::endl;
}
