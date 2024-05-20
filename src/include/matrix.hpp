
#ifndef MATRIXLIB
#define MATRIXLIB
#include <cstddef>
#include <random>
#include <string>
#include <vector>
class matrix {
  private:
    std::vector<float> data;
    size_t calculateDataIndex(size_t x, size_t y) const;

    size_t _i, _j;

  public:
    matrix &operator=(const matrix &);
    matrix &operator=(matrix &&);
    ~matrix() = default;
    matrix(const matrix &) = default;
    matrix(matrix &&) = default;
    // where i = number of rows, j = number of columns
    matrix(size_t i, size_t j);
    // generates a matrix of given size, using the normal distribution provided
    // where i = number of rows, j = number of columns
    matrix(size_t i, size_t j, std::normal_distribution<float> dist);
    // where i = number of rows, j = number of columns
    matrix(size_t i, size_t j, const std::vector<float> &dist);
    // member accesses are zero indexed
    float &at(size_t x, size_t y);
    // member accesses are zero indexed
    matrix sig() const;
    matrix hadMult(const matrix &b) const;
    matrix sig_d() const;
    matrix multiplyByConstant(float b) const;
    matrix operator+(const matrix &b) const;
    matrix operator*(const matrix &b) const;
    matrix operator-(const matrix &b) const;
    matrix transpose() const;
    bool operator==(const matrix &b) const;
    bool equalsCout(const matrix &b) const;
    void coutMatDims(const std::string &name) const;
    void coutMat(const std::string &name) const;
    size_t i() const;
    size_t j() const;
};
#endif
