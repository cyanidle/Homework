#pragma once

namespace mat_ops
{

struct Matrix
{
    int** mat;
    int n;
};

using Unary = bool(int);

int replace_if(Matrix& m, Unary predicate, int with);
int mul_diagonals(const Matrix& m);
bool is_diag_biggest(const Matrix& m, int row);

}
