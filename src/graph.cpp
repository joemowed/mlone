#include "testHelper.hpp"
#include <cstddef>
#include <graph.hpp>
#include <optional>
graph::graph(size_t inputSize) : inputWidth{inputSize} {
    this->data.push_back(Node{input});
    this->nodeCount++;
}
void graph::addNode(Operation op, const matrix &constants) {
    data.push_back(Node{op, std::nullopt, constants, std::nullopt, std::nullopt});
    this->nodeCount++;
}
void graph::addNode(Operation op) {

    data.push_back(Node{op, std::nullopt, std::nullopt, std::nullopt, std::nullopt});
    this->nodeCount++;
}
void graph::calculate(const matrix &input) {
    assertm(input.j() == 1, "Input dimension mismatch, j dimension");
    assertm(input.i() == inputWidth, "Input dimension mismatch, i dimension");
    data.at(0).result = input;
    push(1);
}
void graph::push(size_t currNode) {
    assertm(data.at(currNode - 1).result.has_value() == true, "Attempt to calculate without previous result data");
    switch (data.at(currNode).operation) {
    case input:
        assertm(false, "Pushing on input node");
    case multiply:
        Multiply(currNode);
    case squared:
        Squared(currNode);
    case add:
        Add(currNode);
    case subtract:
        Subtract(currNode);
    case sigmoid:
        Sigmoid(currNode);
    }
}
void graph::Multiply(size_t currNode) {}
void graph::Input(size_t currNode) {}
void graph::Sigmoid(size_t currNode) {}
void graph::Add(size_t currNode) {}
void graph::Subtract(size_t currNode) {}
void graph::Squared(size_t currNode) {}
size_t graph::size() const { return this->nodeCount; }
size_t graph::inputSize() const { return this->inputWidth; }
