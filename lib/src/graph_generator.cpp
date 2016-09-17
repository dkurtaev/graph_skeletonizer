#include "include/graph_generator.hpp"

#include <stdlib.h>

#include <utility>
#include <set>
#include <vector>

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
  GenPath(n_nodes, min_weight, max_weight, edges);

  std::set<unsigned> used_edges_hashes;
  for (unsigned i = 0; i < n_nodes - 1; ++i) {
    Edge* edge = &edges->operator[](i);
    used_edges_hashes.insert(GetEdgeHash(edge->nodes[0], edge->nodes[1],
                                         n_nodes));
  }

  n_edges -= edges->size();
  Edge edge;
  for (int i = 0; i < n_edges; ++i) {
    edge.weight = RandWeight(min_weight, max_weight);

    unsigned hash, id_1, id_2;
    do {
      hash = rand() % (n_nodes * n_nodes);
      id_1 = hash / n_nodes;
      id_2 = hash - id_1 * n_nodes;
      hash = GetEdgeHash(id_1, id_2, n_nodes);
    } while (id_1 == id_2 || !used_edges_hashes.insert(hash).second);

    if (rand() & 1) {
      edge.nodes[0] = id_1;
      edge.nodes[1] = id_2;
    } else {
      edge.nodes[0] = id_2;
      edge.nodes[1] = id_1;
    }

    edges->push_back(edge);
  }
}

void GraphGenerator::GenPath(unsigned n_nodes, float min_weight,
                             float max_weight, std::vector<Edge>* edges) {
  edges->clear();

  std::vector<unsigned> unvisited_nodes(n_nodes - 1);
  for (unsigned i = 1; i < n_nodes; ++i) {
    unvisited_nodes[i - 1] = i;
  }

  Edge edge;
  edge.nodes[0] = 0;
  for (unsigned i = 1; i < n_nodes; ++i) {
    unsigned idx = rand() % unvisited_nodes.size();
    edge.nodes[1] = unvisited_nodes[idx];
    unvisited_nodes.erase(unvisited_nodes.begin() + idx);

    edge.weight = RandWeight(min_weight, max_weight);
    edges->push_back(edge);
    edge.nodes[0] = edge.nodes[1];
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

unsigned GraphGenerator::GetEdgeHash(unsigned from, unsigned to,
                                     unsigned n_nodes) {
  if (from > to) {
    std::swap(from, to);
  }
  return from * (2 * n_nodes - from - 2) + to - 1;
}
