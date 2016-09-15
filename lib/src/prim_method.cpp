#include "include/prim_method.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

PrimMethod::Edge::Edge(unsigned id, float weight, unsigned from,
                          unsigned to)
  : id(id), weight(weight), from(from), to(to) {}

bool PrimMethod::EdgesComparator(const Edge* first, const Edge* second) {
  return first->weight > second->weight;
}

void PrimMethod::Process(unsigned n_nodes, const std::vector<float>& weights,
                         std::vector<unsigned>* spanning_tree_edges) {
  spanning_tree_edges->clear();
  std::vector<Edge*> edges;

  unsigned edge_id = 0;
  for (unsigned i = 0; i < n_nodes - 1; ++i) {
    for (unsigned j = i + 1; j < n_nodes; ++j) {
      float weight = weights[edge_id];
      if (weight != 0) {
        edges.push_back(new Edge(edge_id, weight, i, j));
      }
      ++edge_id;
    }
  }

  std::sort(edges.begin(), edges.end(), EdgesComparator);

  // Indicates which nodes are inside spanning tree at the moment.
  std::vector<bool> node_in_spanning_tree(n_nodes, false);
  node_in_spanning_tree[rand() % n_nodes] = true;

  do {
    for (unsigned i = edges.size() - 1; i >= 0; --i) {
      Edge* edge = edges[i];
      bool first_node_inside_tree = node_in_spanning_tree[edge->from];
      bool second_node_inside_tree = node_in_spanning_tree[edge->to];

      if (first_node_inside_tree || second_node_inside_tree) {
        edges.erase(edges.begin() + i);
        if (!first_node_inside_tree || !second_node_inside_tree) {
          spanning_tree_edges->push_back(edge->id);
          node_in_spanning_tree[edge->from] = true;
          node_in_spanning_tree[edge->to] = true;
          break;
        }
      }
    }
  } while (spanning_tree_edges->size() != n_nodes - 1);
}
