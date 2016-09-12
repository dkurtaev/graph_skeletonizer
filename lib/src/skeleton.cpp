#include "include/skeleton.hpp"

#include <algorithm>
#include <vector>

#include "glog/logging.h"

std::vector<Skeleton*> Skeleton::skeletons_;

Skeleton::Skeleton(const std::vector<Edge*>& edges)
  : edges_(edges) {
  skeletons_.push_back(this);
  for (unsigned i = 0; i < edges.size(); ++i) {
    CHECK(edges[i]->from == skeletons_.size() - 1 ||
          edges[i]->to == skeletons_.size() - 1);
  }
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

  CHECK(from_id != to_id);
  CHECK(first != second);

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

  first->edges_.resize(updated_edges.size());
  std::copy(updated_edges.begin(), updated_edges.end(), first->edges_.begin());

  unsigned n_skeletons = skeletons_.size();
  for (int i = 0; i < n_skeletons; ++i) {
    if (skeletons_[i] == first || skeletons_[i] == second) {
      skeletons_[i] = first;
    }
  }
}

void Skeleton::Reset() {
  skeletons_.clear();
}
