#ifndef __MATRIX_INC_GRD__
#define __MATRIX_INC_GRD__
#include <cstddef>
#include <vector>

/* Interface class for matrix supporting basic matrix operations.  Matrices
 * must be initialized before use, the constructor does not initialize the
 * matrix into a usable form. Attempting operations on a uninitialized matrix
 * will cause the program to terminate.*/
class Matrix {
  protected:
    /* Underlying datatype of all matrix instances.  Change this here to suit
     * the application */
    using Base_t = float;

  public:
    Matrix() = default;
    Matrix(const Matrix &) = default;
    Matrix(Matrix &&) = default;
    Matrix &operator=(const Matrix &) = default;
    Matrix &operator=(Matrix &&) = default;
    virtual ~Matrix() = 0;

    virtual std::size_t get_m() = 0;
    virtual std::size_t get_n() = 0;

    // returns false if matrix is not yet initialized
    virtual bool is_initialized() = 0;

    virtual Base_t at(std::size_t i, std::size_t j) = 0;

    // matrix multiplication terminates if dimensions mismatch
    virtual Matrix &operator*(const Matrix &right) = 0;

    // matrix subtraction, terminates if dimensions mismatch
    virtual Matrix &operator+(const Matrix &right) = 0;

    // matrix addition, terminates if dimensions mismatch
    virtual Matrix &operator-(const Matrix &right) = 0;

    // used to initialize matrix and weights to zero
    virtual void init(std::size_t m, std::size_t n) = 0;

    // used to initialize matrix and weights based on a vector of values
    virtual void init(std::size_t m, std::size_t n,
                      const std::vector<Base_t> values) = 0;
};

#endif
