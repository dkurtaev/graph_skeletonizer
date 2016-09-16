#include "include/random_spanning_tree.hpp"

#include <stdlib.h>

#include <queue>

void RandomSpanningTree::Process(unsigned n_nodes,
                                 const std::vector<GraphEdge>& edges,
                                 std::vector<GraphEdge>* spanning_tree_edges) {
  spanning_tree_edges->clear();
  spanning_tree_edges->reserve(n_nodes - 1);

  std::vector<bool> nodes_visiting(n_nodes, false);
  std::queue<unsigned> nodes;
  nodes.push(rand() % n_nodes);
  nodes_visiting[nodes.front()] = true;
  do {
    unsigned node_id = nodes.front();
    nodes.pop();

    for (unsigned i = 0; i < edges.size(); ++i) {
      GraphEdge edge = edges[i];
      if (edge.nodes[0] == node_id && !nodes_visiting[edge.nodes[1]]) {
        spanning_tree_edges->push_back(edge);
        nodes.push(edge.nodes[1]);
        nodes_visiting[edge.nodes[1]] = true;
      } else if (edge.nodes[1] == node_id && !nodes_visiting[edge.nodes[0]]) {
        spanning_tree_edges->push_back(edge);
        nodes.push(edge.nodes[0]);
        nodes_visiting[edge.nodes[0]] = true;
      }
    }
  } while (!nodes.empty());
}
