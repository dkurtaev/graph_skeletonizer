#include <fstream>
#include <string>

#include "gtest/gtest.h"

#include "test/macros.hpp"
#include "include/graph.hpp"

TEST(Graph, reading_from_file) {
  static const unsigned kNumGenerations = 50;
  static const unsigned kMinNumNodes = 3;
  static const unsigned kMaxNumNodes = 25;

  for (unsigned iter = 0; iter < kNumGenerations; ++iter) {
    int n_nodes = rand() % (kMaxNumNodes - kMinNumNodes + 1) + kMinNumNodes;
    const unsigned kMinNumEdges = n_nodes - 1;  // For connectivity.
    const unsigned kMaxNumEdges = n_nodes * (n_nodes - 1) / 2;
    int n_edges = rand() % (kMaxNumEdges - kMinNumEdges + 1) + kMinNumEdges;

    std::vector<GraphEdge> target_edges;
    GenGraph(n_nodes, n_edges, &target_edges);

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
    std::vector<GraphEdge> received_edges;
    graph.GetEdges(&received_edges);

    ASSERT_EQ(n_edges, received_edges.size());
    for (int i = 0; i < n_edges; ++i) {
      ASSERT_EQ(target_edges[i].nodes[0], received_edges[i].nodes[0]);
      ASSERT_EQ(target_edges[i].nodes[1], received_edges[i].nodes[1]);
      ASSERT_EQ(target_edges[i].weight, received_edges[i].weight);
    }
  }
}
