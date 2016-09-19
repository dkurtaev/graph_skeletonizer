#include <math.h>

#include <fstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "include/graph_generator.hpp"
#include "include/graph.hpp"

TEST(Graph, reading_from_file) {
  static const unsigned kNumGenerations = 50;
  static const unsigned kMinNumNodes = 3;
  static const unsigned kMaxNumNodes = 25;
  static const float kZeroLimit = 1e-5f;

  for (unsigned iter = 0; iter < kNumGenerations; ++iter) {
    std::vector<Edge> target_edges;
    int n_nodes = GraphGenerator::GenGraph(kMinNumNodes, kMaxNumNodes,
                                           &target_edges);
    int n_edges = target_edges.size();

    // Writing file.
    static const std::string file_path = "./graph_test.txt";
    std::ofstream file(file_path.c_str());
    file << n_nodes << ' ' << n_edges << '\n';
    for (int i = 0; i < n_edges; ++i) {
      file << target_edges[i].nodes[0] << ' ' << target_edges[i].nodes[1] << ' '
           << target_edges[i].weight << '\n';
    }
    file.close();

    // Graph creating.
    Graph graph(file_path);
    std::vector<Edge> received_edges;
    graph.GetEdges(&received_edges);

    ASSERT_EQ(n_edges, received_edges.size());
    for (int i = 0; i < n_edges; ++i) {
      ASSERT_EQ(target_edges[i].nodes[0], received_edges[i].nodes[0]);
      ASSERT_EQ(target_edges[i].nodes[1], received_edges[i].nodes[1]);
      ASSERT_LT(fabs(target_edges[i].weight - received_edges[i].weight),
                kZeroLimit);
    }
  }
}
