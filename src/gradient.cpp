#include <cassert>
#include <cstddef>
#include <gradient.hpp>
#include <iostream>
#include <machine.hpp>
#include <matMath.hpp>
#include <matrix.hpp>
#include <ostream>
#include <string>
#include <unistd.h>
gradient::gradient(machine *mach) : mach(mach){};
gradient::~gradient(){};
matrix gradient::inferLayer(matrix input, std::size_t layerIndex) {
    matrix &weights = mach->layers.at(layerIndex).at(0);
    matrix &bias = mach->layers.at(layerIndex).at(1);
    matrix ret = input;
    ret.transpose();
    ret = ret * weights;
    ret.transpose();
    ret = MM::addMat(ret, bias);
    linearLayers.at(layerIndex).Z = ret;
    ret.relu();
    linearLayers.at(layerIndex).A = ret;
    return ret;
}
void gradient::addLinearLayer(std::array<matrix, 2> layer, std::size_t layerLevel) {
    matrixDimensions dims = layer.at(1).getDimensions();
    matrix Z = matrix(dims);
    matrix A = matrix(dims);
    linearLayer ret = {.A = A, .Z = Z, .layer_dx = matrix({1, 1}), .forward_dx = matrix({1, 1}), .layerLevel = 0};
    ret.layerLevel = layerLevel;
    linearLayers.push_back(ret);
}
void warn(float num, std::string str) {
    if (num < 1E-4) {
        std::cout << "Warning: " << str << " going to 0\n";
    }
}
matrix gradient::singleLayerWeightGradient(std::size_t layer) {
    int L = 1;
    auto &currLayer = linearLayers.at(layer);
    // coutLayer(currLayer, layer);
    auto &backLayer = linearLayers.at(layer - 1);

    auto &currLayerWeights = mach->layers.at(layer).at(0);
    auto layerdx = matrix(currLayerWeights.getDimensions());
    // std::cout << layerdx.getDimensions().rows << layerdx.getDimensions().cols << "layerdx: \n";
    // layerdx.coutMat();
    // Z.sigmoid_dx();

    if (layer == mach->layers.size() - 1) {
        currLayer.forward_dx = dC_dy;
        for (int x = 0; x < layerdx.getDimensions().cols; x++) {
            for (int y = 0; y < layerdx.getDimensions().rows; y++) {

                //            float dw_dx = Z.getMember(0, x); // this is post derivative sigmoid

                float dw_dx = currLayer.forward_dx.getMember(0, x);
                dw_dx *= backLayer.A.getMember(0, y); // woop there it is
                layerdx.setMember(x, y, dw_dx);
            }
        }
        currLayer.forward_dx = currLayerWeights;
    }
    currLayer.layer_dx = layerdx;

    return layerdx;
};
matrix gradient::getGradientForWeight(std::size_t layer) { return singleLayerWeightGradient(layer); }
void gradient::computeCost(matrix &y, matrix &t) {
    assert((y.getDimensions().cols == 1 && t.getDimensions().cols == 1) && (t.getDimensions().rows == y.getDimensions().rows) && "attempt to compute cost dimension mismatch");
    int i = 0;
    matrix ret = matrix(y.getDimensions());
    matrix dcdy = matrix(y.getDimensions());
    for (auto &Cn : ret.data) {
        Cn = (y.data.at(i) - t.data.at(i)) * (y.data.at(i) - t.data.at(i));
        dcdy.data.at(i) = 2 * (y.data.at(i) - t.data.at(i));
        i++;
    }
    cost = ret;
    dC_dy = dcdy;
    dC_dyIsReal = true;
    i = 0;
}
void gradient::coutLayer(linearLayer &layer, std::size_t num) {
    std::cout << "Layer " << num << " calc graph\n";
    std::cout << "layer_dx:\n";
    layer.layer_dx.coutMat();
    std::cout << "forward_dx:\n";
    layer.forward_dx.coutMat();
    std::cout << "A:\n";
    layer.A.coutMat();
    std::cout << "Z:\n";
    layer.Z.coutMat();
}
