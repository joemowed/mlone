#include <array>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <gradient.hpp>
#include <iostream>
#include <machine.hpp>
#include <matMath.hpp>
#include <matrix.hpp>
#include <ostream>
#include <random>
#include <vector>
machine::machine() {
    auto time = std::chrono::system_clock::now();
    auto mid = std::chrono::time_point_cast<std::chrono::nanoseconds>(time);
    double seed = mid.time_since_epoch().count();
    machineRandGenorator.seed(seed);
}
void machine::addInputLayer(std::size_t nodes) {
    assert(!inputLayerAttached);
    const matrixDimensions dims = {.rows = nodes, .cols = 1};
    inputLayer = matrix(dims);
    inputLayerAttached = true;
}
void machine::addLayer(std::size_t nodes) {
    assert((inputLayerAttached) && "no input layer connected before adding layer");
    matrixDimensions dims, biasDims;

    if (layers.size() < 1) {
        dims = {.rows = inputLayer.getDimensions().rows, .cols = nodes};
        biasDims = {.rows = nodes, .cols = 1};
    } else {
        dims = {.rows = (layers.back()[0].getDimensions().cols), .cols = nodes};
        biasDims = {.rows = nodes, .cols = 1};
    }
    matrix weightMat = matrix(dims);
    matrix biasMat = matrix(biasDims);
    for (float &each : weightMat.data) {
        each = genRand();
    }
    for (float &each : biasMat.data) {
        //    each = genRand();
    }
    const std::array<matrix, 2> ret = {weightMat, biasMat};
    grad.addLinearLayer(ret, layers.size());
    layers.push_back(ret);
}
void machine::setRandGenSigma(float sigma) {
    randGenSigma = sigma;
    randGen = std::normal_distribution<float>(0, randGenSigma);
}
float machine::genRand() {
    // return randGenSigma * (1 / std::rand() % 1000);
    float r = randGen(machineRandGenorator);
    std::cout << r << std::endl;
    return r;
}

matrix machine::infer(matrix &input) {
    assert((input.data.size() == inputLayer.data.size()) && "inferring on mismatched matrix");
    const auto dims = input.getDimensions();
    matrix ret = matrix(dims);
    ret.data = input.data;
    int i = 0;
    for (const auto layer : layers) {
        matrix weights = layer[0];
        matrix bias = layer[1];
        ret.transpose();
        ret = ret * weights;
        ret.transpose();
        ret = MM::addMat(ret, bias);
        ret.relu();
        i++;
    }
    return ret;
}
void machine::addLayer(matrix weight, matrix bias) {
    const std::array<matrix, 2> ret = {weight, bias};
    layers.push_back(ret);
}
void machine::addOutputLayer(std::size_t nodes) {
    assert((inputLayerAttached && !outputLayerAttached) && "output layer already defined or input layer undefined");
    /*
    const matrixDimensions dims = {.rows = nodes, .cols = 1};
    matrix weights = matrix(dims);
    matrix bias = matrix(dims);
    for (float &each : weights.data) {
        each = 1;
    }
    for (float &each : bias.data) {
        each = 0;
    }
    const std::array<matrix, 2> ret = {weights, bias};
    layers.push_back(ret);
    */
    addLayer(nodes);
}
float sig(float val) { return (1 / (1 + expf(-1.0 * val))); }
float sig_dx(float val) { return sig(val) * sig(1 - val); }

matrix machine::squareLoss(matrix inferred, matrix actual) {
    assert((inferred.getDimensions().cols == actual.getDimensions().cols && inferred.getDimensions().rows == actual.getDimensions().rows) && "attempt to compute loss with dimension mismatch");
    const auto dims = inferred.getDimensions();
    std::vector<float> ret;
    ret.resize(inferred.getDimensions().rows * inferred.getDimensions().cols);
    int i = 0;
    for (float &each : ret) {
        float res = (inferred.data.at(i) - actual.data.at(i));
        res *= res;
        each = res;
        i++;
    }
    return matrix(dims, ret);
}
/*
matrix machine::finalLayer_dx(matrix x, matrix real, matrix inferred) {

    auto weightIndex = layers.size() - 1;
    auto &finalLayerWeights = layers.at(weightIndex).at(0);
    const auto dims = finalLayerWeights.getDimensions();
    auto ret = matrix(dims);
    for (int i = 0; i < dims.cols; i++) {
        for (int j = 0; j < dims.rows; j++) {
        }
    }
    return ret;
}
*/
void machine::learn(std::size_t epochs, std::vector<matrix> inputs, std::vector<matrix> actual) {
    assert((inputs.size() == actual.size()) && "attempt to learn with input, actual mismatch");
    auto gradient = matrix({1, 1});
    for (int i = 1; i <= epochs; i++) {
        matrix res = matrix(layers.back().at(1).getDimensions());
        int j = 0;
        for (auto &input : inputs) {
            auto &feedForward = input;
            for (std::size_t layerIndex = 0; layerIndex < layers.size(); layerIndex++) {

                feedForward = grad.inferLayer(feedForward, layerIndex);
            }
            res = feedForward;
            grad.computeCost(res, actual.at(j));
            j++;
            if (j == 1) {
                gradient = grad.getGradientForWeight(layers.size() - 1);
            } else {

                auto gradientRun = grad.getGradientForWeight(layers.size() - 1);

                gradient = MM::addMat(gradientRun, gradient);
            }
        }
        if (i < 100 || i % 100 == 0) {
            std::cout << "Training epoch " << i << std::endl;
            std::size_t N = inputs.size();
            updateLayer(layers.back(), gradient);
        }
    }
    int i = 0;
    if (false) {
        for (auto &each : grad.linearLayers) {
            grad.coutLayer(each, i);
            i++;
        }
    }
}
void machine::updateLayer(std::array<matrix, 2> &layer, matrix &weightGrad) {
    bool cout = false;
    if (cout) {
        std::cout << "old mat: \n";
        layer.at(0).coutMat();
    }
    for (int x = 0; x < layer.at(0).getDimensions().cols; x++) {
        for (int y = 0; y < layer.at(0).getDimensions().rows; y++) {
            float weight = layer.at(0).getMember(x, y);
            weight += (-1.0 * learningFactor * weightGrad.getMember(x, y));

            layer.at(0).setMember(x, y, weight);
        }
    }
    if (cout) {
        std::cout << "new mat: \n";
        layer.at(0).coutMat();
    }
}
void machine::coutMachine() {

    int i = 0;
    for (std::array<matrix, 2> &each : layers) {
        std::cout << "Layer " << i << " weights\n";
        each[0].coutMat();
        std::cout << "Layer " << i << " bias\n";
        each[1].coutMat();
        i++;
    }
}
void machine::coutIntermediate() {}
