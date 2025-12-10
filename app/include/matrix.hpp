#ifndef __MATRIX_INC_GRD__
#define __MATRIX_INC_GRD__

#include "matrix_config.hpp"
#include "matrix_st.hpp"

#include <cstddef>
#include <vector>

class Matrix {
  private:
    /*Underlying implementation of all matrix instances.  Change this here to
     * suit the application.*/
    using Impl_t = Matrix_ST;
    Impl_t pimpl = ;

  public:
    Matrix() = delete;

    // initializes matrix with default value for all elements
    Matrix(std::size_t m, std::size_t n);

    /* Used to initialize matrix and weights based on a vector of values
     * (row-wise). */
    Matrix(std::size_t m, std::size_t n, const std::vector<Base_t> values);

    std::size_t get_m();
    std::size_t get_n();

    Base_t at(std::size_t i, std::size_t j);

    // matrix multiplication terminates if dimensions are incompatible
    Matrix &operator*(const Matrix &right);

    // matrix subtraction, terminates if dimensions mismatch
    Matrix &operator+(const Matrix &right);

    // matrix addition, terminates if dimensions mismatch
    Matrix &operator-(const Matrix &right);

    // used to initialize matrix and weights to zero
    void init(std::size_t m, std::size_t n);

    // used to initialize matrix and weights based on a vector of values
    // (row-wise)
    void init(std::size_t m, std::size_t n, const std::vector<Base_t> values);

    Matrix(const Matrix &) = default;
    Matrix(Matrix &&) = default;
    Matrix &operator=(const Matrix &) = default;
    Matrix &operator=(Matrix &&) = default;
    ~Matrix() = default;
};

#endif
