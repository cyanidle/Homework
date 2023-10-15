#include "mat_ops.hpp"
#include <cassert>

int mat_ops::replace_if(Matrix &m, Unary predicate, int with)
{
    int count = 0;
    for (auto i = 0; i < m.n; ++i) {
        for (auto j = 0; j < m.m; ++j) {
            if (predicate(m.mat[i][j])) {
                m.mat[i][j] = with;
                ++count;
            }
        }
    }
    return count;
}

int mat_ops::mul_diagonals(const Matrix &m)
{
    assert(m.n == m.m);
    int aggr = 1;
    for (auto i = 0; i < m.lowerDim(); ++i) {
        aggr *= m.mat[i][i];
    }
    return aggr;
}

bool mat_ops::is_diag_biggest(const Matrix &m, int row)
{
    assert(row <= m.n && row <= m.m);
    auto diag_value = m.mat[row][row];
    for (auto i = 0; i < m.lowerDim(); ++i) {
        if (i != row && diag_value <= m.mat[row][i]) {
            return false;
        }
    }
    return true;
}
