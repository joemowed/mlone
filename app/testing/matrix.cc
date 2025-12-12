
#include "matrix.hpp"
#include <gtest/gtest.h>

TEST(matrix_at, exceptions) {

    // throw when using "matrix.at()" on uninitialized matrix
    Matrix mat(1, 1);
    EXPECT_ANY_THROW(mat.at(1, 2));

    // throw when using invalid indices on matrix
    Matrix mat2(2, 2);
    EXPECT_ANY_THROW(mat2.at(0, 2));
    EXPECT_ANY_THROW(mat2.at(2, 0));
    EXPECT_ANY_THROW(mat2.at(4, 0));
    EXPECT_ANY_THROW(mat2.at(0, 4));
}

TEST(matrix_init, init_with_values) {

    std::vector<Matrix::Base_t> values{1, 2, 3, 4, 5, 6};
    Matrix mat(2, 3, values);
    EXPECT_FLOAT_EQ(mat.at(1, 1), values.at(0));
    EXPECT_FLOAT_EQ(mat.at(1, 2), values.at(1));
    EXPECT_FLOAT_EQ(mat.at(1, 3), values.at(2));
    EXPECT_FLOAT_EQ(mat.at(2, 1), values.at(3));
    EXPECT_FLOAT_EQ(mat.at(2, 2), values.at(4));
    EXPECT_FLOAT_EQ(mat.at(2, 3), values.at(5));

    // throw if values vector length does not match matrix dimensions
    EXPECT_ANY_THROW(Matrix mat(3, 1, values));
    EXPECT_ANY_THROW(Matrix mat(1, 3, values));
    EXPECT_ANY_THROW(Matrix mat(1, 1, values));
    EXPECT_ANY_THROW(Matrix mat(5, 5, values));
}

TEST(matrix_init, default_initialization) {

    Matrix mat(2, 3);
    EXPECT_FLOAT_EQ(mat.at(1, 1), 0);
    EXPECT_FLOAT_EQ(mat.at(1, 2), 0);
    EXPECT_FLOAT_EQ(mat.at(1, 3), 0);
    EXPECT_FLOAT_EQ(mat.at(2, 1), 0);
    EXPECT_FLOAT_EQ(mat.at(2, 2), 0);
    EXPECT_FLOAT_EQ(mat.at(2, 3), 0);
}

TEST(matrix_arithmetic, comparison) {

    std::vector<Matrix::Base_t> values{1, 2, 3, 4, 5, 6};
    Matrix mat1(2, 3, values);
    Matrix mat2(2, 3, values);
    Matrix mat3(3, 2, values);
    Matrix mat4(2, 3);
    EXPECT_TRUE(mat1 == mat2);
    EXPECT_TRUE(mat3 == mat3);
    EXPECT_FALSE(mat1 == mat3);
    EXPECT_FALSE(mat1 == mat4);
}

TEST(matrix_arithmetic, addition_exceptions) {
    Matrix mat1(3, 3);
    Matrix mat2(4, 2);
    Matrix mat3(2, 3);
    Matrix mat4(2, 3);

    EXPECT_ANY_THROW(mat1 + mat2);
    EXPECT_ANY_THROW(mat1 + mat3);
    EXPECT_ANY_THROW(mat2 + mat3);
    EXPECT_NO_THROW(mat3 + mat4);
}

TEST(matrix_arithmetic, addition) {

    std::vector<Matrix::Base_t> values_operands{1, 2, 3, 4, 5, 6};
    std::vector<Matrix::Base_t> values_result{2, 4, 6, 8, 10, 12};
    Matrix mat_op1(2, 3, values_operands);
    Matrix mat_op2(2, 3, values_operands);
    Matrix mat_expected(2, 3, values_result);
    Matrix result = mat_op1 + mat_op2;
    EXPECT_TRUE(result == mat_expected);
}

TEST(matrix_arithmetic, subtraction_exceptions) {
    Matrix mat1(3, 3);
    Matrix mat2(4, 2);
    Matrix mat3(2, 3);
    Matrix mat4(2, 3);

    EXPECT_ANY_THROW(mat1 - mat2);
    EXPECT_ANY_THROW(mat1 - mat3);
    EXPECT_ANY_THROW(mat2 - mat3);
    EXPECT_NO_THROW(mat3 - mat4);
}

TEST(matrix_arithmetic, subtraction) {

    std::vector<Matrix::Base_t> values_operands{1, 2, 3, 4, 5, 6};
    std::vector<Matrix::Base_t> values_result{0, 0, 0, 0, 0, 0};
    Matrix mat_op1(2, 3, values_operands);
    Matrix mat_op2(2, 3, values_operands);
    Matrix mat_expected(2, 3, values_result);
    Matrix result = mat_op1 - mat_op2;
    EXPECT_TRUE(result == mat_expected);
}
