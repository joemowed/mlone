#include "fileio.hpp"
#include "lodepng.h"
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
int main() {
  std::cout << "running mlone.exe\n";
  auto load = std::make_unique<loader>(FIO::MNIST_ROOT_PATH_TRAINING);
  load->generateFileNames();
  for (auto &each : load->catagories) {
    std::cout << each << std::endl;
  }
  load->loadDataSet();
  FIO::displayMatrixAsImage(load->loadedImages.at(58949));
  FIO::displayMatrixAsImage(load->loadedImages.at(40398));
  FIO::displayMatrixAsImage(load->loadedImages.at(3888));

  return 0;
}
