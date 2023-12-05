#ifndef MATRIX_TEST
#define MATRIX_TEST

#include "matrix.hpp"
#include <array>
#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>
template <std::size_t rowSize, std::size_t colSize> void testMatrix() {
  std::cout << "Starting matrix class test\n";
  std::array<float, rowSize * colSize> testArray;
  bool getSetSingle = true;
  bool getRow = true;
  bool getCol = true;
  for (float i = 0; i <= rowSize * colSize - 1; i++) {
    testArray[i] = i;
  }
  std::cout << "Matrix size is " << rowSize << " for rows by " << colSize
            << " cols\n";
  std::cout << "testing single value get and set\n";
  auto testMat = std::make_unique<matrix<rowSize, colSize>>();
  for (int i = 0; i <= rowSize - 1; i++) {
    for (int e = 0; e <= colSize - 1; e++) {
      testMat->setValue(i, e, testArray[rowSize * i + e]);
    }
  }
  for (int i = 0; i <= rowSize - 1; i++) {
    for (int e = 0; e <= colSize - 1; e++) {
      std::cout << testMat->getValue(i, e) << std::endl;

      std::cout << testArray[(rowSize * i) + e] << std::endl;
      if (testMat->getValue(i, e) != testArray[rowSize * i + e]) {
        getSetSingle = false;
        std::cout << "single set/get failed\n";
        std::cout << "Row index " << i << "\nCol index " << e << std::endl;
      }
    }
  }
  std::cout << "Testing column get\n";
  for (int i = 0; i <= colSize - 1; i++) {
    std::array<float, colSize> currCol;
    for (int e = 0; e <= colSize; e++) {
      currCol[e] = testArray[(e * rowSize) + i];
    }
    std::vector<float> col = testMat->getCol(i);
    for (int e = 0; e <= colSize - 1; e++) {
      if (getCol && currCol[e] != col.at(e)) {
        getCol = false;

        std::cout << currCol[e] << " failed in col test\n";
        std::cout << "col index is " << i << std::endl;
        std::cout << "test sub-array index is " << e << std::endl;
        std::cout << "vec value " << col.at(e) << std::endl;
      } else {
      }
    }
    for (float &each : col) {
      std::cout << each << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "Testing Row get\n";
  for (int i = 0; i <= colSize - 1; i++) {
    std::array<float, rowSize> currRow;
    for (int e = 0; e <= rowSize - 1; e++) {
      currRow[e] = testArray[(i * rowSize) + e];
    }
    rowSpan row = testMat->getRow(i);
    for (int e = 0; e <= row.last; e++) {
      float *currVal = row.start;
      if (currRow[e] != *(currVal + e)) {
        getRow = false;
        std::cout << "row test for span @ + " << e << " failed\n";
        std::cout << " row.last is " << row.last << std::endl;
        std::cout << " deref of span is " << *(currVal + e) << std::endl;
        std::cout << " test array is holding " << currRow[e] << std::endl;
      }
    }
  }
  if (getSetSingle) {
    std::cout << "\n\nGet and Set Single values passed\n";
  } else {
    std::cout << "\n\nGet and Set Single values failed\n";
  }

  if (getCol) {
    std::cout << "\n\nGet and Set column values passed\n";
  } else {
    std::cout << "\n\nGet and Set column values failed\n";
  }
  if (getRow) {
    std::cout << "\n\nGet and Set row values passed\n";
  } else {
    std::cout << "\n\nGet and Set row values failed\n";
  }
}

#endif // !MATRIX_TEST
