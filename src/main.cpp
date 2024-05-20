#include <cstddef>
#include <iostream>
#include <machine.hpp>
#include <matrix.hpp>
#include <utility>
#include <vector>
std::vector<std::pair<matrix, matrix>> generateXORdata(size_t n) {
    std::vector<std::pair<matrix, matrix>> ret;
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::bernoulli_distribution dist(0.5);
    for (size_t i = 0; i < n; i++) {

        const bool A = dist(gen);
        const bool B = dist(gen);
        const bool C = B != A;
        matrix input(2, 1, std::vector<float>{static_cast<float>(A), static_cast<float>(B)});
        matrix ans(1, 1, std::vector<float>{static_cast<float>(C)});
        ret.push_back(std::pair<matrix, matrix>{input, ans});
    }
    return ret;
}
int main(int argc, char *[]) {
    auto trainingData = generateXORdata(10);
    std::vector<float> inVec(12, 0.6);
    machine mach{2};
    mach.addLayer(3);
    mach.addLayer(1);
    mach.coutMachine();
    mach.train(trainingData, 5E-12, 10);

    return 0;
}
