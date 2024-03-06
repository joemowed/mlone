#include "machine.hpp"
#include <cassert>
#include <cmath>
#include <cstdint>
#include <matMath.hpp>
#include <memory>
const auto RAND_MAX_DIMENSION = 100;
const auto FLOAT_ABSOLUTE_ERROR = 10E-4;
#include <cstdlib>
#include <gtest/gtest.h>
#include <matrix.hpp>
#include <ostream>
matrixDimensions genRandDims() {
    const uint32_t rows = std::rand() % RAND_MAX_DIMENSION;
    const uint32_t cols = std::rand() % RAND_MAX_DIMENSION;
    const matrixDimensions ret = {.rows = rows, .cols = cols};
    return ret;
}
std::vector<float> genRandVec(const matrixDimensions dims) {
    std::vector<float> ret;
    ret.resize(dims.cols * dims.rows);
    for (auto &each : ret) {
        each = (std::rand() * 0.002) / std::rand();
    }
    assert(ret.size() == dims.cols * dims.rows);

    return ret;
}
float sig(float val) { return (1 / (1 + expf(-1.0 * val))); }
// Demonstrate some basic assertions.
TEST(matrixTest, dimension) {
    for (int i = 0; i < 2000; i++) {
        const matrixDimensions testMatDims = genRandDims();
        std::unique_ptr<matrix> testMat = std::make_unique<matrix>(testMatDims);

        // Expect two strings not to be equal.
        // Expect equality.
        EXPECT_EQ(testMat->getDimensions().cols, testMatDims.cols);
        EXPECT_EQ(testMat->getDimensions().rows, testMatDims.rows);
    }
}
TEST(matrixTest, vector) {
    std::vector<float> one = {1, 2};
    auto two = one;
    EXPECT_EQ(one.at(1), two.at(1));
}

TEST(matrixTest, transpose) {
    std::vector<float> manualVec = {1, 2, 3, 4, 5, 6};
    matrixDimensions manualDims = {.rows = 2, .cols = 3};
    auto manualMat = std::make_unique<matrix>(manualDims, manualVec);
    EXPECT_EQ(manualDims.cols, manualMat->getDimensions().cols);
    EXPECT_EQ(manualDims.rows, manualMat->getDimensions().rows);
    EXPECT_EQ(manualMat->getMember(0, 0), 1);
    EXPECT_EQ(manualMat->getMember(1, 0), 2);
    EXPECT_EQ(manualMat->getMember(2, 0), 3);
    EXPECT_EQ(manualMat->getMember(0, 1), 4);
    EXPECT_EQ(manualMat->getMember(1, 1), 5);
    EXPECT_EQ(manualMat->getMember(2, 1), 6);
    manualMat->transpose();
    EXPECT_EQ(manualDims.rows, manualMat->getDimensions().cols);
    EXPECT_EQ(manualDims.cols, manualMat->getDimensions().rows);
    EXPECT_EQ(manualMat->getMember(0, 0), 1);
    EXPECT_EQ(manualMat->getMember(0, 1), 2);
    EXPECT_EQ(manualMat->getMember(0, 2), 3);
    EXPECT_EQ(manualMat->getMember(1, 0), 4);
    EXPECT_EQ(manualMat->getMember(1, 1), 5);
    EXPECT_EQ(manualMat->getMember(1, 2), 6);
    manualMat->transpose();

    EXPECT_EQ(manualMat->getMember(0, 0), 1);
    EXPECT_EQ(manualMat->getMember(1, 0), 2);
    EXPECT_EQ(manualMat->getMember(2, 0), 3);
    EXPECT_EQ(manualMat->getMember(0, 1), 4);
    EXPECT_EQ(manualMat->getMember(1, 1), 5);
    EXPECT_EQ(manualMat->getMember(2, 1), 6);
    for (int i = 0; i < 5; i++) {
        const matrixDimensions dims = genRandDims();
        std::unique_ptr<matrix> testMat = std::make_unique<matrix>(dims, genRandVec(dims));

        auto testMat2 = std::make_unique<matrix>(dims, testMat->getData());
        EXPECT_EQ(testMat->getData(), testMat2->getData());
        testMat2->transpose();
        testMat2->transpose();
        EXPECT_EQ(testMat->getData(), testMat2->getData());
    }
}
TEST(matrixTest, multiply) {

    std::vector<float> manualVec = {1, 2, 3, 4, 5, 6};
    matrixDimensions manualDims = {.rows = 2, .cols = 3};
    auto manualMat = matrix(manualDims, manualVec);
    auto manualMat2 = matrix(manualDims, manualVec);
    manualMat2.transpose();
    auto res1 = manualMat2 * manualMat;
    EXPECT_EQ(res1.getMember(0, 0), 17);
    EXPECT_EQ(res1.getMember(1, 0), 22);
    EXPECT_EQ(res1.getMember(2, 0), 27);
    EXPECT_EQ(res1.getMember(0, 1), 22);
    EXPECT_EQ(res1.getMember(1, 1), 29);
    EXPECT_EQ(res1.getMember(2, 1), 36);
    EXPECT_EQ(res1.getMember(0, 2), 27);
    EXPECT_EQ(res1.getMember(1, 2), 36);
    EXPECT_EQ(res1.getMember(2, 2), 45);
    auto res2 = manualMat * manualMat2;
    EXPECT_EQ(res2.getMember(0, 0), 14);
    EXPECT_EQ(res2.getMember(1, 0), 32);
    EXPECT_EQ(res2.getMember(0, 1), 32);
    EXPECT_EQ(res2.getMember(1, 1), 77);
    for (int i = 0; i < 5; i++) {
        auto dims = genRandDims();
        auto vec = genRandVec(dims);
        auto A = matrix(dims, vec);
        auto B = matrix(dims, vec);
        auto C = matrix(dims, vec);
    }
}
TEST(matrixTest, addition) {
    for (int i = 0; i < 10; i++) {
        auto dims = genRandDims();
        std::vector<float> manualVec = genRandVec(dims);
        auto manualMat = matrix(dims, manualVec);
        auto manualMat2 = matrix(dims, manualVec);
        auto res = MM::addMat(manualMat, manualMat2);
        auto res2 = MM::addMat(manualMat2, manualMat);
        int j = 0;
        for (const float &each : manualVec) {
            const float resValue = each * 2;
            EXPECT_EQ(res.data.at(j), resValue);
            EXPECT_EQ(res2.data.at(j), resValue);
            j++;
        }
    }
}
TEST(matrixTest, sigmoid) {
    const matrixDimensions manDims = {.rows = 3, .cols = 1};
    const std::vector<float> manVec = {-10.0, 0, 10};
    auto manMat = matrix(manDims, manVec);
    manMat.sigmoid();
    EXPECT_NEAR(manMat.data.at(0), 0, FLOAT_ABSOLUTE_ERROR);
    EXPECT_NEAR(manMat.data.at(1), 0.5, FLOAT_ABSOLUTE_ERROR);
    EXPECT_NEAR(manMat.data.at(2), 1, FLOAT_ABSOLUTE_ERROR);
    for (int i = 0; i < 10; i++) {
        auto dims = genRandDims();
        std::vector<float> vec = genRandVec(dims);
        auto mat = matrix(dims, vec);
        mat.sigmoid();
        int j = 0;
        for (const float &each : vec) {
            const float resValue = (1 / (1 + expf(-1 * each)));
            EXPECT_EQ(mat.data.at(j), resValue);
            j++;
        }
    }
}

