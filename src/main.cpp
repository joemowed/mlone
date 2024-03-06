#include "machine.hpp"
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <matMath.hpp>
#include <matrix.hpp>
#include <vector>
std::array<std::vector<matrix>, 2> genLinearTrainingSet(std::size_t size);
float loss(std::vector<matrix> x, std::vector<matrix> inferred, std::vector<matrix> real);
int main() {
    const std::vector<float> inputVec = {2, 1};
    const matrixDimensions inputDims = {.rows = 2, .cols = 1};
    matrix input = matrix(inputDims, inputVec);
    const std::vector<float> hiddenLayerVec = {-1, 2};
    const matrixDimensions hiddenLayerDims = {2, 1};
    matrix hiddenLayerWeights = matrix(hiddenLayerDims, hiddenLayerVec);
    matrix hiddenLayerBias = matrix({1, 1}, {0});
    machine mach;
    std::vector<matrix> res;
    std::vector<matrix> res2;
    auto data = genLinearTrainingSet(9);
    mach.addInputLayer(1);
    mach.addLayer(30);
    mach.addOutputLayer(1);
    int i = 0;
    if (true) {
        for (auto &each : data.at(0)) {
            const matrix curr = data.at(1).at(i);
            std::cout << "x: " << each.data.at(0);
            std::cout << " real: " << curr.data.at(0);
            std::cout << " inferred: " << mach.infer(each).data.at(0) << std::endl;
            i++;
        }
    }
    i = 0;
    for (auto each : data.at(0)) {
        res.push_back(mach.infer(each));
        i++;
    }
    mach.learn(20, data.at(0), data.at(1));
    i = 0;
    for (auto each : data.at(0)) {
        res2.push_back(mach.infer(each));
        i++;
    }
    i = 0;
    if (true) {
        for (auto &each : data.at(0)) {
            const matrix curr = data.at(1).at(i);
            std::cout << "x: " << each.data.at(0);
            std::cout << " real: " << curr.data.at(0);
            std::cout << " inferred: " << mach.infer(each).data.at(0) << std::endl;
            i++;
        }
    }

    std::cout << "loss before: " << loss(data.at(0), res, data.at(1)) << " after: " << loss(data.at(0), res2, data.at(1)) << std::endl;
    return 1;
}
std::array<std::vector<matrix>, 2> genLinearTrainingSet(std::size_t size) {
    std::array<std::vector<matrix>, 2> ret;
    const float slope = 2;
    const float max = 1;
    const float deltaX = max / (size * slope);
    float curr = 0;
    const matrixDimensions dims = {1, 1};
    for (int i = 0; i <= size; i++) {

        ret.at(0).push_back(matrix(dims, {curr}));
        std::vector<float> yVec;
        yVec.push_back((curr * slope));
        ret.at(1).push_back(matrix(dims, yVec));
        curr += deltaX;
    }
    int i = 0;
    if (false) {
        for (auto &each : ret.at(0)) {
            std::cout << "x: " << each.data.at(0);
            std::cout << " y: " << ret.at(1).at(i).data.at(0) << std::endl;
            i++;
        }
    }
    return ret;
}
float loss(std::vector<matrix> x, std::vector<matrix> inferred, std::vector<matrix> real) {
    float sum = 0;
    int i = 0;
    for (const auto &each : x) {
        sum += (inferred.at(i).data.at(0) - real.at(i).data.at(0)) * (inferred.at(i).data.at(0) - real.at(i).data.at(0));
        i++;
    }
    return sum / x.size();
}
