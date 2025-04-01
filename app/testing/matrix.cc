#include <gtest/gtest.h>
#include <matrix.hpp>
// Demonstrate some basic assertions.
TEST(Matrix, construction) {
    // Expect two strings not to be equal.
    std::vector<float> vec = {1.0, 2, 3, 4, 1.0, 2, 3, 4, 5.0, 6, 7, 8};
    Matrix A(3, 4, vec);
    EXPECT_EQ(A.at(1, 1), vec.at(0));
    EXPECT_EQ(A.at(3, 2), vec.at(9));
    EXPECT_NE(A.at(3, 2), 7.0);
    EXPECT_EQ(A.getM(), 3);
    EXPECT_EQ(A.getN(), 4);
    EXPECT_EQ(A.at(3, 4), 8);
}
TEST(Matrix, nestedVectorConstruction) {
    // Expect two strings not to be equal.
    std::vector<std::vector<float>> vec = {
        {1.0, 2, 3, 4}, {1.0, 2, 3, 4}, {5.0, 6, 7, 8}};
    Matrix A(3, 4, vec);
    EXPECT_EQ(A.at(1, 1), vec.at(1).at(1));
    EXPECT_EQ(A.at(3, 2), vec.at(3).at(2));
    EXPECT_NE(A.at(3, 2), 7.0);
    EXPECT_EQ(A.getM(), 3);
    EXPECT_EQ(A.getN(), 4);
    EXPECT_EQ(A.at(3, 4), 8);
}
