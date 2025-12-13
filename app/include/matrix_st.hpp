#ifndef _MATRIX_ST_INCLUDE_GAURD_
#define _MATRIX_ST_INCLUDE_GAURD_
// Single threaded CPU based implementation of the matrix interface
#include <cstddef>
#include <string>
#include <vector>
class Matrix {
  public:
    // base type used by implementation of matrix
    using Base_t = float;

    // initializes matrix with default value for all elements
    Matrix(std::size_t m, std::size_t n);

    /* Used to initialize matrix and weights based on a vector of values
     * (row-wise). */
    Matrix(std::size_t m, std::size_t n, const std::vector<Base_t> values);

    std::size_t get_m() const;
    std::size_t get_n() const;

    Base_t &at(std::size_t i, std::size_t j);

    // matrix multiplication terminates if dimensions are incompatible
    Matrix operator*(const Matrix &right) const;

    bool operator==(const Matrix &right) const;

    // matrix multiplication with a scalar
    Matrix scale(const Base_t &scalar) const;

    // matrix Hadamard product
    Matrix had(const Matrix &right) const;

    Matrix transpose() const;

    // matrix subtraction, terminates if dimensions mismatch
    Matrix operator+(const Matrix &right) const;

    // matrix addition, terminates if dimensions mismatch
    Matrix operator-(const Matrix &right) const;

  private:
    std::size_t m = 0;
    std::size_t n = 0;

    std::vector<Base_t> data;

    /* calculates the vector index given the indices (i,j) and dimensions (m,n)
     * of the matrix*/
    std::size_t calculate_vec_index(const std::size_t n, const std::size_t i,
                                    const std::size_t j) const;

    /*checks that bounds fall within matrix dimensions, and terminates program
     * if they do not. */
    void bounds_check(const std::size_t i, const std::size_t j) const;

    /* returns true if the matrix has equal dimensions to itself, false
     * otherwise. */
    bool has_equal_dimensions(const Matrix &mat) const;

    // used internally to move data from a vector into a matrix
    void init_with_move(std::vector<Base_t> &values);
    void init_with_move(const std::size_t m, const std::size_t n,
                        std::vector<Base_t> &values);

    // used to create matrix without allocating memory for it
    Matrix() = default;

    /* Performs element-wise transformation with another matrix, returning the
     * result as a new matrix. */
    template <typename Functor>
    Matrix transform(const Matrix &right, Functor &binary_op) const;

    void
    throw_binary_mismatch_dims(const Matrix &right,
                               const std::string &attempted_operation) const;
    void throw_invalid_dims(const std::size_t m, const std::size_t n,
                            const std::string &attempted_operation) const;
};
#endif
