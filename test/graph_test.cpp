#include <fstream>
#include <string>

#include "gtest/gtest.h"

#include "include/graph.hpp"

TEST(Graph, reading_from_file) {
  static const unsigned kNumGenerations = 50;
  static const unsigned kMinNumNodes = 3;
  static const unsigned kMaxNumNodes = 25;
  static const unsigned kMinNumEdges = 0;

  for (unsigned iter = 0; iter < kNumGenerations; ++iter) {
    int n_nodes = rand() % (kMaxNumNodes - kMinNumNodes + 1) + kMinNumNodes;
    const unsigned kMaxNumEdges = n_nodes * (n_nodes - 1) / 2;
    int n_edges = rand() % (kMaxNumEdges - kMinNumEdges + 1) + kMinNumEdges;

    std::vector<GraphEdge> target_edges(n_edges);
    std::vector<bool> edge_exists(n_nodes * n_nodes, false);

    for (int i = 0; i < n_nodes; ++i) {
      edge_exists[i * n_nodes + i] = true;
    }

    for (int i = 0; i < n_edges; ++i) {
      target_edges[i].weight = static_cast<float>(rand() % 100 + 1) / 100;
      unsigned first_node_id;
      unsigned second_node_id;
      do {
        first_node_id = rand() % n_nodes;
        second_node_id = rand() % n_nodes;
      } while (edge_exists[first_node_id * n_nodes + second_node_id]);
      edge_exists[first_node_id * n_nodes + second_node_id] = true;
      edge_exists[second_node_id * n_nodes + first_node_id] = true;
      target_edges[i].nodes[0] = first_node_id;
      target_edges[i].nodes[1] = second_node_id;
    }

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
