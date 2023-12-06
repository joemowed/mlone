#ifndef MATRIX_TEST
#define MATRIX_TEST
#include "../include/matrix.hpp"
#include <algorithm>
#include <array>
#include <cstddef>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
// Demonstrate some basic assertions.
template <std::size_t rowSize, std::size_t colSize>
void matrixTestArrayFill(
    std::array<std::array<float, rowSize>, colSize> &thisArray) {
  for (std::size_t rowIndex = 0; rowIndex < colSize; rowIndex++) {
    for (std::size_t colIndex = 0; colIndex < rowSize; colIndex++) {
      thisArray[rowIndex][colIndex] = rowIndex + colIndex;
    }
  }
}

template <std::size_t rowSize, std::size_t colSize>
void matrixTestSetSingle(
    std::array<std::array<float, rowSize>, colSize> &thisArray,
    matrix<rowSize, colSize> *thisMatrix) {
  std::size_t i = 0;
  std::size_t ii = 0;
  for (const std::array<float, rowSize> &eachRow : thisArray) {

    for (const float &each : eachRow) {
      thisMatrix->setValue(i, ii, each);
      ASSERT_EQ(thisMatrix->getValue(i, ii), each);
      ii++;
    }
    ii = 0;
    i++;
  }
}
template <std::size_t rowSize, std::size_t colSize>
void matrixTestInitZero(
    std::array<std::array<float, rowSize>, colSize> &thisArray,
    matrix<rowSize, colSize> *thisMatrix) {
  for (std::size_t i = 0; i < colSize; i++) {

    for (std::size_t ii = 0; ii < rowSize; ii++) {
      ASSERT_EQ(thisMatrix->getValue(i, ii), 0);
    }
  }
}
TEST(testTest, testTest) {
  // Expect two strings not to be equal.
  ASSERT_STRNE("hello", "heelo");
  // Expect equality.
  ASSERT_EQ(7 * 6, 42);
}
TEST(matrixTest, matrixSetAndGet) {
  auto squareMatrix = std::make_unique<matrix<5, 5>>();
  auto rowMatrix = std::make_unique<matrix<10, 5>>();
  auto colMatrix = std::make_unique<matrix<5, 10>>();
  auto oneRowMatrix = std::make_unique<matrix<20, 1>>();
  auto oneColMatrix = std::make_unique<matrix<1, 20>>();
  auto bigMatrix = std::make_unique<matrix<500, 500>>();
  std::array<std::array<float, 5>, 5> squareTest;
  std::array<std::array<float, 5>, 10> colTest;
  std::array<std::array<float, 10>, 5> rowTest;
  std::array<std::array<float, 20>, 1> oneRowTest;
  std::array<std::array<float, 1>, 20> oneColTest;
  std::array<std::array<float, 500>, 500> bigTest;
  matrixTestArrayFill<5, 5>(squareTest);
  matrixTestArrayFill<5, 10>(colTest);
  matrixTestArrayFill<10, 5>(rowTest);
  matrixTestArrayFill<1, 20>(oneColTest);
  matrixTestArrayFill<20, 1>(oneRowTest);
  matrixTestArrayFill<500, 500>(bigTest);
  matrixTestSetSingle<5, 10>(colTest, colMatrix.get());
  matrixTestSetSingle<5, 5>(squareTest, squareMatrix.get());
  matrixTestSetSingle<10, 5>(rowTest, rowMatrix.get());
  matrixTestSetSingle<1, 20>(oneColTest, oneColMatrix.get());
  matrixTestSetSingle<20, 1>(oneRowTest, oneRowMatrix.get());
  matrixTestSetSingle<500, 500>(bigTest, bigMatrix.get());
}
TEST(matrixTest, copyAndTranpose) {
  auto squareMatrix = std::make_unique<matrix<5, 5>>();
  auto rowMatrix = std::make_unique<matrix<10, 5>>();
  auto colMatrix = std::make_unique<matrix<5, 10>>();
  auto oneRowMatrix = std::make_unique<matrix<20, 1>>();
  auto oneColMatrix = std::make_unique<matrix<1, 20>>();
  auto bigMatrix = std::make_unique<matrix<500, 500>>();
  std::array<std::array<float, 5>, 5> squareTest;
  std::array<std::array<float, 5>, 10> colTest;
  std::array<std::array<float, 10>, 5> rowTest;
  std::array<std::array<float, 20>, 1> oneRowTest;
  std::array<std::array<float, 1>, 20> oneColTest;
  std::array<std::array<float, 500>, 500> bigTest;
  matrixTestArrayFill<5, 5>(squareTest);
  matrixTestArrayFill<5, 10>(colTest);
  matrixTestArrayFill<10, 5>(rowTest);
  matrixTestArrayFill<1, 20>(oneColTest);
  matrixTestArrayFill<20, 1>(oneRowTest);
  matrixTestArrayFill<500, 500>(bigTest);
  matrixTestSetSingle<5, 10>(colTest, colMatrix.get());
  matrixTestSetSingle<5, 5>(squareTest, squareMatrix.get());
  matrixTestSetSingle<10, 5>(rowTest, rowMatrix.get());
  matrixTestSetSingle<1, 20>(oneColTest, oneColMatrix.get());
  matrixTestSetSingle<20, 1>(oneRowTest, oneRowMatrix.get());
  matrixTestSetSingle<500, 500>(bigTest, bigMatrix.get());
  auto copy1 = std::make_unique<matrix<5, 10>>();
  auto copy3 = std::make_unique<matrix<10, 5>>(*rowMatrix);
  ASSERT_EQ(copy3->matrixData, rowMatrix->matrixData);
  MOP::transpose<10, 5>(rowMatrix, copy1);
  ASSERT_NE(copy1->matrixData, rowMatrix->matrixData);
  MOP::transpose<5, 10>(copy1, copy3);

  ASSERT_EQ(copy3->matrixData, rowMatrix->matrixData);
}
TEST(matrixTest, matrixInitZero) {
  auto squareMatrix = std::make_unique<matrix<5, 5>>();
  auto rowMatrix = std::make_unique<matrix<10, 5>>();
  auto colMatrix = std::make_unique<matrix<5, 10>>();
  auto oneRowMatrix = std::make_unique<matrix<20, 1>>();
  auto oneColMatrix = std::make_unique<matrix<1, 20>>();
  auto bigMatrix = std::make_unique<matrix<500, 500>>();
  std::array<std::array<float, 5>, 5> squareTest;
  std::array<std::array<float, 5>, 10> colTest;
  std::array<std::array<float, 10>, 5> rowTest;
  std::array<std::array<float, 20>, 1> oneRowTest;
  std::array<std::array<float, 1>, 20> oneColTest;
  std::array<std::array<float, 500>, 500> bigTest;
  matrixTestArrayFill<5, 5>(squareTest);
  matrixTestArrayFill<5, 10>(colTest);
  matrixTestArrayFill<10, 5>(rowTest);
  matrixTestArrayFill<1, 20>(oneColTest);
  matrixTestArrayFill<20, 1>(oneRowTest);
  matrixTestArrayFill<500, 500>(bigTest);
  matrixTestInitZero<5, 10>(colTest, colMatrix.get());
  matrixTestInitZero<5, 5>(squareTest, squareMatrix.get());
  matrixTestInitZero<10, 5>(rowTest, rowMatrix.get());
  matrixTestInitZero<1, 20>(oneColTest, oneColMatrix.get());
  matrixTestInitZero<20, 1>(oneRowTest, oneRowMatrix.get());
  matrixTestInitZero<500, 500>(bigTest, bigMatrix.get());
  std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\ntesting a1,b1\n";
}
TEST(matrixTest, matrixMultTest) {

  std::cout << "\ntesting a1,b1\n";
  auto A1 = std::make_unique<matrix<3, 3>>();
  auto B1 = std::make_unique<matrix<1, 3>>();
  auto C1 = std::make_unique<matrix<1, 3>>();
  auto C2 = std::make_unique<matrix<2, 3>>();
  auto B2 = std::make_unique<matrix<2, 3>>();
  auto A2 = std::make_unique<matrix<500, 500>>();
  auto B3 = std::make_unique<matrix<500, 500>>();
  auto C3 = std::make_unique<matrix<500, 500>>();
  std::array<std::array<float, 500>, 500> bigTest;
  matrixTestArrayFill<500, 500>(bigTest);
  matrixTestSetSingle<500, 500>(bigTest, A2.get());
  matrixTestSetSingle<500, 500>(bigTest, B3.get());
  A1->setValue(0, 0, 1);
  A1->setValue(0, 1, 2);
  A1->setValue(0, 2, 3);
  A1->setValue(1, 0, 4);
  A1->setValue(1, 1, 5);
  A1->setValue(1, 2, 6);
  A1->setValue(2, 0, 7);
  A1->setValue(2, 1, 8);
  A1->setValue(2, 2, 9);
  B1->setValue(0, 0, 1);
  B1->setValue(1, 0, 2);
  B1->setValue(2, 0, 3);

  B2->setValue(0, 0, 1);
  B2->setValue(1, 0, 2);
  B2->setValue(2, 0, 3);
  B2->setValue(0, 1, 4);
  B2->setValue(1, 1, 5);
  B2->setValue(2, 1, 6);
  std::cout << "\ntesting a1,b1\n";
  MOP::multiply<1, 3, 3>(A1, B1, C1);
  std::cout << "\ntesting a1,b2\n";
  MOP::multiply<2, 3, 3>(A1, B2, C2);
  std::cout << "\ntesting a3,b3\n";
  MOP::multiply<500, 500, 500>(A2, B3, C3);
  ASSERT_EQ(C1->getValue(0, 0), 14);
  ASSERT_EQ(C1->getValue(1, 0), 32);
  ASSERT_EQ(C1->getValue(2, 0), 50);
  ASSERT_EQ(C2->getValue(0, 0), 14);
  ASSERT_EQ(C2->getValue(1, 0), 32);
  ASSERT_EQ(C2->getValue(2, 0), 50);

  ASSERT_EQ(C2->getValue(0, 1), 32);
  ASSERT_EQ(C2->getValue(1, 1), 77);
  ASSERT_EQ(C2->getValue(2, 1), 122);
}
TEST(matrixTest, concatMat) {
  auto squareMatrix = std::make_unique<matrix<5, 5>>();
  auto rowMatrix = std::make_unique<matrix<10, 5>>();
  auto colMatrix = std::make_unique<matrix<5, 10>>();
  auto oneRowMatrix = std::make_unique<matrix<20, 1>>();
  auto oneColMatrix = std::make_unique<matrix<1, 20>>();
  auto bigMatrix = std::make_unique<matrix<500, 500>>();
  std::array<std::array<float, 5>, 5> squareTest;
  std::array<std::array<float, 5>, 10> colTest;
  std::array<std::array<float, 10>, 5> rowTest;
  std::array<std::array<float, 20>, 1> oneRowTest;
  std::array<std::array<float, 1>, 20> oneColTest;
  std::array<std::array<float, 500>, 500> bigTest;
  matrixTestArrayFill<5, 5>(squareTest);
  matrixTestArrayFill<5, 10>(colTest);
  matrixTestArrayFill<10, 5>(rowTest);
  matrixTestArrayFill<1, 20>(oneColTest);
  matrixTestArrayFill<20, 1>(oneRowTest);
  matrixTestArrayFill<500, 500>(bigTest);
  matrixTestSetSingle<5, 10>(colTest, colMatrix.get());
  matrixTestSetSingle<5, 5>(squareTest, squareMatrix.get());
  matrixTestSetSingle<10, 5>(rowTest, rowMatrix.get());
  matrixTestSetSingle<1, 20>(oneColTest, oneColMatrix.get());
  matrixTestSetSingle<20, 1>(oneRowTest, oneRowMatrix.get());
  matrixTestSetSingle<500, 500>(bigTest, bigMatrix.get());
  auto first = std::make_unique<matrix<2, 3>>();
  auto second = std::make_unique<matrix<2, 3>>();
  auto result = std::make_unique<matrix<2, 6>>();
  auto compare = std::make_unique<matrix<2, 6>>();
  float i = 0;
  for (float &each : first->matrixData) {
    each = i;
    i++;
  }
  i = 0;
  for (float &each : second->matrixData) {
    each = i;
    i++;
  }
  i = 0;
  for (float &each : compare->matrixData) {
    i = (i >= 6) ? 0 : i;
    each = i;
    i++;
  }

  MOP::concatForMult<2, 6, 3, 3>(first, second, result);
  ASSERT_EQ(compare->matrixData, result->matrixData);
}
TEST(matrixTest, sliceMat) {
  auto squareMatrix = std::make_unique<matrix<5, 5>>();
  auto rowMatrix = std::make_unique<matrix<10, 5>>();
  auto colMatrix = std::make_unique<matrix<5, 10>>();
  auto oneRowMatrix = std::make_unique<matrix<20, 1>>();
  auto oneColMatrix = std::make_unique<matrix<1, 20>>();
  auto bigMatrix = std::make_unique<matrix<500, 500>>();
  std::array<std::array<float, 5>, 5> squareTest;
  std::array<std::array<float, 5>, 10> colTest;
  std::array<std::array<float, 10>, 5> rowTest;
  std::array<std::array<float, 20>, 1> oneRowTest;
  std::array<std::array<float, 1>, 20> oneColTest;
  std::array<std::array<float, 500>, 500> bigTest;
  matrixTestArrayFill<5, 5>(squareTest);
  matrixTestArrayFill<5, 10>(colTest);
  matrixTestArrayFill<10, 5>(rowTest);
  matrixTestArrayFill<1, 20>(oneColTest);
  matrixTestArrayFill<20, 1>(oneRowTest);
  matrixTestArrayFill<500, 500>(bigTest);
  matrixTestSetSingle<5, 10>(colTest, colMatrix.get());
  matrixTestSetSingle<5, 5>(squareTest, squareMatrix.get());
  matrixTestSetSingle<10, 5>(rowTest, rowMatrix.get());
  matrixTestSetSingle<1, 20>(oneColTest, oneColMatrix.get());
  matrixTestSetSingle<20, 1>(oneRowTest, oneRowMatrix.get());
  matrixTestSetSingle<500, 500>(bigTest, bigMatrix.get());
  auto first = std::make_unique<matrix<2, 3>>();
  auto second = std::make_unique<matrix<2, 3>>();
  auto result = std::make_unique<matrix<2, 6>>();

  auto compare = std::make_unique<matrix<2, 6>>();
  float i = 0;
  for (float &each : first->matrixData) {
    each = i;
    i++;
  }
  i = 0;
  for (float &each : second->matrixData) {
    each = i;
    i++;
  }
  i = 0;
  for (float &each : compare->matrixData) {
    i = (i >= 6) ? 0 : i;
    each = i;
    i++;
  }
  auto slice1 = std::make_unique<matrix<2, 3>>();
  auto slice2 = std::make_unique<matrix<2, 3>>();
  MOP::concatForMult<2, 6, 3, 3>(first, second, result);
  MOP::sliceHelper<2, 6, 3>(result, slice1, 0);
  MOP::sliceHelper<2, 6, 3>(result, slice2, 1);
  ASSERT_EQ(first->matrixData, slice1->matrixData);
  ASSERT_EQ(second->matrixData, slice2->matrixData);
}
#endif // !MATRIX_TEST
