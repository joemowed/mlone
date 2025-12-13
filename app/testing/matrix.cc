
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
TEST(matrix_arithmetic, multiplication_exceptions) {
    const Matrix A{2, 3};
    const Matrix B{2, 2};
    const Matrix A_T{A.transpose()};
    const Matrix B_T{B.transpose()};
    EXPECT_ANY_THROW(A * B);
    EXPECT_ANY_THROW(B * A_T);
    EXPECT_ANY_THROW(A * B_T);
    EXPECT_NO_THROW(B * A);
    EXPECT_NO_THROW(A_T * B);
    EXPECT_NO_THROW(B_T * A);
}
TEST(matrix_arithmetic, multiplication) {
    const std::vector<Matrix::Base_t> A_values{1, 2, 3, 4, 5, 6};
    const std::vector<Matrix::Base_t> B_values{1, 2, 1, 2};
    const Matrix A{2, 3, A_values};
    const Matrix B{2, 2, B_values};
    const Matrix A_T{A.transpose()};
    const Matrix B_T{B.transpose()};

    // result1 = A^T * A
    const std::vector<Matrix::Base_t> result1_values{17, 22, 27, 22, 29,
                                                     36, 27, 36, 45};
    // result2 = A * A^T
    const std::vector<Matrix::Base_t> result2_values{14, 32, 32, 77};

    // result3 = B * B
    const std::vector<Matrix::Base_t> result3_values{3, 6, 3, 6};
    // result4 = B^T * B
    const std::vector<Matrix::Base_t> result4_values{2, 4, 4, 8};

    // result5 = B * A
    const std::vector<Matrix::Base_t> result5_values{9, 12, 15, 9, 12, 15};

    const Matrix result1{3, 3, result1_values};
    const Matrix result2{2, 2, result2_values};
    const Matrix result3{2, 2, result3_values};
    const Matrix result4{2, 2, result4_values};
    const Matrix result5{2, 3, result5_values};
    EXPECT_TRUE((A_T * A) == result1);
    EXPECT_TRUE((A * A_T) == result2);
    EXPECT_TRUE((B * B) == result3);
    EXPECT_TRUE((B_T * B) == result4);
    EXPECT_TRUE((B * A) == result5);
}
TEST(matrix_arithmetic, hadamard_exceptions) {

    const Matrix mat1(3, 3);
    const Matrix mat2(4, 2);
    const Matrix mat3(2, 3);
    const Matrix mat4(2, 3);

    EXPECT_ANY_THROW(mat1.had(mat2));
    EXPECT_ANY_THROW(mat1.had(mat3));
    EXPECT_ANY_THROW(mat2.had(mat3));
    EXPECT_NO_THROW(mat3.had(mat4));
}
TEST(matrix_arithmetic, hadamard_product) {

    const std::vector<Matrix::Base_t> values_operands{1, 2, 3, 4, 5, 6};
    const std::vector<Matrix::Base_t> values_result{1, 4, 9, 16, 25, 36};
    const Matrix mat_op1(2, 3, values_operands);
    const Matrix mat_op2(2, 3, values_operands);
    const Matrix mat_expected(2, 3, values_result);
    const Matrix result = mat_op1.had(mat_op2);
    EXPECT_TRUE(result == mat_expected);
}
TEST(matrix_arithmetic, scalar_multiplication) {

    const std::vector<Matrix::Base_t> A_values{1, 2, 3, 4, 5, 6};
    const std::vector<Matrix::Base_t> result1_values{3, 6, 9, 12, 15, 18};
    const std::vector<Matrix::Base_t> result2_values(6, 0);
    const Matrix A{2, 3, A_values};
    const Matrix result1{2, 3, result1_values};
    const Matrix result2{2, 3, result2_values};
    EXPECT_TRUE(A.scale(3) == result1);
    EXPECT_TRUE(A.scale(0) == result2);
}
