#include "include/skeleton.hpp"

#include <algorithm>
#include <vector>

std::vector<Skeleton*> Skeleton::skeletons_;

Skeleton::Skeleton(const std::vector<Edge*>& edges)
  : edges_(edges) {
  skeletons_.push_back(this);
}

Edge* Skeleton::GetMinimalWeightedEdge() {
  const unsigned n_edges = edges_.size();
  if (n_edges == 0) return 0;

  Edge* minimal_weighted_edge = edges_.front();
  Edge* edge = 0;
  for (unsigned i = 1; i < n_edges; ++i) {
    edge = edges_[i];
    if (edge->weight < minimal_weighted_edge->weight) {
      minimal_weighted_edge = edge;
    }
  }
  return minimal_weighted_edge;
}

Edge::Edge(unsigned id, unsigned from, unsigned to, float weight)
  : id(id), weight(weight), from(from), to(to), processed(false) {}

void Skeleton::MergeBy(Edge* merging_edge) {
  const unsigned from_id = merging_edge->from;
  const unsigned to_id = merging_edge->to;

  Skeleton* first = skeletons_[from_id];
  Skeleton* second = skeletons_[to_id];

  std::vector<Edge*> updated_edges;
  unsigned n_edges = first->edges_.size();
  for (unsigned i = 0; i < n_edges; ++i) {
    Edge* edge = first->edges_[i];
    if (skeletons_[edge->from] != second && skeletons_[edge->to] != second) {
      updated_edges.push_back(edge);
    }
  }

  n_edges = second->edges_.size();
  for (unsigned i = 0; i < n_edges; ++i) {
    Edge* edge = second->edges_[i];
    if (skeletons_[edge->from] != first && skeletons_[edge->to] != first) {
      updated_edges.push_back(edge);
    }
  }

  skeletons_[from_id] = first;
  skeletons_[to_id] = first;
  first->edges_.resize(updated_edges.size());
  std::copy(updated_edges.begin(), updated_edges.end(), first->edges_.begin());
}
