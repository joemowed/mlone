#ifndef gradienthpp
#define gradienthpp
#include <array>
#include <cstddef>
#include <matrix.hpp>
struct linearLayer {
    matrix A;
    matrix Z;
    matrix layer_dx;
    matrix forward_dx;
    std::size_t layerLevel; // the index of the layer in machine.layers
};
class machine;
class gradient {
  public:
    gradient(machine *mach);
    ~gradient();

    void addLinearLayer(std::array<matrix, 2>, std::size_t);
    matrix inferLayer(matrix input, std::size_t layerIndex);
    matrix getGradientForWeight(std::size_t);
    matrix cost = matrix({.rows = 1, .cols = 1});
    void computeCost(matrix &y, matrix &t);
    void coutLayer(linearLayer &, std::size_t);
    std::vector<linearLayer> linearLayers;
    matrix dC_dy = matrix({.rows = 1, .cols = 1});

  private:
    matrix singleLayerWeightGradient(std::size_t layer);
    bool dC_dyIsReal = false;

    machine *mach;
};

#endif // !gradienthpp
