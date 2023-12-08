#include "fileio.hpp"
#include "lodepng.h"
#include "matrix.hpp"
#include <filesystem>
#include <string>
#include <unistd.h>
#include <vector>
loader::loader(std::string rootDir) { loader::rootDir = rootDir; }
std::vector<std::string> loader::getNamesForSubFolder(std::string subDir) {
  std::vector<std::string> ret;
  std::string fullPath;
  fullPath = rootDir + "/" + subDir;
  for (const std::filesystem::directory_entry &eachFile :
       std::filesystem::directory_iterator(fullPath)) {

    ret.push_back(eachFile.path());
  }
  return ret;
}

void loader::generateFileNames() {
  assert(!loader::hasFileNamesGenerated && "attempt to re-generate filenames");
  std::vector<std::string> topLevel;
  topLevel = loader::getNamesForSubFolder("");
  for (const std::string &eachSubDir : topLevel) {
    std::string attenuatedSubDir = eachSubDir;
    attenuatedSubDir.erase(0, loader::rootDir.length() + 1);
    loader::catagories.push_back(attenuatedSubDir);
    std::vector<std::string> currScan;
    currScan = loader::getNamesForSubFolder(attenuatedSubDir);
    loader::fileNames.push_back(currScan);
  }

  loader::hasFileNamesGenerated = true;
}
void loader::dumpFileNames() {

  assert(loader::hasFileNamesGenerated &&
         "attempt to dump names before generation of file names");
  int i = 0;
  for (auto &each : fileNames) {
    std::cout << catagories.at(i) << std::endl;
    i++;
    for (auto &eachStr : each) {
      std::cout << "    |" << eachStr << std::endl;
    }
  }
}
std::vector<float> loader::loadImage(std::string fileName) {
  std::vector<unsigned char> imageVec;
  std::vector<unsigned char> tempPng;
  std::vector<unsigned char> proc;
  std::vector<float> postProc;
  postProc.reserve(FIO::HEIGHT * FIO::WIDTH);
  proc.reserve((4 * FIO::WIDTH * FIO::HEIGHT));
  imageVec.reserve(FIO::HEIGHT * FIO::WIDTH * 4);
  lodepng::load_file(tempPng, fileName);
  unsigned w, h;
  lodepng::decode(imageVec, w, h, tempPng);
  for (int red = 0; red < w * 4 * h; red++) {
    if (red % 4 == 2) {
      proc.push_back(imageVec.at(red));
    }
  }
  for (auto &each : proc) {
    float curr = static_cast<float>(each);
    curr = (curr == 0) ? 0 : (curr * (1.0 / 255.0));
    postProc.push_back(curr);
  }
  for (auto &each : postProc) {
  }
  return postProc;
}
void loader::loadDataSet() {

  assert(loader::hasFileNamesGenerated &&
         "attempt to load images before generating filenames");
  std::size_t outer = 0;
  for (const std::vector<std::string> &eachCatagory : loader::fileNames) {
    std::string currCatagory = loader::catagories.at(outer);
    outer++;
    for (const std::string &currFile : eachCatagory) {
      loader::loadedImagesCatagories.push_back(currCatagory);
      std::vector<float> currVec = loadImage(currFile);

      matrix<FIO ::WIDTH, FIO::HEIGHT> currMat =
          matrix<FIO ::WIDTH, FIO::HEIGHT>(currVec);
      loader::loadedImages.push_back(currMat);
    }
  }
}
void FIO::displayMatrixAsImage(matrix<FIO::WIDTH, FIO::HEIGHT> &mat) {
  const std::string black = " ";
  const std::string dark = "▓";
  const std::string medium = "▒";
  const std::string light = "░";
  std::size_t currPixel = 0;
  std::cout << std::endl << "displaying matrix as image";
  for (float &each : mat.matrixData) {
    if ((currPixel + 0) % FIO::WIDTH == 0) {
      std::cout << std::endl;
    }
    currPixel++;
    if (each == 0.0) {
      std::cout << black;
    } else if (each < 0.4) {
      std::cout << light;
    } else if (each < 0.69) {
      std::cout << medium;
    } else {
      std::cout << dark;
    }
  }
}
