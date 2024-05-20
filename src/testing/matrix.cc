#include <cstddef>
#include <gtest/gtest.h>
#include <matrix.hpp>
#include <random>
#include <testHelper.hpp>
#include <vector>
TEST(matrix, simpleConstructor) {
    matrix mat(4, 4);
    matrix mat4(4, 4);
    matrix mat2(1, 4);
    matrix mat3(4, 1);
    EXPECT_EQ(mat.at(0, 0), 0);
    matrixWalker(mat, mat4);
    matrixWalker(mat, 0);
    matrixWalker(mat2, 0);
    matrixWalker(mat3, 0);
    mat.coutMat("mat");
    mat2.coutMat("mat2");
    mat3.coutMat("mat3");
}
TEST(matrix, vectorConstructor) {
    std::vector<float> vec{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4};
    matrix mat(4, 3, vec);
    for (size_t x = 0; x < mat.i(); x++) {
        for (size_t y = 0; y < mat.j(); y++) {
            EXPECT_EQ(mat.at(x, y), vec.at(calculateDataIndex(x, y, mat)));
        }
    }
}
TEST(matrix, randomConstructor) {
    std::normal_distribution<float> dist(0, 2);
    EXPECT_NO_THROW(matrix mat(40, 400, dist));
    matrix mat(40, 400, dist);
    matrix mat2(500, 500, dist);
    EXPECT_NO_THROW(mat.at(39, 399));
    EXPECT_NO_THROW(mat.at(0, 0));
    mat.coutMatDims("Mat");
    mat2.coutMatDims("Mat2");
}
TEST(matrix, equality) {
    matrix mat{10, 10};
    matrix mat2{10, 10};
    matrix mat3{5, 10};
    matrix mat4{10, 5};
    EXPECT_EQ(true, mat == mat2);
    EXPECT_EQ(true, mat2 == mat);
    EXPECT_EQ(false, mat2 == mat4);
    EXPECT_NE(true, (mat == mat3));
    EXPECT_NE(true, mat == mat4);
    EXPECT_NE(true, mat3 == mat4);
}
TEST(matrix, addition) {
    const std::vector<float> vec1 = randVec(10);
    matrix mat(2, 5, vec1);
    matrix mat2(2, 5, vec1);
    matrix mat3 = mat + mat2;
    for (size_t x = 0; x < mat.i(); x++) {
        for (size_t y = 0; y < mat.j(); y++) {
            EXPECT_EQ(mat3.at(x, y), vec1.at(calculateDataIndex(x, y, mat)) * 2);
        }
    }
}
TEST(matrix, subtraction) {

    // const std::vector<float> vec1 = randVec(10);
    // const std::vector<float> vec2 = randVec(10);
    const std::vector<float> vec1(10, 2);
    matrix mat(2, 5, vec1);
    matrix mat2(2, 5, vec1);
    matrix mat3 = mat - mat2;
    for (size_t x = 0; x < mat.i(); x++) {
        for (size_t y = 0; y < mat.j(); y++) {
            EXPECT_EQ(mat3.at(x, y), vec1.at(calculateDataIndex(x, y, mat)) - vec1.at(calculateDataIndex(x, y, mat)));
        }
    }
    const std::vector<float> vec3 = randVec(10);
    const std::vector<float> vec4 = randVec(10);
    matrix mat4(2, 5, vec3);
    matrix mat5(2, 5, vec4);
    mat4 = mat4 - mat5;
    for (size_t x = 0; x < mat4.i(); x++) {
        for (size_t y = 0; y < mat4.j(); y++) {
            EXPECT_EQ(mat4.at(x, y), vec3.at(calculateDataIndex(x, y, mat4)) - vec4.at(calculateDataIndex(x, y, mat4)));
        }
    }
}
TEST(matrix, multiplication) {
    const std::vector<float> vec{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4};
    const std::vector<float> vec1{1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    const std::vector<float> resVec1{3, 6, 9, 12, 6, 12, 18, 24, 9, 18, 27, 36, 12, 24, 36, 48};
    const std::vector<float> resVec2(9, 30);
    matrix res2{4, 4, resVec1};
    matrix mat{4, 3, vec};
    matrix mat1{3, 4, vec1};
    matrix res1 = mat * mat1;
    EXPECT_EQ(true, res1 == res2);
    matrix mat2{4, 3, vec};
    matrix mat3{3, 4, vec1};
    matrix res3(3, 3, resVec2);
    mat = mat3 * mat2;
    EXPECT_EQ(true, mat.equalsCout(res3));
    size_t bigI = 100;
    size_t bigJ = 100;
    const std::vector vec3 = randVec((bigI * bigJ));
    matrix A(bigI, bigJ, vec3);
    matrix B(bigJ, bigI, vec3);
    matrix C = A * B;
    matrix D = B * A;
}
TEST(matrix, sigmoid) {
    const std::vector<float> vec{-1, 0, 0.5};
    const std::vector<float> ansVec{0.268941, 0.5, 0.622459};
    matrix mid{3, 1, vec};
    matrix res{3, 1, ansVec};
    matrix calc = mid.sig();
    EXPECT_EQ(true, calc == res);
}
TEST(matrix, sigmoid_dx) {

    const std::vector<float> vec{-1, 0, 0.5};
    const std::vector<float> ansVec{0.196612, 0.25, 0.235004};
    matrix mid{3, 1, vec};
    matrix res{3, 1, ansVec};
    matrix calc = mid.sig_d();
    EXPECT_EQ(true, calc == res);
}
TEST(matrix, transpose) {
    const std::vector<float> startVec{1, 2, 3, 4, 5, 6};
    const std::vector<float> transVec{1, 3, 5, 2, 4, 6};
    matrix mid{3, 2, startVec};
    matrix res{2, 3, transVec};
    mid = mid.transpose();
    EXPECT_EQ(true, mid == res);
    const std::vector<float> vec1 = randVec(2500);
    matrix start(50, 50, vec1);
    matrix middle = start.transpose();
    EXPECT_EQ(false, middle == start);
    matrix end = middle.transpose();
    EXPECT_EQ(true, end == start);
}
