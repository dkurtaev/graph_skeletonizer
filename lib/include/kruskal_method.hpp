#ifndef INCLUDE_KRUSKAL_METHOD_HPP_
#define INCLUDE_KRUSKAL_METHOD_HPP_

#include "include/graph.hpp"

class KruskalMethod {
 public:
  static void Process(unsigned n_nodes, const std::vector<GraphEdge>& edges,
                      std::vector<GraphEdge>* spanning_tree_edges);

 private:
   static bool EdgesComparator(const GraphEdge& first, const GraphEdge& second);
};

#endif  // INCLUDE_KRUSKAL_METHOD_HPP_
