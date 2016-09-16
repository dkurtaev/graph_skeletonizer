#ifndef INCLUDE_RANDOM_SPANNING_TREE_HPP_
#define INCLUDE_RANDOM_SPANNING_TREE_HPP_

#include <vector>

#include "include/graph.hpp"

class RandomSpanningTree {
 public:
  static void Process(unsigned n_nodes, const std::vector<GraphEdge>& edges,
                      std::vector<GraphEdge>* spanning_tree_edges);
};

#endif  // INCLUDE_BORUVKA_METHOD_HPP_
