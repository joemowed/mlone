#include "graph.hpp"
#include <gtest/gtest.h>
using Operation = graph::Operation;
TEST(graph, init) {
    graph g(140);
    EXPECT_EQ(g.inputSize(), 140);
    EXPECT_EQ(1, g.size());
};
TEST(graph, optionals) {
    graph g(140);
    g.addNode(Operation::multiply);
    EXPECT_EQ(g.data.at(0).result.has_value(), false);
    EXPECT_EQ(g.data.at(0).input_dx.has_value(), false);
    EXPECT_EQ(g.data.at(0).constants_dx.has_value(), false);
    EXPECT_EQ(g.data.at(0).constants.has_value(), false);
    EXPECT_EQ(g.data.at(1).result.has_value(), false);
    EXPECT_EQ(g.data.at(1).input_dx.has_value(), false);
    EXPECT_EQ(g.data.at(1).constants_dx.has_value(), false);
    EXPECT_EQ(g.data.at(1).constants.has_value(), false);
}
