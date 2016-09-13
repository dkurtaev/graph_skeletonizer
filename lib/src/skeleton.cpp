#include "include/skeleton.hpp"

#include <algorithm>
#include <vector>

#include "glog/logging.h"

void Skeleton::SetEdges(const std::vector<Edge*>& edges) {
  edges_.resize(edges.size());
  std::copy(edges.begin(), edges.end(), edges_.begin());
}

Edge* Skeleton::GetMinimalWeightedEdge() {
  const unsigned n_edges = edges_.size();
  if (n_edges == 0) return 0;

  Edge* minimal_weighted_edge = edges_.front();
  Edge* edge = 0;
  for (unsigned i = 1; i < n_edges; ++i) {
    edge = edges_[i];
    float w1 = edge->weight;
    float w2 = minimal_weighted_edge->weight;
    if (w1 < w2 || w1 == w2 && edge->id < minimal_weighted_edge->id) {
      minimal_weighted_edge = edge;
    }
  }
  return minimal_weighted_edge;
}

Edge::Edge(unsigned id, float weight, Skeleton* from, Skeleton* to)
  : id(id), weight(weight), processed(false) {
  skeletons[0] = from;
  skeletons[1] = to;
}

void Skeleton::MergeBy(Edge* merging_edge) {
  Skeleton* first = merging_edge->skeletons[0];
  Skeleton* second = merging_edge->skeletons[1];

  CHECK(first != second);

  std::vector<Edge*> updated_edges;
  unsigned n_edges = first->edges_.size();
  for (unsigned i = 0; i < n_edges; ++i) {
    Edge* edge = first->edges_[i];
    if (edge->skeletons[0] != second && edge->skeletons[1] != second) {
      updated_edges.push_back(edge);
    }
  }

  n_edges = second->edges_.size();
  for (unsigned i = 0; i < n_edges; ++i) {
    Edge* edge = second->edges_[i];
    if (edge->skeletons[0] != first && edge->skeletons[1] != first) {
      updated_edges.push_back(edge);
    }

    if (edge->skeletons[0] == second) {
      edge->skeletons[0] = first;
    } else {
      edge->skeletons[1] = first;
    }
  }

  first->edges_.resize(updated_edges.size());
  std::copy(updated_edges.begin(), updated_edges.end(), first->edges_.begin());
}
