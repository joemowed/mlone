#include "matrix_st.hpp"
#include <cstdlib>
#include <iostream>

std::size_t Matrix_ST::get_m() const { return this->m; }
std::size_t Matrix_ST::get_n() const { return this->n; }

Base_t &Matrix_ST::at(std::size_t i, std::size_t j) {
    if (!is_initialized) {
        std::cerr << "Attempt to call \"at(i,j)\" on uninitialized matrix"
                  << std::endl;
        std::abort();
    }
    return data.at(calculate_vec_index(i, j));
}

// matrix multiplication terminates if dimensions mismatch
Matrix &Matrix_ST::operator*(const Matrix &right) {}

// matrix subtraction, terminates if dimensions mismatch
Matrix &Matrix_ST::operator+(const Matrix &right) {}

// matrix addition, terminates if dimensions mismatch
Matrix &Matrix_ST::operator-(const Matrix &right) {}

// used to initialize matrix and weights to zero
void Matrix_ST::init(const std::size_t m, const std::size_t n) {
    // terminate if matrix is already initialized
    if (is_initialized) {
        std::cerr << "Matrix initilization failed, matrix already initialized"
                  << std::endl;
        std::abort();
    }
    this->m = m;
    this->n = n;
    this->is_initialized = true;
}

// used to initialize matrix and weights based on a vector of values
void Matrix_ST::init(const std::size_t m, const std::size_t n,
                     const std::vector<Base_t> values) {
    if (m * n != values.size()) {
        std::cerr << "Matrix initialization failed, vector of values does not "
                     "match matrix dimensions.\n"
                  << "Matrix size: " << m << "x" << n << " (" << m * n
                  << " total elements)\n"
                  << "Vector size: " << values.size() << " elements"
                  << std::endl;
        std::abort();
    }
    this->data = values;
    this->init(m, n);
}

// calculates the vector index given the indices (i,j) from the matrix
std::size_t Matrix_ST::calculate_vec_index(const std::size_t i,
                                           const std::size_t j) const {
    bounds_check(i, j);

    /*Row first storage.  The minus ones are because matrix is 1-indexed and
     * vector is 0-indexed.*/
    return j - 1 + ((i - 1) * get_n());
}

/*checks that bounds fall within matrix dimensions, and terminates program
 * if they do not.*/
void Matrix_ST::bounds_check(const std::size_t i, const std::size_t j) const {
    const bool is_over = ((i > get_m()) || (j > get_n()));
    const bool is_under = ((i <= 0) || (j <= 0));
    if (is_over || is_under) {
        std::cerr << "Matrix bounds out of range.\n"
                  << "Matrix size: (" << get_m() << "," << get_n()
                  << ") Attempted access: (" << i << "," << j << ")"
                  << std::endl;
        std::abort();
    }
    return;
}
