#ifndef __MATRIX_ST_INCLUDE_GAURD__
#define __MATRIX_ST_INCLUDE_GAURD__
// Single threaded CPU based implementation of the matrix interface
#include "matrix_config.hpp"
#include <cstddef>
#include <vector>
class Matrix;
class Matrix_ST {
  public:
    std::size_t get_m() const;
    std::size_t get_n() const;

    Base_t &at(const std::size_t i, const std::size_t j);

    // matrix multiplication terminates if dimensions mismatch
    Matrix *operator*(const Matrix &right);

    // matrix subtraction, terminates if dimensions mismatch
    Matrix *operator+(const Matrix &right);

    // matrix addition, terminates if dimensions mismatch
    Matrix *operator-(const Matrix &right);

    // used to initialize matrix and weights to zero
    void init(const std::size_t m, const std::size_t n);

    // used to initialize matrix and weights based on a vector of values
    void init(const std::size_t m, const std::size_t n,
              const std::vector<Base_t> values);

  private:
    std::size_t m = 0;
    std::size_t n = 0;
    bool is_initialized = false;

    std::vector<Base_t> data;

    // calculates the vector index given the indices (i,j) from the matrix
    std::size_t calculate_vec_index(const std::size_t i,
                                    const std::size_t j) const;

    /*checks that bounds fall within matrix dimensions, and terminates program
     * if they do not.*/
    void bounds_check(const std::size_t i, const std::size_t j) const;
};
#endif
