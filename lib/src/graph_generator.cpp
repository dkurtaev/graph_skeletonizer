#include "include/graph_generator.hpp"

#include <stdlib.h>

#include <utility>
#include <set>
#include <vector>
#include <algorithm>

void GraphGenerator::GenGraph(unsigned n_nodes, std::vector<Edge>* edges) {
  const unsigned min_n_edges = n_nodes - 1;  // For connectivity.
  const unsigned max_n_edges = n_nodes * (n_nodes - 1) / 2;
  int n_edges = rand() % (max_n_edges - min_n_edges + 1) + min_n_edges;
  GenGraph(n_nodes, n_edges, 0.1f, 1.0f, edges);
}

unsigned GraphGenerator::GenGraph(unsigned min_n_nodes, unsigned max_n_nodes,
                                  std::vector<Edge>* edges) {
  int n_nodes = rand() % (max_n_nodes - min_n_nodes + 1) + min_n_nodes;
  GenGraph(n_nodes, edges);
  return n_nodes;
}

void GraphGenerator::GenGraph(unsigned n_nodes, unsigned n_edges,
                              float min_weight, float max_weight,
                              std::vector<Edge>* edges) {
  edges->resize(n_edges);
  // Maximal number of edges - n(n-1)/2, where n - number of nodes.
  // Adjacency matrix:
  //        node_2 node_3 ... node_n
  // node_1    w1    w2   ... w(n-1)
  // node_2          wn   ... w(2n-3)
  //    ...
  // For connectivity lets make path node_1->node_2->node_3->...->node_n
  // But for better randomization, remap each node to other index.
  std::vector<unsigned> nodes_map(n_nodes);
  for (unsigned i = 0; i < n_nodes; ++i) {
    nodes_map[i] = i;
  }
  std::random_shuffle(nodes_map.begin(), nodes_map.end());

  // Build connectivity path.
  Edge* edge = 0;
  for (unsigned i = 1; i < n_nodes; ++i) {
    edge = &edges->operator[](i - 1);
    edge->weight = RandWeight(min_weight, max_weight);
    edge->nodes[0] = nodes_map[i - 1];
    edge->nodes[1] = nodes_map[i];
  }

  if (n_nodes <= 2) return;

  // Fill vector with possible edges.
  // (exclude generated for graph connectivity).
  const unsigned max_n_edges = (n_nodes - 1) * (n_nodes - 2) / 2;
  std::vector<std::pair<unsigned, unsigned> > unsused_edges(max_n_edges);
  unsigned offset = 0;
  for (unsigned from = 0; from < n_nodes - 2; ++from) {
    for (unsigned to = from + 2; to < n_nodes; ++to) {
      unsused_edges[offset].first = from;
      unsused_edges[offset].second = to;
      ++offset;
    }
  }
  std::random_shuffle(unsused_edges.begin(), unsused_edges.end());

  // Select [n_edges - (n_nodes - 1)] edges.
  n_edges -= n_nodes - 1;
  for (unsigned i = 0; i < n_edges; ++i) {
    edge = &edges->operator[](i + n_nodes - 1);
    edge->weight = RandWeight(min_weight, max_weight);
    edge->nodes[0] = nodes_map[unsused_edges[i].first];
    edge->nodes[1] = nodes_map[unsused_edges[i].second];
  }
}

float GraphGenerator::RandWeight(float min_weight, float max_weight,
                                 unsigned n_bins) {
  const float step = (max_weight - min_weight) / (n_bins - 1);
  return min_weight + step * (rand() % n_bins);
}

bool GraphGenerator::GraphParametersIsCorrect(unsigned n_nodes,
                                              unsigned n_edges) {
  return n_nodes - 1 <= n_edges && n_edges <= n_nodes * (n_nodes - 1) / 2;
}
