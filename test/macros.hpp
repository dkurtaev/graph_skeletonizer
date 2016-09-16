#ifndef TEST_MACROS_HPP_
#define TEST_MACROS_HPP_

#include <utility>
#include <set>

#include "include/graph.hpp"

void GenGraph(unsigned n_nodes, unsigned n_edges,
              std::vector<GraphEdge>* edges);

// Add edges for graph connectivity.
void GenPath(unsigned n_nodes, std::vector<GraphEdge>* edges);

float RandWeight();

float ComputeTreeCost(const std::vector<float>& weights,
                      const std::vector<unsigned>& spanning_tree);

// Check that edges has different ids.
bool CheckEdgesUniqueness(const std::vector<GraphEdge>& edges);

#endif  // TEST_MACROS_HPP_

void GenGraph(unsigned n_nodes, unsigned n_edges,
              std::vector<GraphEdge>* edges) {
  GenPath(n_nodes, edges);

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
    edge.weight = RandWeight();
    edges->push_back(edge);
    unused_edges.erase(unused_edges.begin() + idx);
    ++edge.id;
  }
}

void GenPath(unsigned n_nodes, std::vector<GraphEdge>* edges) {
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

    edge.weight = RandWeight();
    edges->push_back(edge);
    edge.nodes[0] = edge.nodes[1];
    ++edge.id;
  }
}

float RandWeight() {
  return static_cast<float>(rand() % 100 + 1) / 100;
}

float ComputeTreeCost(const std::vector<float>& weights,
                      const std::vector<unsigned>& spanning_tree) {
  const unsigned n_edges = spanning_tree.size();
  float cost = 0;
  for (unsigned i = 0; i < n_edges; ++i) {
    cost += weights[spanning_tree[i]];
  }
  return cost;
}

bool CheckEdgesUniqueness(const std::vector<GraphEdge>& edges) {
  std::set<unsigned> unique_ids;
  const unsigned n_edges = edges.size();
  for (unsigned i = 0; i < n_edges; ++i) {
    if (!unique_ids.insert(edges[i].id).second) {
      return false;
    }
  }
  return true;
}
