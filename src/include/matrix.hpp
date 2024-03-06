#include <cstddef>
#include <vector>
#ifndef matrixhpp
#define matrixhpp
struct matrixDimensions {
    std::size_t rows;
    std::size_t cols;
};
class matrix {
  public:
    matrix operator*(matrix &);
    void coutMat();
    bool isTransposed = false;
    matrix(const matrixDimensions);
    matrix(const matrixDimensions, const std::vector<float>);
    matrixDimensions getDimensions();
    std::vector<float> getData() { return data; }
    void transpose();
    void relu();
    void addConst(float);
    void sigmoid();
    void sigmoid_dx();

    std::vector<float> data;
    // zero indexed
    float getMember(int x, int y);
    void setMember(int x, int y, float);
    ~matrix();

  private:
    matrixDimensions dimensions;
};
#endif
