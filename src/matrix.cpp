#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <matrix.hpp> // Use (void) to silence unused warnings.
#include <string>
#include <utility>
#define assertm(exp, msg) assert(((void)msg, exp))
constexpr const float COMPARE_MAX_SQUARED_ERROR = 1E-9;
matrix::matrix(size_t i, size_t j) : _i{i}, _j{j} { data = std::vector<float>(_i * _j); }
matrix::matrix(size_t i, size_t j, std::normal_distribution<float> dist) : _i{i}, _j{j} {
    data = std::vector<float>(_i * _j);
    std::random_device rd{};
    std::mt19937 gen{rd()};
    for (float &each : data) {

        each = dist(gen);
    }
}
matrix::matrix(size_t i, size_t j, const std::vector<float> &initData) : _i{i}, _j{j} {
    assertm((this->_i * this->_j) == initData.size(), "Matrix initialization: dimension mismatch i*j is not equal to size of input vector");
    this->data = initData;
}
float &matrix::at(size_t x, size_t y) { return data.at(this->calculateDataIndex(x, y)); }

matrix matrix::sig() const {
    matrix ret{this->_i, this->_j, this->data};
    for (float &each : ret.data) {
        const float exp = std::exp(each);
        each = (exp / (1 + exp));
    }
    return ret;
}
matrix matrix::sig_d() const {

    matrix ret{this->_i, this->_j, this->data};
    for (float &each : ret.data) {
        const float exp = std::exp((each * -1));
        const float denom = (1 + exp);
        each = (exp / (denom * denom));
    }
    return ret;
}
matrix matrix::operator+(const matrix &b) const {
    assertm(this->_i == b._i, "Matrix Addition: dimension mismatch in A+B, i dimension ");
    assertm(this->_j == b._j, "Matrix Addition: dimension mismatch in A+B, j dimension ");
    matrix mat(this->_i, this->_j);
    size_t i{0};
    for (float &each : mat.data) {
        each = this->data.at(i) + b.data.at(i);
        i++;
    }
    return mat;
}

matrix &matrix::operator=(const matrix &b) {
    if (this == &b) {
        return *this;
    }
    this->_i = b._i;
    this->_j = b._j;
    this->data = b.data;
    return *this;
}

matrix matrix::operator-(const matrix &b) const {
    matrix ret{this->_i, this->_j};
    assertm(this->_i == b._i, "Matrix Subtraction: dimension mismatch in A+B, i dimension ");
    assertm(this->_j == b._j, "Matrix Subtraction: dimension mismatch in A+B, j dimension ");
    size_t i = 0;
    for (float &each : ret.data) {
        each = this->data.at(i) - b.data.at(i);
        i++;
    }
    return ret;
}
matrix &matrix::operator=(matrix &&b) {

    if (this == &b) {
        return *this;
    }
    this->_i = b._i;
    this->_j = b._j;
    this->data = std::move(b.data);
    return *this;
};
matrix matrix::operator*(const matrix &b) const {
    assertm(this->_j == b._i, "Matrix Multiplication: A.j != to B.i, in A*B");
    matrix ret(this->_i, b._j);
    std::cout << "\n";
    for (size_t rowA = 0; rowA < this->_i; rowA++) {

        for (size_t colB = 0; colB < b._j; colB++) {
            float currVal = 0;
            for (size_t i = 0; i < this->_j; i++) {
                currVal += this->data.at(calculateDataIndex(rowA, i)) * b.data.at(b.calculateDataIndex(i, colB));
            }
            ret.at(rowA, colB) = currVal;
        }
    }
    return ret;
}
bool matrix::operator==(const matrix &b) const {
    if (b._i != this->_i) {
        return false;
    }
    if (b._j != this->_j) {
        return false;
    }
    size_t i = 0;
    for (const float &each : this->data) {
        if (((each - b.data.at(i)) * (each - b.data.at(i))) > COMPARE_MAX_SQUARED_ERROR) {
            return false;
        }
        i++;
    }
    return true;
}
matrix matrix::transpose() const {
    matrix ret{this->j(), this->i()};
    for (size_t x = 0; x < this->j(); x++) {
        for (size_t y = 0; y < this->i(); y++) {
            ret.at(x, y) = this->data.at(this->calculateDataIndex(y, x));
        }
    }
    return ret;
}
bool matrix::equalsCout(const matrix &b) const {

    if (b._i != this->_i) {
        std::cout << "Failed on i dimension\n";
        return false;
    }
    if (b._j != this->_j) {

        std::cout << "Failed on j dimension\n";
        return false;
    }
    size_t i = 0;
    for (const float &each : this->data) {
        if (((each - b.data.at(i)) * (each - b.data.at(i))) > COMPARE_MAX_SQUARED_ERROR) {

            std::cout << "Failed on compare, A = " << each << " B = " << b.data.at(i) << "\n";
            return false;
        }
        i++;
    }
    return true;
}
size_t matrix::calculateDataIndex(size_t x, size_t y) const {
    assertm(x < this->_i, "Matrix index out of range: x");
    assertm(y < this->_j, "Matrix index out of range: y");
    return (this->_j * x) + y;
}
void matrix::coutMatDims(const std::string &name) const {
    size_t mem = sizeof(float) * this->data.size();
    std::string memString;
    memString = (mem < 1E3) ? (std::to_string(mem) + " B") : "";
    memString = (mem >= 1E3) ? (std::to_string(static_cast<float>(mem) / 1E3) + " KB") : memString;
    memString = (mem >= 1E6) ? (std::to_string(static_cast<float>(mem) / 1E6) + " MB") : memString;
    std::cout << "Matrix " << name << " Dimensions: " << _i << " , " << _j << " n: " << (_j * _i) << " Memory usage " << memString << "\n";
}
void matrix::coutMat(const std::string &name) const {
    this->coutMatDims(name);
    for (size_t x = 0; x < this->_i; x++) {
        std::string currLine = "";
        for (size_t y = 0; y < this->_j; y++) {
            currLine += std::to_string(this->data.at(calculateDataIndex(x, y))) + " ";
        }
        std::cout << currLine << "\n";
    }
}
size_t matrix::i() const { return this->_i; }
size_t matrix::j() const { return this->_j; }
