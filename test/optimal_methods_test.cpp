#include <math.h>

#include <vector>

#include "gtest/gtest.h"

#include "test/macros.hpp"
#include "include/graph_generator.hpp"
#include "include/boruvka_method.hpp"
#include "include/kruskal_method.hpp"
#include "include/prim_method.hpp"

// Check that optimal methods returns spanning trees with similar weighs sum.
TEST(OptimalMethods, equals_costs) {
  static const unsigned kNumGenerations = 10000;
  static const unsigned kMinNumNodes = 3;
  static const unsigned kMaxNumNodes = 25;
  static const float kZeroLimit = 1e-5f;

  std::vector<Edge> edges;
  std::vector<Edge> spanning_tree;
  for (unsigned iter = 0; iter < kNumGenerations; ++iter) {
    int n_nodes = GraphGenerator::GenGraph(kMinNumNodes, kMaxNumNodes, &edges);

    BoruvkaMethod::Process(n_nodes, edges, &spanning_tree);
    float boruvka_spanning_tree_cost = WeightsSum(spanning_tree);

    KruskalMethod::Process(n_nodes, edges, &spanning_tree);
    float kruskal_spanning_tree_cost = WeightsSum(spanning_tree);

    PrimMethod::Process(n_nodes, edges, &spanning_tree);
    float prim_spanning_tree_cost = WeightsSum(spanning_tree);

    ASSERT_LT(fabs(kruskal_spanning_tree_cost - boruvka_spanning_tree_cost),
              kZeroLimit);
    ASSERT_LT(fabs(prim_spanning_tree_cost - boruvka_spanning_tree_cost),
              kZeroLimit);
    ASSERT_LT(fabs(kruskal_spanning_tree_cost - prim_spanning_tree_cost),
              kZeroLimit);
  }
}
