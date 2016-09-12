#ifndef INCLUDE_SKELETON_HPP_
#define INCLUDE_SKELETON_HPP_

#include <vector>

// Edge between spanning trees. Ids of skeleton pointers inside static vector.
struct Edge {
  Edge(unsigned id, unsigned from, unsigned to, float weight);

  unsigned id;
  float weight;
  unsigned from;
  unsigned to;
  bool processed;
};

class Skeleton {
 public:
  explicit Skeleton(const std::vector<Edge*>& edges);

  Edge* GetMinimalWeightedEdge();

  // Merge two skeletons by minimal weighted edge. Both pointers inside
  // [skeletons_] vector replaced to similar pointer (once of them) with
  // merged edges.
  // At the end, all pointers are equal (single skeleton).
  static void MergeBy(Edge* merging_edge);

  static void Reset();

 private:
  std::vector<Edge*> edges_;
  static std::vector<Skeleton*> skeletons_;
};

#endif  // INCLUDE_SKELETON_HPP_
