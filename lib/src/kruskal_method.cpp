#include "include/kruskal_method.hpp"

#include <vector>
#include <algorithm>

#include "include/sets_separator.hpp"

bool KruskalMethod::EdgesComparator(const Edge& first, const Edge& second) {
  return first.weight < second.weight;
}

void KruskalMethod::Process(unsigned n_nodes,
                            const std::vector<Edge>& graph_edges,
                            std::vector<Edge>* spanning_tree_edges) {
  spanning_tree_edges->clear();
  spanning_tree_edges->reserve(n_nodes - 1);

  std::vector<Edge> edges(graph_edges);
  std::sort(edges.begin(), edges.end(), EdgesComparator);

  // Sets for grouping nodes.
  SetsSeparator separator(n_nodes);

  const unsigned n_edges = graph_edges.size();
  const Edge* edge = 0;
  unsigned n_tree_edges = 0;
  for (unsigned i = 0; i < n_edges && n_tree_edges < n_nodes - 1; ++i) {
    edge = &edges[i];
    if (separator.Merge(edge->nodes[0], edge->nodes[1])) {
      ++n_tree_edges;
      spanning_tree_edges->push_back(*edge);
    }
  }
}