TEST(matrixTest, sigmoid_dx) {
    const matrixDimensions manDims = {.rows = 3, .cols = 1};
    const std::vector<float> manVec = {-10.0, 0, 10};
    auto manMat = matrix(manDims, manVec);
    manMat.sigmoid_dx();
    EXPECT_NEAR(manMat.data.at(0), 0, FLOAT_ABSOLUTE_ERROR);
    EXPECT_NEAR(manMat.data.at(1), 0.25, FLOAT_ABSOLUTE_ERROR);
    EXPECT_NEAR(manMat.data.at(2), 0, FLOAT_ABSOLUTE_ERROR);
    for (int i = 0; i < 10; i++) {
        auto dims = genRandDims();
        std::vector<float> vec = genRandVec(dims);
        auto mat = matrix(dims, vec);
        mat.sigmoid_dx();
        int j = 0;
        for (const float &each : vec) {
            const float currSig = (1 / (1 + expf(-1.0 * each)));
            const float resValue = currSig * (1.0 - currSig);
            EXPECT_EQ(mat.data.at(j), resValue);
            j++;
        }
    }
}
TEST(machineTest, infer) {
    const std::vector<float> inputVec = {2};
    const matrixDimensions inputDims = {1, 1};
    matrix input = matrix(inputDims, inputVec);

    const std::vector<float> hiddenLayerVec = {2};
    const matrixDimensions hiddenLayerDims = {1, 1};
    matrix hiddenLayerWeights = matrix(hiddenLayerDims, hiddenLayerVec);
    matrix hiddenLayerBias = matrix(hiddenLayerDims, hiddenLayerVec);
    machine mach;
    mach.addInputLayer(1);
    mach.addLayer(hiddenLayerWeights, hiddenLayerBias);
    mach.addOutputLayer(1);
    auto res = mach.infer(input);
    float manualCalc;
    manualCalc = sig((2 * 2) + 2);
    EXPECT_NEAR(res.data[0], manualCalc, FLOAT_ABSOLUTE_ERROR);
}
