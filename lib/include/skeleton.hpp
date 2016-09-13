#ifndef INCLUDE_SKELETON_HPP_
#define INCLUDE_SKELETON_HPP_

#include <vector>

// Edge between spanning trees. Ids of skeleton pointers inside static vector.
class Skeleton;
struct Edge {
  Edge(unsigned id, float weight, Skeleton* from, Skeleton* to);

  unsigned id;
  float weight;
  Skeleton* skeletons[2];
  bool processed;
};

class Skeleton {
 public:
  void SetEdges(const std::vector<Edge*>& edges);

  Edge* GetMinimalWeightedEdge();

  // Merge two skeletons by minimal weighted edge.
  // Pointer to one of them replaced to second pointer (both pointers has
  // similar value after merge).
  // At the end, all pointers are equal (single skeleton).
  static void MergeBy(Edge* merging_edge);

 private:
  std::vector<Edge*> edges_;
};

#endif  // INCLUDE_SKELETON_HPP_
