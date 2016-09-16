#include "include/graph_generator.hpp"

#include <stdlib.h>

#include <set>

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

  std::set<unsigned> used_edges;
  for (unsigned i = 0; i < n_nodes - 1; ++i) {
    GraphEdge* edge = &edges->operator[](i);
    unsigned id_1 = edge->nodes[0];
    unsigned id_2 = edge->nodes[1];
    if (id_1 < id_2) {
      used_edges.insert(id_1 * n_nodes + id_2);
    } else {
      used_edges.insert(id_2 * n_nodes + id_1);
    }
  }

  n_edges = n_edges - edges->size();
  GraphEdge edge;
  edge.id = edges->size();
  for (int i = 0; i < n_edges; ++i) {
    edge.weight = RandWeight(min_weight, max_weight);

    unsigned id_1, id_2;
    bool edge_is_unused = false;
    do {
      id_1 = rand() % n_nodes;
      id_2 = rand() % n_nodes;
      if (id_1 < id_2) {
        edge_is_unused = used_edges.insert(id_1 * n_nodes + id_2).second;
      } else {
        edge_is_unused = used_edges.insert(id_2 * n_nodes + id_1).second;
      }
    } while (id_1 == id_2 || !edge_is_unused);

    edge.nodes[0] = id_1;
    edge.nodes[1] = id_2;

    edges->push_back(edge);
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

bool GraphGenerator::GraphParametersIsCorrect(unsigned n_nodes,
                                              unsigned n_edges) {
  return n_nodes - 1 <= n_edges && n_edges <= n_nodes * (n_nodes - 1) / 2;
}
