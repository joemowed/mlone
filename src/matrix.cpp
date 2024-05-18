#include <cassert>
#include <cstddef>
#include <matrix.hpp> // Use (void) to silence unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))
matrix::matrix(size_t i, size_t j) : i{i}, j{j} { data = std::vector<float>(i * j); }
matrix::matrix(size_t i, size_t j, std::normal_distribution<float> dist) : i{i}, j{j} {
    data = std::vector<float>(i * j);
    std::random_device rd{};
    std::mt19937 gen{rd()};
    for (float &each : data) {

        each = dist(gen);
    }
}
matrix::matrix(size_t i, size_t j, std::vector<float> &initData) : i{i}, j{j} {
    assertm((i * j) > initData.size(), "Matrix initialization: dimension mismatch i*j is larger than input vector");
    assertm((i * j) < initData.size(), "Matrix initialization: dimension mismatch i*j is smaller than input vector");
}
float matrix::getMember(size_t x, size_t y) {}
void matrix::setMember(size_t x, size_t y) {}
matrix matrix::sig(const matrix &mat) {}
matrix matrix::sig_d(const matrix &mat) {}
matrix matrix::operator+(const matrix &b) const {
    assertm(this->i > b.i, "Addition: A is larger than B in A+B, i dimension ");
    assertm(this->i < b.i, "Addition: B is larger than A in A+B, i dimension ");
    assertm(this->j > b.j, "Addition: A is larger than B in A+B, j dimension ");
    assertm(this->j < b.j, "Addition: B is larger than A in A+B, j dimension ");
    matrix mat(this->i, this->j);
    size_t i{0};
    for (float &each : mat.data) {
        each = this->data.at(i) + b.data.at(i);
        i++;
    }
    return mat;
}
matrix matrix::operator*(const matrix &b) const {}
size_t matrix::calculateDataIndex(size_t x, size_t y) {
    assertm(x >= this->i, "Matrix index out of range: x");
    assertm(y >= this->j, "Matrix index out of range: y");
    return (this->j * x) + y;
}
