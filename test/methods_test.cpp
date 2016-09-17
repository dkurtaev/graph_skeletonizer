#include <vector>

#include "gtest/gtest.h"

#include "test/macros.hpp"
#include "include/graph.hpp"
#include "include/boruvka_method.hpp"
#include "include/kruskal_method.hpp"
#include "include/prim_method.hpp"
#include "include/random_spanning_tree.hpp"

void TestCorrectness(void (*Method)(unsigned, const std::vector<Edge>&,
                                    std::vector<Edge>*));

void TestIsBetterThanRandom(void (*Method)(unsigned,
                                           const std::vector<Edge>&,
                                           std::vector<Edge>*));

TEST(BoruvkaMethod, spanning_tree_correctness) {
  TestCorrectness(BoruvkaMethod::Process);
}

TEST(KruskalMethod, spanning_tree_correctness) {
  TestCorrectness(KruskalMethod::Process);
}

TEST(PrimMethod, spanning_tree_correctness) {
  TestCorrectness(PrimMethod::Process);
}

TEST(RandomSpanningTree, spanning_tree_correctness) {
  TestCorrectness(RandomSpanningTree::Process);
}

TEST(BoruvkaMethod, is_better_than_random) {
  TestIsBetterThanRandom(BoruvkaMethod::Process);
}

TEST(KruskalMethod, is_better_than_random) {
  TestIsBetterThanRandom(KruskalMethod::Process);
}

TEST(PrimMethod, is_better_than_random) {
  TestIsBetterThanRandom(PrimMethod::Process);
}

void TestCorrectness(void (*Method)(unsigned, const std::vector<Edge>&,
                                    std::vector<Edge>*)) {
  static const unsigned kNumGenerations = 10000;
  static const unsigned kMinNumNodes = 3;
  static const unsigned kMaxNumNodes = 25;

  std::vector<Edge> edges;
  std::vector<Edge> spanning_tree;
  for (unsigned iter = 0; iter < kNumGenerations; ++iter) {
    int n_nodes = rand() % (kMaxNumNodes - kMinNumNodes + 1) + kMinNumNodes;
    const unsigned kMinNumEdges = n_nodes - 1;  // For connectivity.
    const unsigned kMaxNumEdges = n_nodes * (n_nodes - 1) / 2;
    int n_edges = rand() % (kMaxNumEdges - kMinNumEdges + 1) + kMinNumEdges;
    GenGraph(n_nodes, n_edges, &edges);

    Graph gr(n_nodes, edges);
    gr.WriteDot("./test.dot");

    Method(n_nodes, edges, &spanning_tree);
    ASSERT_EQ(spanning_tree.size(), n_nodes - 1);
    ASSERT_TRUE(CheckEdgesUniqueness(spanning_tree));
  }
}

void TestIsBetterThanRandom(void (*Method)(unsigned,
                                           const std::vector<Edge>&,
                                           std::vector<Edge>*)) {
  static const unsigned kNumGenerations = 10000;
  static const unsigned kMinNumNodes = 3;
  static const unsigned kMaxNumNodes = 25;
  static const float kZeroLimit = 1e-5f;

  std::vector<Edge> edges;
  std::vector<Edge> spanning_tree;
  for (unsigned iter = 0; iter < kNumGenerations; ++iter) {
    int n_nodes = rand() % (kMaxNumNodes - kMinNumNodes + 1) + kMinNumNodes;
    const unsigned kMinNumEdges = n_nodes - 1;  // For connectivity.
    const unsigned kMaxNumEdges = n_nodes * (n_nodes - 1) / 2;
    int n_edges = rand() % (kMaxNumEdges - kMinNumEdges + 1) + kMinNumEdges;
    GenGraph(n_nodes, n_edges, &edges);

    Method(n_nodes, edges, &spanning_tree);
    float method_spanning_tree_cost = WeightsSum(spanning_tree);

    RandomSpanningTree::Process(n_nodes, edges, &spanning_tree);
    float random_spanning_tree_cost = WeightsSum(spanning_tree);

    ASSERT_LT(method_spanning_tree_cost - random_spanning_tree_cost,
              kZeroLimit);
  }
}
