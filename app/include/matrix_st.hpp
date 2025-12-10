#ifndef __MATRIX_ST_INCLUDE_GAURD__
#define __MATRIX_ST_INCLUDE_GAURD__
// Single threaded CPU based implementation of the matrix interface
#include "matrix_config.hpp"
#include <cstddef>
#include <vector>
class Matrix;
class Matrix_ST {

    std::size_t get_m();
    std::size_t get_n();

    // returns false if matrix is not yet initialized
    bool is_initialized();

    Base_t at(std::size_t i, std::size_t j);

    // matrix multiplication terminates if dimensions mismatch
    Matrix &operator*(const Matrix &right);

    // matrix subtraction, terminates if dimensions mismatch
    Matrix &operator+(const Matrix &right);

    // matrix addition, terminates if dimensions mismatch
    Matrix &operator-(const Matrix &right);

    // used to initialize matrix and weights to zero
    void init(std::size_t m, std::size_t n);

    // used to initialize matrix and weights based on a vector of values
    void init(std::size_t m, std::size_t n, const std::vector<Base_t> values);
};
#endif
