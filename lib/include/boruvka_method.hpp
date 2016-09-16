#ifndef INCLUDE_BORUVKA_METHOD_HPP_
#define INCLUDE_BORUVKA_METHOD_HPP_

#include <vector>

#include "include/graph.hpp"

class BoruvkaMethod {
 public:
  static void Process(unsigned n_nodes, const std::vector<GraphEdge>& edges,
                      std::vector<GraphEdge>* spanning_tree_edges);

 private:
  class Skeleton {
   public:
    explicit Skeleton(unsigned id) : id_(id), minimal_weighted_edge_(0) {}

    void AddEdge(GraphEdge* edge);

    GraphEdge* GetMinWeightEdge();

    void MergeWith(Skeleton* skeleton);

   private:
    unsigned id_;
    GraphEdge* minimal_weighted_edge_;
    std::vector<GraphEdge*> edges_from_;
  };
};

#endif  // INCLUDE_BORUVKA_METHOD_HPP_
