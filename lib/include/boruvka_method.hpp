#ifndef INCLUDE_BORUVKA_METHOD_HPP_
#define INCLUDE_BORUVKA_METHOD_HPP_

#include <vector>

class BoruvkaMethod {
 public:
  // #weights = n_nodes*(n_nodes-1) / 2.
  // Returns edges ids of spanning tree.
  static void Process(unsigned n_nodes, const std::vector<float>& weights,
                      std::vector<unsigned>* spanning_tree_edges);

 private:
};

#endif  // INCLUDE_BORUVKA_METHOD_HPP_
