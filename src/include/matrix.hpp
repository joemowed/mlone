#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

template <std::size_t rowSize, std::size_t colSize> class matrix {
private:
  std::size_t flattenIndex(const std::size_t &rowIndex,
                           const std::size_t &colIndex) {
    assert(rowIndex < colSize);
    assert(colIndex < rowSize);
    return rowIndex * rowSize + colIndex;
  }

public:
  std::vector<float> matrixData;
  matrix() { matrixData.resize(rowSize * colSize, 0); };
  matrix(const matrix<rowSize, colSize> &t) { matrixData = t.matrixData; }
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

const std::size_t MULTIPLY_TRANS_OPTIMIZATION_SIZE = 1;
const std::size_t MULTIPLY_TRANS_THREADS = 10;
template <std::size_t originRowSize, std::size_t originColSize>
void transpose(
    matrix<originRowSize, originColSize> *originalMat,
    const std::unique_ptr<matrix<originColSize, originRowSize>> &transMat) {
  for (std::size_t originRowIndex = 0; originRowIndex < originColSize;
       originRowIndex++) {
    for (std::size_t originColIndex = 0; originColIndex < originRowSize;
         originColIndex++) {
      transMat->setValue(originColIndex, originRowIndex,
                         originalMat->getValue(originRowIndex, originColIndex));
    }
  }
}
template <std::size_t rowSize, std::size_t colSize, std::size_t aColSize,
          std::size_t bColSize>
void concatForMult(
    const std::unique_ptr<matrix<rowSize, aColSize>> &A,
    const std::unique_ptr<matrix<rowSize, bColSize>> &B,
    const std::unique_ptr<matrix<rowSize, (aColSize + bColSize)>> &dest) {
  dest->matrixData = A->matrixData;
  dest->matrixData.insert(dest->matrixData.end(), B->matrixData.begin(),
                          B->matrixData.end());
}
// 0 is the first slice, the source and destinsation matrix must have the same
// rowSize
template <std::size_t aRowSize, std::size_t aColSize, std::size_t bColSize>
void sliceHelper(matrix<aRowSize, aColSize> *A,
                 const std::unique_ptr<matrix<aRowSize, bColSize>> &dest,
                 const std::size_t &slice) {
  const std::size_t endOffset = aRowSize * bColSize;
  const std::size_t sliceOffset = slice * endOffset;
  dest->matrixData.assign(A->matrixData.begin() + sliceOffset,
                          A->matrixData.begin() + sliceOffset + endOffset);
}

template <std::size_t bRowSize, std::size_t sharedSize, std::size_t aColSize>
// needs B to be transposed
void transMultThread(matrix<sharedSize, aColSize> *A,
                     matrix<sharedSize, bRowSize> *B,
                     matrix<bRowSize, aColSize> *dest) {
  for (std::size_t aCurrRow = 0; aCurrRow < aColSize; aCurrRow++) {

    for (std::size_t bCurrCol = 0; bCurrCol < bRowSize; bCurrCol++) {
      float sum = 0;

      for (std::size_t dotIter = 0; dotIter < sharedSize; dotIter++) {
        sum += A->getValue(aCurrRow, dotIter) * B->getValue(bCurrCol, dotIter);
      }
      dest->setValue(aCurrRow, bCurrCol, sum);
    }
  }
}

template <std::size_t bRowSize, std::size_t sharedSize, std::size_t aColSize>
void transMult(matrix<sharedSize, aColSize> *A, matrix<bRowSize, sharedSize> *B,
               matrix<bRowSize, aColSize> *dest) {

  auto transMat = std::make_unique<matrix<sharedSize, bRowSize>>();
  transpose<bRowSize, sharedSize>(B, transMat);
  std::vector<std::unique_ptr<matrix<sharedSize, bRowSize>>> bMats;
  constexpr const std::size_t batchColSize = aColSize / MULTIPLY_TRANS_THREADS;
  constexpr const std::size_t lastColSize = aColSize % MULTIPLY_TRANS_THREADS;
  std::vector<std::unique_ptr<matrix<sharedSize, batchColSize>>> aMats;
  auto lastAMat = std::make_unique<matrix<sharedSize, lastColSize>>();
  std::vector<std::unique_ptr<matrix<bRowSize, batchColSize>>> cMats;
  auto lastCMat = std::make_unique<matrix<bRowSize, lastColSize>>();
  constexpr const std::size_t lastAMatOffsetBegin =
      batchColSize * sharedSize * MULTIPLY_TRANS_THREADS;
  lastAMat->matrixData.assign(A->matrixData.begin() + lastAMatOffsetBegin,
                              A->matrixData.end());
  for (std::size_t constructItor = 0; constructItor < MULTIPLY_TRANS_THREADS;
       constructItor++) {
    aMats.push_back(std::make_unique<matrix<sharedSize, batchColSize>>());
  };

  ;
  for (std::size_t constructItor = 0; constructItor <= MULTIPLY_TRANS_THREADS;
       constructItor++) {
    bMats.push_back(std::make_unique<matrix<sharedSize, bRowSize>>(*transMat));
  }

  for (std::size_t constructItor = 0; constructItor < MULTIPLY_TRANS_THREADS;
       constructItor++) {
    cMats.push_back(std::make_unique<matrix<bRowSize, batchColSize>>());
  }

  for (std::size_t genItor = 0; genItor < MULTIPLY_TRANS_THREADS; genItor++) {
    sliceHelper<sharedSize, aColSize, batchColSize>(A, aMats.at(genItor),
                                                    genItor);
  }
  std::vector<std::thread> threads;
  for (std::size_t genItor = 0; genItor < MULTIPLY_TRANS_THREADS; genItor++) {
    threads.push_back(
        std::thread(transMultThread<bRowSize, sharedSize, batchColSize>,
                    aMats.at(genItor).get(), bMats.at(genItor).get(),
                    cMats.at(genItor).get()));
  }

  transMultThread<bRowSize, sharedSize, lastColSize>(
      lastAMat.get(), bMats.at(MULTIPLY_TRANS_THREADS).get(), lastCMat.get());

  for (std::thread &each : threads) {
    each.join();
  }
  dest->matrixData = {};
  for (std::size_t genItor = 0; genItor < MULTIPLY_TRANS_THREADS; genItor++) {
    dest->matrixData.insert(dest->matrixData.end(),
                            cMats.at(genItor)->matrixData.begin(),
                            cMats.at(genItor)->matrixData.end());
  }

  dest->matrixData.insert(dest->matrixData.end(), lastCMat->matrixData.begin(),
                          lastCMat->matrixData.end());
}
template <std::size_t bRowSize, std::size_t sharedSize, std::size_t aColSize>
void multiply(matrix<sharedSize, aColSize> *A, matrix<bRowSize, sharedSize> *B,
              matrix<bRowSize, aColSize> *dest) {
  if (sharedSize >= MULTIPLY_TRANS_OPTIMIZATION_SIZE &&
      bRowSize >= MULTIPLY_TRANS_OPTIMIZATION_SIZE &&
      aColSize >= MULTIPLY_TRANS_OPTIMIZATION_SIZE) {
    transMult<bRowSize, sharedSize, aColSize>(A, B, dest);
    return;
  }
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
