#ifndef __MATRIX_INC_GRD__
#define __MATRIX_INC_GRD__

#include <cstddef>
#include <vector>

class Matrix {
  private:
    using T = float;
    const std::size_t M; // number of rows (length of col)
    const std::size_t N; // number of cols (length of row)
    std::vector<T> data;

    // asserts indexes are valid
    // and returns the index of the requested value within the data array
    std::size_t calculateIndex(std::size_t i, std::size_t j);

  public:
    Matrix(std::size_t I, std::size_t J);
    Matrix(std::size_t I, std::size_t J, const std::vector<T> &vec);
    Matrix(std::size_t I, std::size_t J,
           const std::vector<std::vector<T>> &vec);
    // number of rows (length of col)
    std::size_t getM() const;
    // number of cols (length of row)
    std::size_t getN() const;
    T &at(std::size_t I, std::size_t J);
};

#endif
