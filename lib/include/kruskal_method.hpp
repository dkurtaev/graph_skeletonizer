#ifndef INCLUDE_KRUSKAL_METHOD_HPP_
#define INCLUDE_KRUSKAL_METHOD_HPP_

#include <vector>

#include "include/graph.hpp"

class KruskalMethod {
 public:
  static void Process(unsigned n_nodes, const std::vector<Edge>& edges,
                      std::vector<Edge>* spanning_tree_edges);

 private:
  static bool EdgesComparator(const Edge& first, const Edge& second);
};

#endif  // INCLUDE_KRUSKAL_METHOD_HPP_
