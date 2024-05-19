#ifndef TESTINGHELPERS
#define TESTINGHELPERS
#include <gtest/gtest.h>
#include <matrix.hpp>
#include <random>
#include <vector>

// compares two matrices value for value

#define assertm(exp, msg) assert(((void)msg, exp))

inline void matrixWalker(matrix &mat, matrix &mat2) {
    assertm((mat.j() == mat2.j() && mat.i() == mat.j()), "Testing: matrixWalker dimension mismatch");
    for (size_t x = 0; x < mat.i(); x++) {
        for (size_t y = 0; y < mat.j(); y++) {
            EXPECT_EQ(mat.at(x, y), mat2.at(x, y));
        }
    }
}
// compares every value in matrix against the same given value
inline void matrixWalker(matrix &mat, float compare) {
    for (size_t x = 0; x < mat.i(); x++) {
        for (size_t y = 0; y < mat.j(); y++) {
            EXPECT_EQ(mat.at(x, y), compare);
        }
    }
}
inline size_t calculateDataIndex(size_t x, size_t y, matrix mat) {
    assertm(x < mat.i(), "Matrix index out of range: x");
    assertm(y < mat.j(), "Matrix index out of range: y");
    return (mat.j() * x) + y;
}
inline std::vector<float> randVec(size_t n) {
    std::vector<float> ret(n);
    std::normal_distribution<float> dist{0, 1};
    std::random_device rd{};
    std::mt19937 gen{rd()};
    for (float &each : ret) {

        each = dist(gen);
    }
    return ret;
}
#endif
