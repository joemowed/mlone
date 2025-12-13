#include "matrix_st.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>

#if MATRIX_IMPL == MATRIX_IMPL_CPU_ST_VALUE

std::size_t Matrix::get_m() const { return this->m; }
std::size_t Matrix::get_n() const { return this->n; }

Matrix::Base_t &Matrix::at(std::size_t i, std::size_t j) {
    bounds_check(i, j);
    return data.at(calculate_vec_index(get_n(), i, j));
}

// matrix multiplication terminates if dimensions mismatch
Matrix Matrix::operator*(const Matrix &right) const {
    /* Multiplies left(m x n) with right(n x p) matrix to produce result(m x p)
     * matrix.  Transposes right(n x p) to improve cache locality.*/
    const std::size_t m = get_m();
    const std::size_t n = get_n();
    const std::size_t p = right.get_n();

    bool is_dimensions_valid = (n == right.get_m());
    if (!is_dimensions_valid) {
        throw_binary_mismatch_dims(right, "multiplication");
    }

    std::vector<Base_t> values(m * p);
    Matrix right_T = right.transpose();

    for (std::size_t i = 1; i <= m; ++i) {
        for (std::size_t j = 1; j <= p; ++j) {
            Base_t sum = 0;
            for (std::size_t k = 1; k <= n; ++k) {
                const Base_t curr_left = data.at(calculate_vec_index(n, i, k));
                const Base_t curr_right =
                    right_T.data.at(calculate_vec_index(n, j, k));
                sum += curr_left * curr_right;
            };
            const std::size_t result_idx = calculate_vec_index(p, i, j);
            values.at(result_idx) = sum;
        }
    }
    Matrix mat{};
    mat.init_with_move(get_m(), right.get_n(), values);
    return mat;
}

// matrix subtraction, terminates if dimensions mismatch
Matrix Matrix::operator+(const Matrix &right) const {
    if (!this->has_equal_dimensions(right)) {
        throw_binary_mismatch_dims(right, "addition");
    }

    auto lambda = [](const Base_t &a, const Base_t &b) { return a + b; };

    return transform(right, lambda);
}

// matrix addition, terminates if dimensions mismatch
Matrix Matrix::operator-(const Matrix &right) const {

    if (!this->has_equal_dimensions(right)) {
        throw_binary_mismatch_dims(right, "subtraction");
    }

    auto lambda = [](const Base_t &a, const Base_t &b) { return a - b; };

    return transform(right, lambda);
}

// used to initialize matrix and weights to zero
Matrix::Matrix(const std::size_t m, const std::size_t n) {
    if ((m <= 0) || (n <= 0)) {
        throw_invalid_dims(m, n, "initilization");
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

std::size_t Matrix::calculate_vec_index(const std::size_t n,
                                        const std::size_t i,
                                        const std::size_t j) const {

    /*Row first storage.  The minus ones are because matrix is 1-indexed and
     * vector is 0-indexed.*/
    return j - 1 + ((i - 1) * n);
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
        throw_invalid_dims(m, n, "initialization with move");
    }
    this->data = std::move(values);
}

void Matrix::init_with_move(const std::size_t m, const std::size_t n,
                            std::vector<Base_t> &values) {
    if ((m <= 0) || (n <= 0)) {
        throw_invalid_dims(m, n, "initialization with move");
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

void Matrix::throw_binary_mismatch_dims(
    const Matrix &right, const std::string &attempted_operation) const {
    std::string error_reason = "Matrix " + attempted_operation +
                               " failed, matrix dimensions mismatch.";

    std::cerr << error_reason << "Dimensions: (" << get_m() << "x" << get_n()
              << ") + (" << right.get_m() << "x" << right.get_n() << ")"
              << std::endl;
    throw std::invalid_argument(error_reason);
}

void Matrix::throw_invalid_dims(std::size_t m, std::size_t n,
                                const std::string &attempted_operation) const {
    std::string error_reason = "Matrix " + attempted_operation +
                               " failed, matrix dimensions invalid. ";

    std::cerr << error_reason << "Dimensions: (" << m << "x" << n << ")"
              << std::endl;
    throw std::invalid_argument(error_reason);
}
Matrix Matrix::scale(const Base_t &scalar) const {
    auto mult_by_scalar = [&scalar](const Base_t value) {
        return value * scalar;
    };
    std::vector<Base_t> scaled_values(get_m() * get_n());
    std::transform(data.begin(), data.end(), scaled_values.begin(),
                   mult_by_scalar);
    Matrix ret{};
    ret.init_with_move(get_m(), get_n(), scaled_values);
    return ret;
}
Matrix Matrix::had(const Matrix &right) const {
    if (!this->has_equal_dimensions(right)) {
        throw_binary_mismatch_dims(right, "hadamard product");
    }
    return transform(right, std::multiplies<Base_t>{});
}
#endif
