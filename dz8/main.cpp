#include "common.hpp"
#include "containers/fwd_list.hpp"
#include "predicates.hpp"

bool isOnlyFromOdd(int num)
{
    bool res = true;
    forEachDigit(num, [&](int dig){
        if (!(dig & 1)) {
            res = false;
        }
    });
    return res;
}

bool numberHas6and8(int num)
{
    auto hits = digitsCount(num);
    return hits[6] && hits[8];
}

int main()
{
    auto list = fwd_list<int>{};
    auto n = get_input<uint>("количество натуральных чисел");
    std::cout << "Числа: ";
    for (auto i = 0u; i < n; ++i) {
        int val;
        std::cin >> val;
        list.append(val);
    }
    auto isSortedFirstOrLast = std::is_sorted(list.begin(), list.end(), [](int lhs, int rhs){
        auto pLeft = first_last_digit(lhs);
        auto pRight = first_last_digit(rhs);
        return pLeft.first < pRight.first || pLeft.second < pRight.second;
    });
    if (isSortedFirstOrLast) {
        for (auto it = list.begin(); it != list.end();) {
            if (isOnlyFromOdd(*it)) {
                it = list.erase(it);
            } else {
                ++it;
            }
        }
        for (auto it = list.begin(); it != list.end();) {
            if (numberHas6and8(*it)) {
                it = list.insert(it, *it);
            } else {
                ++it;
            }
        }
    } else {
        list.bubble_sort();
    }
    std::cout << "Результат: [";
    for (auto val: list) {
        std::cout << val << " ,";
    }
    std::cout << ']' << std::endl;
}
