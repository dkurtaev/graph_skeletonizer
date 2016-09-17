#include "include/prim_method.hpp"

#include <vector>
#include <algorithm>


bool PrimMethod::EdgesComparator(const Edge& first,
                                 const Edge& second) {
  return first.weight > second.weight;
}

void PrimMethod::Process(unsigned n_nodes,
                         const std::vector<Edge>& graph_edges,
                         std::vector<Edge>* spanning_tree_edges) {
  spanning_tree_edges->clear();
  spanning_tree_edges->reserve(n_nodes - 1);

  std::vector<Edge> edges(graph_edges);
  std::sort(edges.begin(), edges.end(), EdgesComparator);

  // Indicates which nodes are inside spanning tree at the moment.
  std::vector<bool> node_in_spanning_tree(n_nodes, false);
  node_in_spanning_tree[rand() % n_nodes] = true;
  do {
    for (unsigned i = edges.size() - 1; i >= 0; --i) {
      Edge edge = edges[i];
      bool first_node_inside_tree = node_in_spanning_tree[edge.nodes[0]];
      bool second_node_inside_tree = node_in_spanning_tree[edge.nodes[1]];

      if (first_node_inside_tree || second_node_inside_tree) {
        edges.erase(edges.begin() + i);
        if (!first_node_inside_tree || !second_node_inside_tree) {
          spanning_tree_edges->push_back(edge);
          node_in_spanning_tree[edge.nodes[0]] = true;
          node_in_spanning_tree[edge.nodes[1]] = true;
          break;
        }
      }
    }
  } while (spanning_tree_edges->size() != n_nodes - 1);
}
