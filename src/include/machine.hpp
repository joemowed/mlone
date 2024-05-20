#ifndef MACHINE_FJDLKSAJLFKJDSALKJFLKASJFLKJASLKFJSLAKHKJSDFHGO
#define MACHINE_FJDLKSAJLFKJDSALKJFLKASJFLKJASLKFJSLAKHKJSDFHGO
#include "graph.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <memory>
#include <vector>
class machine {
  public:
    struct Layer {
        const size_t size;
        const size_t weightCount;
    };

  private:
    std::vector<Layer> Layers;
    std::unique_ptr<graph> g;
    bool costFlag = false;

    matrix getdC_dE() const;
    void addCostLayer(const size_t size);
    void loadNewCostConstants(const matrix &y);
    std::vector<matrix> inferForTraining(std::pair<matrix, matrix> inputData);
    matrix trainingTransposeMult(const matrix &prevActivation, const matrix &sig_dx);
    void updateWeights(const size_t rate, std::vector<matrix> reverseWeightAdjustmentMatrix);

  public:
    machine(const size_t inputLayerSize);
    void coutLayer(size_t layer) const;
    void fullCoutLayer(size_t layer) const;
    void coutMachine() const;
    void addLayer(const size_t size);
    matrix infer(matrix input);
    // input on left, correct answer on right
    void train(std::vector<std::pair<matrix, matrix>> trainingData, const float learningRate, const size_t epocs);
};

#endif
