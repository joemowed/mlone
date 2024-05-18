#include <cstddef>
#include <gtest/gtest.h>
#include <matrix.hpp>
#include <testHelper.hpp>

TEST(matrix, simpleConstructor) {
    matrix mat(4, 4);
    matrix mat2(1, 4);
    matrix mat3(4, 1);
    matrixWalker(mat, 0);
    matrixWalker(mat2, 0);
    matrixWalker(mat3, 0);
}
