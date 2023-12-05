#ifndef MATRIX_H
#define MATRIX_H
#include <array>
#include <cstddef>
#include <sys/types.h>
#include <vector>
struct rowSpan {
  float *const start;
  const std::size_t last;
};
template <std::size_t colSize, std::size_t rowSize> class matrix {
  static_assert(rowSize >= 0, "row size too small");
  static_assert(colSize >= 0, "column size too small");

private:
  std::array<float, colSize * rowSize> data;

public:
  matrix() {}
  rowSpan getRow(const unsigned int &rowIndex) {
    rowSpan ret = {data.data() + (rowIndex * rowSize), rowSize - 1};
    return ret;
  }
  std::vector<float> getCol(const unsigned int &colIndex) {
    std::vector<float> ret;
    for (unsigned int i = colIndex; i <= rowSize * colSize; i += (rowSize)) {
      ret.push_back(data[i]);
    }
    return ret;
  }
  float &getValue(const unsigned int &rowIndex, const unsigned int &colIndex) {
    return data[rowIndex * rowSize + colIndex];
  }
  void setValue(const unsigned int &rowIndex, const unsigned int &colIndex,
                const float &value) {
    data[rowIndex * rowSize + colIndex] = value;
  }
};

#endif // include gaurd
