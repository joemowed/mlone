#include "matrix_st.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>

#if MATRIX_IMPL == MATRIX_IMPL_CPU_ST_VALUE

std::size_t Matrix::get_m() const { return this->m; }
std::size_t Matrix::get_n() const { return this->n; }

Matrix::Base_t &Matrix::at(std::size_t i, std::size_t j) {
    return data.at(calculate_vec_index(i, j));
}

// matrix multiplication terminates if dimensions mismatch
Matrix Matrix::operator*(const Matrix &right) const {}

// matrix subtraction, terminates if dimensions mismatch
Matrix Matrix::operator+(const Matrix &right) const {
    if (!this->has_equal_dimensions(right)) {
        std::cerr << "Matrix addition failed, matrix dimensions mismatch.\n"
                  << "Dimensions: (" << get_m() << "x" << get_n() << ") + ("
                  << right.get_m() << "x" << right.get_n() << ")" << std::endl;
        throw std::invalid_argument(
            "Matrix addtion failed, matrix dimensions mismatch.");
    }

    auto lambda = [](const Base_t &a, const Base_t &b) { return a + b; };

    return transform(right, lambda);
}

// matrix addition, terminates if dimensions mismatch
Matrix Matrix::operator-(const Matrix &right) const {

    if (!this->has_equal_dimensions(right)) {
        std::cerr << "Matrix subtraction failed, matrix dimensions mismatch.\n"
                  << "Dimensions: (" << get_m() << "x" << get_n() << ") + ("
                  << right.get_m() << "x" << right.get_n() << ")" << std::endl;
        throw std::invalid_argument(
            "Matrix subtraction failed, matrix dimensions mismatch.");
    }

    auto lambda = [](const Base_t &a, const Base_t &b) { return a - b; };

    return transform(right, lambda);
}

// used to initialize matrix and weights to zero
Matrix::Matrix(const std::size_t m, const std::size_t n) {
    if ((m <= 0) || (n <= 0)) {
        std::cerr << "Matrix initilization failed, matrix dimensions invalid. "
                  << "Dimensions: (" << m << "x" << n << ")" << std::endl;
        throw std::invalid_argument(
            "Matrix initilization failed, matrix dimensions invalid.");
    }
    this->m = m;
    this->n = n;
    this->data.resize(m * n);
}

// used to initialize matrix and weights based on a vector of values
Matrix::Matrix(const std::size_t m, const std::size_t n,
               const std::vector<Base_t> values)
    : Matrix(m, n) {
    if (m * n != values.size()) {
        std::cerr << "Matrix initialization failed, vector of values does not "
                     "match matrix dimensions.\n"
                  << "Matrix size: " << m << "x" << n << " (" << m * n
                  << " total elements)\n"
                  << "Vector size: " << values.size() << " elements"
                  << std::endl;
        throw std::invalid_argument(
            "Matrix initialization vector size does not match matrix size.");
    }
    this->data = values;
}

// calculates the vector index given the indices (i,j) from the matrix
std::size_t Matrix::calculate_vec_index(const std::size_t i,
                                        const std::size_t j) const {
    bounds_check(i, j);

    /*Row first storage.  The minus ones are because matrix is 1-indexed and
     * vector is 0-indexed.*/
    return j - 1 + ((i - 1) * get_n());
}

/*checks that bounds fall within matrix dimensions, and terminates program
 * if they do not.*/
void Matrix::bounds_check(const std::size_t i, const std::size_t j) const {
    const bool is_over = ((i > get_m()) || (j > get_n()));
    const bool is_under = ((i <= 0) || (j <= 0));
    if (is_over || is_under) {
        std::cerr << "Matrix bounds out of range.\n"
                  << "Matrix size: (" << get_m() << "," << get_n()
                  << ") Attempted access: (" << i << "," << j << ")"
                  << std::endl;
        throw std::out_of_range("Matrix access out of bounds.");
    }
    return;
}

bool Matrix::operator==(const Matrix &right) const {
    if (!this->has_equal_dimensions(right)) {
        return false;
    }
    if (this->data != right.data) {
        return false;
    }
    return true;
}

bool Matrix::has_equal_dimensions(const Matrix &mat) const {
    if (this->get_m() != mat.get_m()) {
        return false;
    }
    if (this->get_n() != mat.get_n()) {
        return false;
    }
    return true;
}

void Matrix::init_with_move(std::vector<Base_t> &values) {

    if ((get_m() * get_n()) != values.size()) {
        std::cerr
            << "Matrix initialization with move failed, matrix dimensions "
               "invalid. "
            << "Dimensions: (" << m << "x" << n << ")" << std::endl;
        throw std::invalid_argument("Matrix initialization with move failed, "
                                    "matrix dimensions invalid.");
    }
    this->data = std::move(values);
}

void Matrix::init_with_move(const std::size_t m, const std::size_t n,
                            std::vector<Base_t> &values) {
    if ((m <= 0) || (n <= 0)) {
        std::cerr << "Matrix initialization with move failed, matrix "
                     "dimensions invalid. "
                  << "Dimensions: (" << m << "x" << n << ")" << std::endl;
        throw std::invalid_argument("Matrix initialization with move failed, "
                                    "matrix dimensions invalid.");
    }

    this->m = m;
    this->n = n;
    this->data = std::move(values);
}
template <typename Functor>
Matrix Matrix::transform(const Matrix &right, Functor &binary_op) const {

    std::vector<Base_t> values(get_m() * get_n());
    Matrix ret(get_m(), get_n());

    auto this_begin = data.begin();
    auto this_end = data.end();
    auto right_begin = right.data.begin();
    auto result_begin = values.begin();

    // do the operation element-wise on the vectors
    std::transform(this_begin, this_end, right_begin, result_begin, binary_op);

    // move the values into the return matrix
    ret.init_with_move(values);

    return ret;
}

Matrix Matrix::transpose() const {

    std::vector<Base_t> values_T(data.size());
    const std::size_t m = get_m();
    const std::size_t n = get_n();

    for (std::size_t i = 0; i < m * n; i++) {
        const std::size_t transposed_idx = (i % n) * m + (i / n);
        values_T.at(transposed_idx) = data.at(i);
    }

    Matrix ret{};
    ret.init_with_move(n, m, values_T);
    return ret;
}
#endif
