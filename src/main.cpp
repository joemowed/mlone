#include "benchmark.hpp"
#include "fileio.hpp"
#include "lodepng.h"
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
int main() {
  benchMark tot("main");
  std::cout << "running mlone.exe\n";
  auto load = std::make_unique<loader>(FIO::MNIST_ROOT_PATH_TRAINING);
  benchMark benchgfn("get file names");
  load->generateFileNames();
  for (auto &each : load->catagories) {
    std::cout << each << std::endl;
  }
  benchgfn.stop();
  benchMark benchlf("load files");
  load->loadDataSet();
  FIO::displayMatrixAsImage(load->loadedImages.at(58949));
  FIO::displayMatrixAsImage(load->loadedImages.at(40398));
  FIO::displayMatrixAsImage(load->loadedImages.at(20042));
  benchlf.stop();
  tot.stop();
  std::cout << load->loadedImages.size();
  return 0;
}
