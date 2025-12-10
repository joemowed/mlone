#include "matrix.hpp"

Matrix::Matrix(std::size_t m, std::size_t n) { this->impl.init(m, n); }

Matrix::Matrix(std::size_t m, std::size_t n, const std::vector<Base_t> values) {
    this->impl.init(m, n, values);
}

std::size_t Matrix::get_m() { return this->impl.get_m(); }
std::size_t Matrix::get_n() { return this->impl.get_n(); }
Base_t Matrix::at(std::size_t i, std::size_t j) { return this->impl.at(i, j); }
Matrix &Matrix::operator*(const Matrix &right) { return this->impl * right; }
Matrix &Matrix::operator+(const Matrix &right) { return this->impl + right; }
Matrix &Matrix::operator-(const Matrix &right) { return this->impl - right; }
