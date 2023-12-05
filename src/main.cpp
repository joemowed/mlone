#include "matrix.hpp"
#include "matrixTest.hpp"
#include <iostream>
#include <memory>
#include <ostream>
int main() {
  testMatrix<4, 3>();

  testMatrix<3, 5>();

  //: testMatrix<342, 543>();

  return 0;
}
