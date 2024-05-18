
#ifndef MATRIXLIB
#define MATRIXLIB
#include <cstddef>
#include <random>
#include <vector>
class matrix {
  private:
    std::vector<float> data;
    size_t calculateDataIndex(size_t x, size_t y);

  public:
    const size_t i, j;
    // where i = number of rows, j = number of columns
    matrix(size_t i, size_t j);
    // generates a matrix of given size, using the normal distribution provided
    // where i = number of rows, j = number of columns
    matrix(size_t i, size_t j, std::normal_distribution<float> dist);
    // where i = number of rows, j = number of columns
    matrix(size_t i, size_t j, std::vector<float> &dist);
    // member accesses are zero indexed
    float getMember(size_t x, size_t y);
    // member accesses are zero indexed
    void setMember(size_t x, size_t y);
    matrix sig(const matrix &mat);
    matrix sig_d(const matrix &mat);
    matrix operator+(const matrix &b) const;
    matrix operator*(const matrix &b) const;
};
#endif
