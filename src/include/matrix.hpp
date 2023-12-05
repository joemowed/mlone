#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdatomic.h>
#include <vector>
template <std::size_t rowSize, std::size_t colSize> class matrix {
private:
  std::vector<float> matrixData;
  std::size_t flattenIndex(const std::size_t &rowIndex,
                           const std::size_t &colIndex) {
    // std::cout << "rowIndex is " << rowIndex << " , " << colIndex <<
    // std::endl; std::cout << "size is " << rowSize << " , " << colSize <<
    // std::endl;
    assert(rowIndex < colSize);
    assert(colIndex < rowSize);
    return rowIndex * rowSize + colIndex;
  }

public:
  matrix() { matrixData.resize(rowSize * colSize, 0); };

  void setValue(const std::size_t &rowIndex, const std::size_t &colIndex,
                const float &value) {
    matrixData.at(flattenIndex(rowIndex, colIndex)) = value;
  }
  float &getValue(const std::size_t &rowIndex, const std::size_t &colIndex) {
    return matrixData.at(flattenIndex(rowIndex, colIndex));
  }
  void dumpCout() {
    std::cout << "\nsize is: " << rowSize << " , " << colSize << std::endl;
    for (std::size_t rowIndex = 0; rowIndex < colSize; rowIndex++) {
      for (std::size_t colIndex = 0; colIndex < rowSize; colIndex++) {
        std::cout << matrixData.at(flattenIndex(rowIndex, colIndex)) << " ";
      }
      std::cout << std::endl;
    }

    std::cout << std::endl;
  }
};
namespace MOP {
template <std::size_t bRowSize, std::size_t sharedSize, std::size_t aColSize>
void multiply(const std::unique_ptr<matrix<sharedSize, aColSize>> &A,
              const std::unique_ptr<matrix<bRowSize, sharedSize>> &B,
              const std::unique_ptr<matrix<bRowSize, aColSize>> &dest) {
  for (std::size_t aCurrRow = 0; aCurrRow < aColSize; aCurrRow++) {
    for (std::size_t bCurrCol = 0; bCurrCol < bRowSize; bCurrCol++) {
      float sum = 0;
      for (std::size_t dotIter = 0; dotIter < sharedSize; dotIter++) {
        sum += A->getValue(aCurrRow, dotIter) * B->getValue(dotIter, bCurrCol);
      }
      dest->setValue(aCurrRow, bCurrCol, sum);
    }
  }
}
} // namespace MOP
