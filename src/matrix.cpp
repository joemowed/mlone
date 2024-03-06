#include <algorithm>
#include <bits/fs_fwd.h>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <matrix.hpp>
#include <vector>
matrix::matrix(const matrixDimensions dims, const std::vector<float> vecData) : dimensions(dims) {

    assert(vecData.size() % dims.cols == 0 && vecData.size() % dims.rows == 0 && "Matrix init via vector requires vector size to be integer multiple  of matrix dimensions");
    data = vecData;
}
matrix::matrix(const matrixDimensions dims) : dimensions(dims) { data.resize(dimensions.rows * dimensions.cols); }
float matrix::getMember(int x, int y) {
    if (false) {
        std::cout << "x,y " << x << "," << y << " dims: " << dimensions.rows << "," << dimensions.cols << std::endl;
    }
    assert(((y * dimensions.cols) + x) < data.size() && "Matrix getMember out of index on get");
    return data.at((dimensions.cols * y) + x);
}

void matrix::setMember(int x, int y, float value) {
    assert(((y * dimensions.cols) + x) < data.size() && "Matrix set member out of index on set");
    data.at((dimensions.cols * y) + x) = value;
}
void matrix::coutMat() {
    int i = 1;
    for (const float &each : data) {
        std::cout << each << " ";
        if (i % dimensions.cols == 0) {
            std::cout << std::endl;
        }
        i++;
    }
}

matrixDimensions matrix::getDimensions() { return dimensions; }
void matrix::transpose() {
    std::vector<float> newData;
    newData.resize(dimensions.cols * dimensions.rows);
    for (int y = 0; y < dimensions.rows; y++) {
        for (int x = 0; x < dimensions.cols; x++) {
            newData.at((x * dimensions.rows) + y) = getMember(x, y);
        }
    }
    const uint32_t rows = dimensions.rows;
    const uint32_t cols = dimensions.cols;

    dimensions.rows = cols;
    dimensions.cols = rows;
    data = newData;
}
void matrix::relu() {
    for (auto &each : data) {
        each = std::max<float>(0, each);
    }
}
matrix matrix::operator*(matrix &rightMat) {
    matrixDimensions dims = {.rows = dimensions.rows, .cols = rightMat.dimensions.cols};
    assert((dimensions.cols == rightMat.dimensions.rows) && "matrix multiply dimension mismatch");
    matrix ret = matrix(dims);
    for (int y = 0; y < ret.getDimensions().rows; y++) {
        for (int x = 0; x < ret.getDimensions().cols; x++) {
            float res = 0;
            for (int additionIter = 0; additionIter < dimensions.cols; additionIter++) {
                res += (getMember(additionIter, y) * rightMat.getMember(x, additionIter));
            }
            ret.setMember(x, y, res);
        }
    }
    return ret;
}
void matrix::sigmoid() {
    for (float &each : data) {
        each = (1 / (1 + expf(-1.0 * each)));
    }
}

void matrix::sigmoid_dx() {
    sigmoid();
    for (float &each : data) {
        each = each * (1 - each);
    }
}

matrix::~matrix() {}
