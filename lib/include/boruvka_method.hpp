#ifndef INCLUDE_BORUVKA_METHOD_HPP_
#define INCLUDE_BORUVKA_METHOD_HPP_

#include <vector>

#include "include/graph.hpp"

class BoruvkaMethod {
 public:
  static void Process(unsigned n_nodes, const std::vector<GraphEdge>& edges,
                      std::vector<GraphEdge>* spanning_tree_edges);

 private:
  static unsigned GetGroupId(unsigned node,
                             const std::vector<unsigned>& group_ids);

  static void Merge(unsigned src, unsigned dst,
                    std::vector<unsigned>* group_ids,
                    std::vector<unsigned>* subtree_depths);
};

#endif  // INCLUDE_BORUVKA_METHOD_HPP_
