
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

    const std::vector<Matrix::Base_t> values{1, 2, 3, 4, 5, 6};
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

    const std::vector<Matrix::Base_t> values{1, 2, 3, 4, 5, 6};
    const Matrix mat1(2, 3, values);
    const Matrix mat2(2, 3, values);
    const Matrix mat3(3, 2, values);
    const Matrix mat4(2, 3);
    EXPECT_TRUE(mat1 == mat2);
    EXPECT_TRUE(mat3 == mat3);
    EXPECT_FALSE(mat1 == mat3);
    EXPECT_FALSE(mat1 == mat4);
}

TEST(matrix_arithmetic, addition_exceptions) {
    const Matrix mat1(3, 3);
    const Matrix mat2(4, 2);
    const Matrix mat3(2, 3);
    const Matrix mat4(2, 3);

    EXPECT_ANY_THROW(mat1 + mat2);
    EXPECT_ANY_THROW(mat1 + mat3);
    EXPECT_ANY_THROW(mat2 + mat3);
    EXPECT_NO_THROW(mat3 + mat4);
}

TEST(matrix_arithmetic, addition) {

    const std::vector<Matrix::Base_t> values_operands{1, 2, 3, 4, 5, 6};
    const std::vector<Matrix::Base_t> values_result{2, 4, 6, 8, 10, 12};
    const Matrix mat_op1(2, 3, values_operands);
    const Matrix mat_op2(2, 3, values_operands);
    const Matrix mat_expected(2, 3, values_result);
    const Matrix result = mat_op1 + mat_op2;
    EXPECT_TRUE(result == mat_expected);
}

TEST(matrix_arithmetic, subtraction_exceptions) {
    const Matrix mat1(3, 3);
    const Matrix mat2(4, 2);
    const Matrix mat3(2, 3);
    const Matrix mat4(2, 3);

    EXPECT_ANY_THROW(mat1 - mat2);
    EXPECT_ANY_THROW(mat1 - mat3);
    EXPECT_ANY_THROW(mat2 - mat3);
    EXPECT_NO_THROW(mat3 - mat4);
}

TEST(matrix_arithmetic, subtraction) {

    const std::vector<Matrix::Base_t> values_operands{1, 2, 3, 4, 5, 6};
    const std::vector<Matrix::Base_t> values_result{0, 0, 0, 0, 0, 0};
    const Matrix mat_op1(2, 3, values_operands);
    const Matrix mat_op2(2, 3, values_operands);
    const Matrix mat_expected(2, 3, values_result);
    const Matrix result = mat_op1 - mat_op2;
    EXPECT_TRUE(result == mat_expected);
}

TEST(matrix_arithmetic, transpose) {
    const std::vector<Matrix::Base_t> rect_values{1, 2, 3, 4, 5, 6};
    const std::vector<Matrix::Base_t> rect_values_T{1, 4, 2, 5, 3, 6};
    const std::vector<Matrix::Base_t> square_values{1, 2, 3, 4};
    const std::vector<Matrix::Base_t> square_values_T{1, 3, 2, 4};

    const Matrix rect_mat(2, 3, rect_values);
    const Matrix rect_mat_T(3, 2, rect_values_T);
    const Matrix square_mat(2, 2, square_values);
    const Matrix square_mat_T(2, 2, square_values_T);

    const Matrix rect_mat_calc_T = rect_mat.transpose();
    const Matrix square_mat_calc_T = square_mat.transpose();

    EXPECT_TRUE(rect_mat_T == rect_mat_calc_T);
    EXPECT_TRUE(square_mat_T == square_mat_calc_T);
}
