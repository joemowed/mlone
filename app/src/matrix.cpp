#include <cassert>
#include <debug.hpp>
#include <matrix.hpp>

Matrix::Matrix(std::size_t I, std::size_t J) : I(I), J(J) {
    this->data.resize(I * J, 0);
}

Matrix::Matrix(std::size_t I, std::size_t J, const std::vector<T> &vec)
    : I(I), J(J) {
    this->data.resize(I * J, 0);
    if constexpr (debug::MATRIX_ASSERT_EN) {
        assert(vec.size() == (I * J) &&
               "Matrix cannot be instantiated from the "
               "given vector, dimension mismatch.");
    }
    this->data = vec;
}

// returns lvalue refernce of the requested item
Matrix::T &Matrix::at(std::size_t i, std::size_t j) {
    if constexpr (debug::MATRIX_ASSERT_EN) {
        assert((i <= this->I) &&
               "Invalid row query for matrix, i is larger than "
               "number of rows in matrix.");
        assert((j <= this->J) &&
               "Invalid row query for matrix, j is larger than "
               "number of columns in matrix.");
        assert((i >= 1) && "Invalid row query for matrix, i is less than 0.");
        assert((j >= 1) && "Invalid row query for matrix, j is less than 0.");
    }
    return this->data.at(this->calculateIndex(i, j));
}

// the values i and j must be validated before calling this function
// this function performs no validation
std::size_t Matrix::calculateIndex(std::size_t i, std::size_t j) {
    std::size_t ret = 0;
    ret += (this->J * (i - 1));
    ret += j - 1;
    return ret;
}
