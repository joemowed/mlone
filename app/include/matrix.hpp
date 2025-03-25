#ifndef __MATRIX_INC_GRD__
#define __MATRIX_INC_GRD__

#include <cstddef>
#include <vector>

class Matrix {
  private:
    using T = float;
    const std::size_t I; // number of rows
    const std::size_t J; // number of cols
    std::vector<T> data;

    // asserts indexes are valid
    // and returns the index of the requested value within the data array
    std::size_t calculateIndex(std::size_t i, std::size_t j);

  public:
    Matrix(std::size_t I, std::size_t J);
    Matrix(std::size_t I, std::size_t J, const std::vector<T> &vec);
    std::size_t getI() const;
    std::size_t getJ() const;
    T &at(std::size_t I, std::size_t J);
};

#endif
