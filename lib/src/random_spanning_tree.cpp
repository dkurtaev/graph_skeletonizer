#include "include/random_spanning_tree.hpp"

#include <stdlib.h>

#include <queue>

void RandomSpanningTree::Process(unsigned n_nodes,
                                 const std::vector<float>& weights,
                                 std::vector<unsigned>* spanning_tree_edges) {
  spanning_tree_edges->clear();
  spanning_tree_edges->reserve(n_nodes - 1);

  std::vector<bool> nodes_visiting(n_nodes, false);
  std::queue<unsigned> nodes;
  nodes.push(rand() % n_nodes);
  nodes_visiting[nodes.front()] = true;
  do {
    unsigned node_id = nodes.front();
    nodes.pop();

    unsigned edge_id = node_id;
    for (unsigned i = 0; i < node_id; ++i) {
      if (weights[edge_id] != 0 && !nodes_visiting[i]) {
        spanning_tree_edges->push_back(edge_id);
        nodes.push(i);
        nodes_visiting[i] = true;
      }
      edge_id += n_nodes - 1 - i;
    }
    for (unsigned i = 0; i < n_nodes - node_id - 1; ++i) {
      if (weights[edge_id] != 0 && !nodes_visiting[node_id + i + 1]) {
        spanning_tree_edges->push_back(edge_id);
        nodes.push(node_id + i + 1);
        nodes_visiting[node_id + i + 1] = true;
      }
      ++edge_id;
    }
  } while (!nodes.empty());
}
