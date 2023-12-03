#include "common.hpp"
#include "mat_ops.hpp"

int main()
{
    auto n = get_input<int>("n(строки/столбцы)");
    int storage[101][101];
    int* helper[101];
    std::cout << "Далее необходимо будет ввести строки матрицы." << std::endl;
    auto maxRow = -1;
    auto maxMul = std::numeric_limits<int>::min();
    for (auto i = 0; i < n; ++i) {
        populate_array(storage[i], n);
        helper[i] = storage[i];
    }
    mat_ops::Matrix mat{helper, n};
    int diagonalsMult = mat_ops::mul_diagonals(mat);
    bool diagonalsAreBiggest = true;
    for (auto i = 0; i < n; ++i) {
        if (!mat_ops::is_diag_biggest(mat, i)) {
            diagonalsAreBiggest = false;
            break;
        }
    }
    if (diagonalsAreBiggest) {
        auto replaced = mat_ops::replace_if(
            mat,
            [](int val){return val == 0;},
            diagonalsMult
        );
        print("Подменено нулей: ", replaced);
    }
    for (auto i = 0; i < n; ++i) {
        print_array(helper[i], n);
    }
}
