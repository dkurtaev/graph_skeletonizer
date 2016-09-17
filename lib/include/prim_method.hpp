#ifndef INCLUDE_PRIM_METHOD_HPP_
#define INCLUDE_PRIM_METHOD_HPP_

#include <vector>

#include "include/graph.hpp"

class PrimMethod {
 public:
  static void Process(unsigned n_nodes, const std::vector<Edge>& edges,
                      std::vector<Edge>* spanning_tree_edges);

 private:
  static bool EdgesComparator(const Edge& first, const Edge& second);
};

#endif  // INCLUDE_PRIM_METHOD_HPP_
