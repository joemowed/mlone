
#include "graph.hpp"
#include "testHelper.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <machine.hpp>
#include <memory>
#include <random>
#include <string>
constexpr const size_t COST_NODES = 3;
machine::machine(const size_t inputLayerSize) {
    Layer tmp{inputLayerSize, 0};
    Layers.push_back(tmp);
    this->g = std::make_unique<graph>(inputLayerSize);
}
void machine::fullCoutLayer(size_t layer) const { std::cout << g->data.at(layer).operation << "\n"; }
void machine::coutLayer(size_t layer) const {
    const Layer &currLayer = Layers.at(layer);
    std::cout << "Layer " << layer << "  Size:" << currLayer.size << "  Weights: " << currLayer.weightCount << "\n";
}
void machine::coutMachine() const {
    size_t weightCount = 0;
    for (const auto &each : Layers) {
        weightCount += each.weightCount;
    }
    size_t mem = sizeof(float) * weightCount;
    std::string memString;
    memString = (mem < 1E3) ? (std::to_string(mem) + " B") : "";
    memString = (mem >= 1E3) ? (std::to_string(static_cast<float>(mem) / 1E3) + " KB") : memString;
    memString = (mem >= 1E6) ? (std::to_string(static_cast<float>(mem) / 1E6) + " MB") : memString;
    std::cout << "Printing machine:\nLayer count: " << Layers.size() << "  Total weights: " << weightCount << " Float only memory usage: " << memString << "\nInput Layer  size: " << Layers.at(0).size
              << "\n";
    size_t i = 0;
    for (const auto &each : Layers) {
        // skip input
        if (i == 0) {
            i++;
            continue;
        } else {
            coutLayer(i++);
        }
    }
}
void machine::addLayer(const size_t size) {
    const Layer &prevLayer = Layers.back();
    const float xavierSD = sqrtf((2 / (static_cast<float>(size) + static_cast<float>(prevLayer.size))));
    std::normal_distribution<float> dist{0, xavierSD};
    matrix weights{size, prevLayer.size, dist};
    const Layer currLayer{size, (size * prevLayer.size)};
    g->addNode(graph::multiply, weights);
    g->addNode(graph::sigmoid);
    Layers.push_back(currLayer);
}
matrix machine::infer(matrix input) {
    assertm(input.j() == 1, "Inferring on matrix with more than one column");
    assertm(input.i() == Layers.at(0).size, "Inferring on matrix not equal to input layer size");
    g->calculate(input);
    return g->result();
}
void machine::train(std::vector<std::pair<matrix, matrix>> trainingData, const float learningRate, const size_t epocs) {
    addCostLayer(trainingData.at(0).second.i());
    const float derating = 1.0 / trainingData.size();
    for (size_t epocCounter = 1; epocCounter <= epocs; epocCounter++) {
        float avgLoss = 0;
        size_t i = 0;
        std::vector<matrix> meanWeightAdj;
        for (const auto &inputData : trainingData) {
            auto iterDelta = this->inferForTraining(inputData);
            if (i == 0) {
                std::vector<matrix> tmp;
                for (auto &each : iterDelta) {
                    matrix mat = each.multiplyByConstant(derating);
                    tmp.push_back(mat);
                }
                meanWeightAdj = tmp;
            } else {
                size_t ii = 0;
                for (auto &each : meanWeightAdj) {
                    each = each + iterDelta.at(ii).multiplyByConstant(derating);
                    ii++;
                }
            }
            for (auto each : meanWeightAdj) {
                //    each.coutMat("m");
            }
            i++;
            for (size_t j = 0; j < g->result().i(); j++) {
                avgLoss += (g->result().at(j, 0) / derating);
            }
        }
        this->updateWeights(learningRate, meanWeightAdj);
        std::cout << "Epoc " << epocCounter << " (" << (100.0 * (static_cast<float>(epocCounter) / static_cast<float>(epocs))) << "%) " << "Loss: " << avgLoss << "\n";
    }
}
void machine::updateWeights(const size_t rate, std::vector<matrix> reverseWeightAdjustmentMatrix) {
    std::reverse(reverseWeightAdjustmentMatrix.begin(), reverseWeightAdjustmentMatrix.end());
    size_t i = 0;
    for (const auto &each : reverseWeightAdjustmentMatrix) {
        for (;;) {
            if (g->data.at(i).operation == graph::multiply) {
                each.multiplyByConstant((-1.0 * rate));
                g->data.at(i).constants = g->data.at(i).constants.value() + each.transpose();
                i++;
                break;
            }
            i++;
        }
    }
}
// very simple backprop, includes the cost function and sig_dx
std::vector<matrix> machine::inferForTraining(std::pair<matrix, matrix> inputData) {
    assert(costFlag);
    const matrix &input = inputData.first;
    const matrix &y = inputData.second;
    const auto &gdata = g->data;
    std::vector<matrix> ret;
    this->loadNewCostConstants(y);
    g->calculate(input);
    matrix prev_dC = this->getdC_dE();
    size_t i = gdata.size() - COST_NODES - 1;
    for (; i > 0; i--) {
        const auto &currNode = gdata.at(i);
        if (currNode.operation == graph::sigmoid) {
            prev_dC = prev_dC.hadMult(currNode.result->sig_d());
        }
        if (currNode.operation == graph::multiply) {
            matrix dC_dw = (prev_dC * (gdata.at(i - 1).result->transpose())).transpose();
            prev_dC = (currNode.constants.value().transpose() * prev_dC);
            ret.push_back(dC_dw);
        }
    }
    return ret;
}
matrix machine::getdC_dE() const { return g->data.at(g->data.size() - COST_NODES).result.value(); }
void machine::loadNewCostConstants(const matrix &y) {
    assertm(y.j() == 1, "Loading non j=1 cost matrix");
    assertm(y.i() == Layers.back().size, "Cost matrix does not align with final activation layer, i dimension");
    // 3 is magic constant from addCostLayer
    g->data.at(g->data.size() - COST_NODES).constants = y;
}
void machine::addCostLayer(const size_t size) {
    std::vector<float> halfVec(size, 0.5F);
    matrix y{size, 1};
    matrix half{size, 1, halfVec};
    g->addNode(graph::subtract, y);
    g->addNode(graph::squared);
    g->addNode(graph::multiply, half);
    costFlag = true;
}
