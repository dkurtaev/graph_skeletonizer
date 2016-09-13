#include <vector>

#include "gtest/gtest.h"

#include "test/macros.hpp"
#include "include/random_spanning_tree.hpp"

TEST(RandomSpanningTree, spanning_tree_correctness) {
  static const unsigned kNumGenerations = 10000;
  static const unsigned kMinNumNodes = 3;
  static const unsigned kMaxNumNodes = 25;

  std::vector<float> weights;
  std::vector<unsigned> spanning_tree;
  for (unsigned iter = 0; iter < kNumGenerations; ++iter) {
    int n_nodes = rand() % (kMaxNumNodes - kMinNumNodes + 1) + kMinNumNodes;
    GenGraph(n_nodes, &weights);
    RandomSpanningTree::Process(n_nodes, weights, &spanning_tree);
    ASSERT_EQ(spanning_tree.size(), n_nodes - 1);
    ASSERT_TRUE(CheckEdgesUniqueness(weights.size(), spanning_tree));
  }
}
