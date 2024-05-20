#include "graph.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
TEST(graph, init) {
    graph g(140);
    EXPECT_EQ(g.inputSize(), 140);
    EXPECT_EQ(1, g.size());
};
TEST(graph, optionals) {
    graph g(140);
    g.addNode(graph::multiply);
    EXPECT_EQ(g.data.at(0).result.has_value(), false);
    EXPECT_EQ(g.data.at(0).input_dx.has_value(), false);
    EXPECT_EQ(g.data.at(0).constants_dx.has_value(), false);
    EXPECT_EQ(g.data.at(0).constants.has_value(), false);
    EXPECT_EQ(g.data.at(1).result.has_value(), false);
    EXPECT_EQ(g.data.at(1).input_dx.has_value(), false);
    EXPECT_EQ(g.data.at(1).constants_dx.has_value(), false);
    EXPECT_EQ(g.data.at(1).constants.has_value(), false);
}
TEST(graph, multiply) {
    const std::vector<float> A{1, 2, 3, 4, 5, 6, 7, 8};
    const std::vector<float> B{1, 1, 2, 2, 3, 4};
    const std::vector<float> res1Vec{100, 200, 370};
    const std::vector<float> inputs{1, 2, 3, 4};
    const std::vector<float> resVec{30, 70};
    matrix res{2, 1, resVec};
    matrix in{4, 1, inputs};
    matrix constants{2, 4, A};

    EXPECT_EQ(true, res == (constants * in));
    graph g(4);
    g.addNode(graph::multiply, constants);
    g.calculate(in);
    EXPECT_EQ(true, res == g.result());
    graph g2(4);
    matrix constants2{3, 2, B};
    matrix res2{3, 1, res1Vec};
    g2.addNode(graph::multiply, constants);
    g2.addNode(graph::multiply, constants2);
    g2.calculate(in);

    EXPECT_EQ(true, res2 == g2.result());
    g2.result().coutMat("Calc");
    res2.coutMat("predef");
}
TEST(graph, sigmoid) {
    const std::vector<float> vec{-1, 0, 0.5};
    const std::vector<float> ansVec{0.268941, 0.5, 0.622459};
    matrix mid{3, 1, vec};
    matrix res{3, 1, ansVec};
    graph g(3);
    g.addNode(graph::sigmoid);
    g.calculate(mid);
    EXPECT_EQ(true, g.result() == res);
    std::cerr << std::endl;
    g.result().coutMat("sig");
}
TEST(graph, sigmoid_dx) {

    const std::vector<float> vec{-1, 0, 0.5};
    const std::vector<float> ansVec{0.196612, 0.25, 0.235004};
    matrix mid{3, 1, vec};
    matrix res{3, 1, ansVec};

    graph g(3);
    g.addNode(graph::sigmoid);
    g.calculate(mid);
    EXPECT_EQ(true, g.data.at(1).input_dx.value() == res);
    g.data.at(1).input_dx->coutMat("dx");
}
TEST(graph, subtract) {
    const std::vector<float> tens(12, 10);
    const std::vector<float> fives(12, 5);
    matrix A(12, 1, fives);
    matrix in(12, 1, tens);
    matrix B(12, 1, fives);
    matrix res = B;
    matrix res2(12, 1);
    graph g(12);

    g.addNode(graph::subtract, A);
    g.calculate(in);
    std::cerr << std::endl;
    g.result().coutMat("sub");
    EXPECT_EQ(true, g.result() == A);
    graph g2(12);
    g2.addNode(graph::subtract, A);
    g2.addNode(graph::subtract, A);
    g2.calculate(in);
    std::cerr << std::endl;
    g.result().coutMat("sub2");
    EXPECT_EQ(true, g2.result() == res2);
}
TEST(graph, add) {

    const std::vector<float> tens(12, 10);
    const std::vector<float> fives(12, 5);
    matrix A(12, 1, fives);
    matrix in(12, 1, tens);
    matrix B(12, 1, fives);
    matrix res3 = B + A + B;
    matrix res2(12, 1);
    graph g(12);

    g.addNode(graph::add, A);
    g.calculate(A);
    std::cerr << std::endl;
    g.result().coutMat("add");
    EXPECT_EQ(true, g.result() == in);
    graph g2(12);
    g2.addNode(graph::add, A);
    g2.addNode(graph::add, A);
    g2.addNode(graph::add, A);
    g2.calculate(res2);
    std::cerr << std::endl;
    g2.result().coutMat("add2");
    EXPECT_EQ(true, g2.result() == res3);
}
TEST(graph, squared) {
    const std::vector<float> tens(12, 10);
    const std::vector<float> twentyFive(12, 25);
    const std::vector<float> hundred25(12, 625);
    const std::vector<float> fives(12, 5);
    matrix f(12, 1, fives);
    matrix tf(12, 1, twentyFive);
    matrix htf(12, 1, hundred25);
    graph g(12);
    g.addNode(graph::squared);
    g.calculate(f);
    EXPECT_EQ(true, g.result() == tf);
    graph g2(12);
    g2.addNode(graph::squared);
    g2.addNode(graph::squared);
    g2.calculate(f);
    EXPECT_EQ(true, g2.result() == htf);
}
TEST(graph, chaining) {

    const std::vector<float> tens(12, 10);
    const std::vector<float> ones(12, 0.993307);
    const std::vector<float> fives(12, 5);
    const std::vector<float> hundred25(12, 625);

    matrix A(12, 1, fives);
    matrix htf(12, 1, hundred25);
    matrix one(12, 1, ones);
    graph g(12);
    g.addNode(graph::subtract, A);
    g.addNode(graph::add, A);
    g.addNode(graph::sigmoid);
    g.calculate(A);
    std::cerr << std::endl;
    g.result().coutMat("chaining");
    EXPECT_EQ(true, g.result() == one);
}
