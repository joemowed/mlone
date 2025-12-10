
#include <gtest/gtest.h>
#include <matrix.hpp>

TEST(matrix, terminate_at) {
    Matrix::Impl_t mat{};
    // terminate when using "matrix.at()" on uninitialized matrix
    EXPECT_DEATH(mat.at(1, 2), "");
    // terminate when using invalid indices on matrix
    Matrix mat2(2, 2);
    EXPECT_DEATH(mat.at(0, 2), "");
    EXPECT_DEATH(mat.at(2, 0), "");
    EXPECT_DEATH(mat.at(4, 0), "");
    EXPECT_DEATH(mat.at(0, 4), "");
}

TEST(matrix, init_with_values_and_at) {
    std::vector<Base_t> values{1, 2, 3, 4, 5, 6};
    Matrix mat(2, 3, values);
    EXPECT_FLOAT_EQ(mat.at(1, 1), values.at(0));
    EXPECT_FLOAT_EQ(mat.at(1, 2), values.at(1));
    EXPECT_FLOAT_EQ(mat.at(1, 3), values.at(2));
    EXPECT_FLOAT_EQ(mat.at(2, 1), values.at(3));
    EXPECT_FLOAT_EQ(mat.at(2, 2), values.at(4));
    EXPECT_FLOAT_EQ(mat.at(2, 3), values.at(5));
}
