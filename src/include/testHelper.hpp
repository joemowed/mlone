#ifndef TESTINGHELPERS
#define TESTINGHELPERS
#include <gtest/gtest.h>
#include <matrix.hpp>

// compares two matrices value for value

#define assertm(exp, msg) assert(((void)msg, exp))

inline void matrixWalker(matrix &mat, matrix &mat2) {
    assertm(!(mat.j == mat2.j && mat.i == mat.j), "Testing: matrixWalker dimension mismatch");
    for (size_t x = 0; x < mat.i; x++) {
        for (size_t y = 0; y < mat.j; y++) {
            EXPECT_EQ(mat.getMember(x, y), mat2.getMember(x, y));
        }
    }
}
// compares every value in matrix against the same given value
inline void matrixWalker(matrix &mat, float compare) {
    for (size_t x = 0; x < mat.i; x++) {
        for (size_t y = 0; y < mat.j; y++) {
            EXPECT_EQ(mat.getMember(x, y), compare);
        }
    }
}
#endif
