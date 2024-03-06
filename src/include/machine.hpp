#ifndef machinehpp
#define machinehpp
#include <array>
#include <cstddef>
#include <gradient.hpp>
#include <matrix.hpp>
#include <random>
#include <vector>
class machine {
  public:
    machine();
    void addInputLayer(std::size_t nodes);
    void addLayer(std::size_t nodes);
    void setRandGenSigma(float sigma);
    void addOutputLayer(std::size_t nodes);
    void addLayer(matrix weights, matrix bias);
    void coutMachine();
    void coutIntermediate();
    matrix final_dx(matrix prevActivation, matrix Z, matrix actual, matrix activation);
    void learn(std::size_t epochs, std::vector<matrix> inputs, std::vector<matrix> actual);
    matrix infer(matrix &input);
    std::vector<std::array<matrix, 2>> layers;
    matrix inferLearn(matrix &input);

  private:
    gradient grad = gradient(this);
    void updateLayer(std::array<matrix, 2> &layer, matrix &weightGrad);
    matrix finalLayer_dx(matrix, matrix, matrix);
    bool inputLayerAttached = false;
    matrix getZ(std::size_t layer, matrix val);
    bool outputLayerAttached = false;
    matrix outputLayer = matrix({1, 1});
    float learningFactor = 0.005;
    float genRand();
    std::default_random_engine machineRandGenorator;
    float randGenSigma = 0.75;
    std::normal_distribution<float> randGen{0, randGenSigma};
    matrix inputLayer = matrix({1, 1});
    matrix squareLoss(matrix inferred, matrix actual);
};
#endif // !machinehpp
