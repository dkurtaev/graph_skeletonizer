#ifndef INCLUDE_KRUSKAL_METHOD_HPP_
#define INCLUDE_KRUSKAL_METHOD_HPP_

#include <vector>

class KruskalMethod {
 public:
  // #weights = n_nodes*(n_nodes-1) / 2.
  // Returns edges ids of spanning tree.
  static void Process(unsigned n_nodes, const std::vector<float>& weights,
                      std::vector<unsigned>* spanning_tree_edges);

 private:
   struct Edge {
     Edge(unsigned id, float weight, unsigned from, unsigned to);

     unsigned id;
     float weight;
     unsigned from;
     unsigned to;
   };

   static bool EdgesComparator(const Edge* first, const Edge* second);
};

#endif  // INCLUDE_KRUSKAL_METHOD_HPP_
