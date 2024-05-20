#include "testHelper.hpp"
#include <cstddef>
#include <graph.hpp>
#include <optional>
graph::graph(size_t inputSize) : inputWidth{inputSize} {
    this->data.push_back(Node{input});
    this->nodeCount = 1;
}
void graph::addNode(Operation op, const matrix &constants) {
    data.push_back(Node{op, std::nullopt, constants});
    this->nodeCount++;
}
void graph::addNode(Operation op) {

    data.push_back(Node{op, std::nullopt, std::nullopt});
    this->nodeCount++;
}
void graph::calculate(const matrix &input) {
    assertm(input.j() == 1, "Input dimension mismatch, j dimension");
    assertm(input.i() == inputWidth, "Input dimension mismatch, i dimension");
    data.at(0).result = input;
    push(1);
}
matrix graph::result() const {
    auto ret = data.at(nodeCount - 1);
    assertm(ret.result.has_value(), "Attempt to get result before calculation");
    return ret.result.value();
}
std::string graph::getOpString(Operation op) {
    switch (op) {
    case input:
        return "input";
    case multiply:
        return "multiply";
    case add:
        return "add";
    case subtract:
        return "subtract";
    case sigmoid:
        return "sigmoid";
    case squared:
        return "squared";
    }
}
void graph::push(size_t currNode) {
    assertm(data.at(currNode - 1).result.has_value() == true, "Attempt to calculate without previous result data");

    switch (data.at(currNode).operation) {
    case graph::input:
        assertm(false, "Pushing on input node");
        break;
    case graph::multiply:
        Multiply(currNode);
        break;
    case graph::squared:
        Squared(currNode);
        break;
    case graph::add:
        Add(currNode);
        break;
    case graph::subtract:
        Subtract(currNode);
        break;
    case graph::sigmoid:
        Sigmoid(currNode);
        break;
    default:
        assertm(false, "Made it to default in graph logic");
        break;
    }
    currNode++;
    if (currNode == nodeCount) {
        return;
    } else {
        push(currNode);
    }
}
void graph::Multiply(size_t currNode) {
    Node &node = data.at(currNode);
    Node &prevNode = data.at(currNode - 1);
    assertm(node.constants.has_value() == true, "Attempt to multiply on node without loaded constants");
    node.result.emplace(node.constants.value() * prevNode.result.value());
}
void graph::Sigmoid(size_t currNode) {

    Node &node = data.at(currNode);
    Node &prevNode = data.at(currNode - 1);
    assertm(node.constants.has_value() == false, "Attempt to sigmoid on node with constants loaded");
    node.result = prevNode.result->sig();
}
void graph::Add(size_t currNode) {

    Node &node = data.at(currNode);
    Node &prevNode = data.at(currNode - 1);
    assertm(node.constants.has_value(), "Attempt to add on node without loaded constants");
    node.result = prevNode.result.value() + node.constants.value();
}
void graph::Subtract(size_t currNode) {

    Node &node = data.at(currNode);
    Node &prevNode = data.at(currNode - 1);
    assertm(node.constants.has_value(), "Attempt to subtract on node without loaded constants");
    node.result = prevNode.result.value() - node.constants.value();
}
void graph::Squared(size_t currNode) {

    Node &node = data.at(currNode);
    Node &prevNode = data.at(currNode - 1);
    const size_t i = prevNode.result->i();
    const size_t j = prevNode.result->j();
    assertm(!node.constants.has_value(), "Attempt to square node with loaded constants");
    matrix ret = prevNode.result.value();
    for (size_t x = 0; x < i; x++) {
        for (size_t y = 0; y < j; y++) {
            ret.at(x, y) = prevNode.result->at(x, y) * prevNode.result->at(x, y);
        }
    }
    node.result = ret;
}
size_t graph::size() const { return this->nodeCount; }
size_t graph::inputSize() const { return this->inputWidth; }
