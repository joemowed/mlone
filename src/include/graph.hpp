#ifndef GRAPH_KLSDFJSALKJFLKSADJFLKSADHFOIWEHSDNF
#define GRAPH_KLSDFJSALKJFLKSADJFLKSADHFOIWEHSDNF
#include "matrix.hpp"
#include <cstddef>
#include <optional>
#include <vector>
class graph {
  private:
    // input node is 1
    size_t nodeCount = 0;
    const size_t inputWidth;
    void push(size_t currNode);
    void Multiply(size_t currNode);
    void Sigmoid(size_t currNode);
    void Add(size_t currNode);
    void Subtract(size_t currNode);
    void Squared(size_t currNode);

  public:
    enum Operation { input, multiply, sigmoid, add, subtract, squared };

    struct Node {
        Operation operation;
        std::optional<matrix> result;
        std::optional<matrix> constants;
        std::optional<matrix> backprop_dx;
        std::optional<Node *> prevNode;
    };
    std::vector<Node> data;
    graph(size_t inputSize);
    matrix condenseWeights(Node &);
    static std::string getOpString(Operation);
    void addNode(Operation op, const matrix &constants);
    void addNode(Operation op);
    void calculate(const matrix &input);
    size_t size() const;
    size_t inputSize() const;
    matrix result() const;
};

#endif
