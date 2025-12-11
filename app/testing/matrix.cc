
#include <gtest/gtest.h>
#include <matrix.hpp>

TEST(matrix_at, exceptions) {

    // throw when using "matrix.at()" on uninitialized matrix
    Matrix::Impl_t mat{};
    EXPECT_ANY_THROW(mat.at(1, 2));

    // throw when using invalid indices on matrix
    Matrix mat2(2, 2);
    EXPECT_ANY_THROW(mat.at(0, 2));
    EXPECT_ANY_THROW(mat.at(2, 0));
    EXPECT_ANY_THROW(mat.at(4, 0));
    EXPECT_ANY_THROW(mat.at(0, 4));
}

TEST(matrix_init, init_with_values) {

    std::vector<Base_t> values{1, 2, 3, 4, 5, 6};
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
