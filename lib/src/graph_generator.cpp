#include "include/graph_generator.hpp"

#include <stdlib.h>

void GraphGenerator::GenGraph(unsigned n_nodes, std::vector<GraphEdge>* edges) {
  const unsigned min_n_edges = n_nodes - 1;  // For connectivity.
  const unsigned max_n_edges = n_nodes * (n_nodes - 1) / 2;
  int n_edges = rand() % (max_n_edges - min_n_edges + 1) + min_n_edges;
  GenGraph(n_nodes, n_edges, 0.1f, 1.0f, edges);
}

unsigned GraphGenerator::GenGraph(unsigned min_n_nodes, unsigned max_n_nodes,
                                  std::vector<GraphEdge>* edges) {
  int n_nodes = rand() % (max_n_nodes - min_n_nodes + 1) + min_n_nodes;
  GenGraph(n_nodes, edges);
  return n_nodes;
}

void GraphGenerator::GenGraph(unsigned n_nodes, unsigned n_edges,
                              float min_weight, float max_weight,
                              std::vector<GraphEdge>* edges) {
  GenPath(n_nodes, min_weight, max_weight, edges);

  std::vector<std::pair<int, int> > unused_edges;
  for (int from = 0; from < n_nodes - 1; ++from) {
    for (int to = from + 1; to < n_nodes; ++to) {

      bool is_used = false;
      for (int i = 0; i < edges->size(); ++i) {
        GraphEdge edge = edges->operator[](i);
        if (edge.nodes[0] == from && edge.nodes[1] == to ||
            edge.nodes[0] == to && edge.nodes[1] == from) {
          is_used = true;
          break;
        }
      }
      if (!is_used) {
        unused_edges.push_back(std::pair<int, int>(from, to));
      }
    }
  }

  n_edges = n_edges - edges->size();
  GraphEdge edge;
  edge.id = edges->size();
  for (int i = 0; i < n_edges; ++i) {
    unsigned idx = rand() % unused_edges.size();
    edge.nodes[0] = unused_edges[idx].first;
    edge.nodes[1] = unused_edges[idx].second;
    edge.weight = RandWeight(min_weight, max_weight);
    edges->push_back(edge);
    unused_edges.erase(unused_edges.begin() + idx);
    ++edge.id;
  }
}

void GraphGenerator::GenPath(unsigned n_nodes, float min_weight,
                             float max_weight, std::vector<GraphEdge>* edges) {
  edges->clear();

  std::vector<unsigned> unvisited_nodes(n_nodes - 1);
  for (unsigned i = 1; i < n_nodes; ++i) {
    unvisited_nodes[i - 1] = i;
  }

  GraphEdge edge;
  edge.id = 0;
  edge.nodes[0] = 0;
  for (unsigned i = 1; i < n_nodes; ++i) {
    unsigned idx = rand() % unvisited_nodes.size();
    edge.nodes[1] = unvisited_nodes[idx];
    unvisited_nodes.erase(unvisited_nodes.begin() + idx);

    edge.weight = RandWeight(min_weight, max_weight);
    edges->push_back(edge);
    edge.nodes[0] = edge.nodes[1];
    ++edge.id;
  }
}

float GraphGenerator::RandWeight(float min_weight, float max_weight,
                                 unsigned n_bins) {
  const float step = (max_weight - min_weight) / (n_bins - 1);
  return min_weight + step * (rand() % n_bins);
}
