#include "fileio.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <vector>
TEST(fileio, testTest) { ASSERT_EQ(1, 1); }
TEST(fileio, getNames) {

  auto load = std::make_unique<loader>(FIO::MNIST_ROOT_PATH_TRAINING);
  std::vector<std::string> subDirNames = load->getNamesForSubFolder("training");
  for (std::string &each : subDirNames) {
    std::cout << each << std::endl;
  }
  ASSERT_EQ(subDirNames.at(0),
            (static_cast<std::string>(FIO::MNIST_ROOT_PATH_TRAINING) + "/0"));
}
