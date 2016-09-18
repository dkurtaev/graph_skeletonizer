#ifndef TEST_MACROS_HPP_
#define TEST_MACROS_HPP_

#include <set>

#include "include/graph.hpp"

float WeightsSum(const std::vector<Edge>& edges);

// Check that edges has different ids.
bool CheckEdgesUniqueness(const std::vector<Edge>& edges);

#endif  // TEST_MACROS_HPP_


float WeightsSum(const std::vector<Edge>& edges) {
  const unsigned n_edges = edges.size();
  float cost = 0;
  for (unsigned i = 0; i < n_edges; ++i) {
    cost += edges[i].weight;
  }
  return cost;
}

bool CheckEdgesUniqueness(const std::vector<Edge>& edges) {
  std::set<const Edge*> unique_ids;
  const unsigned n_edges = edges.size();
  for (unsigned i = 0; i < n_edges; ++i) {
    if (!unique_ids.insert(&edges[i]).second) {
      return false;
    }
  }
  return true;
}
