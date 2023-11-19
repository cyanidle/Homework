#include "common.hpp"
#include "containers/fwd_list.hpp"

void DZ_8(int)
{
    auto list = fwd_list<int>{};
    auto n = get_input<uint>("количество натуральных чисел");
    std::cout << "Числа: ";
    for (auto i = 0u; i < n; ++i) {
        int val;
        std::cin >> val;
        list.append(val);
    }
}
