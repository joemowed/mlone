#include "matrix.hpp"
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>
namespace FIO {

constexpr const std::size_t WIDTH = 28;
constexpr const std::size_t HEIGHT = 28;
constexpr const char MNIST_ROOT_PATH_TRAINING[] =
    "/home/jmaloney/Documents/mlone/mnist_png/training";
constexpr const char MNIST_ROOT_PATH_TESTING[] =
    "/home/jmaloney/Documents/mlone/mnist_png/testing";
void displayMatrixAsImage(matrix<WIDTH, HEIGHT> &mat);
} // namespace FIO
class loader {

public:
  void generateFileNames();
  void dumpFileNames();
  bool hasFileNamesGenerated = false;
  std::string rootDir = "";
  std::vector<std::vector<std::string>> fileNames;
  std::vector<std::string> catagories; // index matched to fileNames outervector
  std::vector<std::string> getNamesForSubFolder(std::string subDir);
  std::vector<matrix<FIO::WIDTH, FIO::HEIGHT>> loadedImages;
  std::vector<std::string>
      loadedImagesCatagories; // index Matched to loadedImages
  std::vector<float> loadImage(std::string fileName);
  loader(std::string rootDir);
  void loadDataSet();
};
