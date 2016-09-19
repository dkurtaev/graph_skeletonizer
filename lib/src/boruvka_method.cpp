#include "include/boruvka_method.hpp"

#include <vector>

#include "include/sets_separator.hpp"

void BoruvkaMethod::Process(unsigned n_nodes,
                            const std::vector<Edge>& edges,
                            std::vector<Edge>* spanning_tree_edges) {
  spanning_tree_edges->clear();
  spanning_tree_edges->reserve(n_nodes - 1);

  // Sets for grouping nodes.
  SetsSeparator separator(n_nodes);

  const unsigned n_edges = edges.size();
  const Edge* edge = 0;
  do {
    std::vector<const Edge*> min_weight_edges(n_nodes, 0);
    for (unsigned i = 0; i < n_edges; ++i) {
      edge = &edges[i];
      unsigned first_group_id = separator.GetSetDestination(edge->nodes[0]);
      unsigned second_group_id = separator.GetSetDestination(edge->nodes[1]);
      if (first_group_id != second_group_id) {
        if (!min_weight_edges[first_group_id] ||
            edge->weight < min_weight_edges[first_group_id]->weight) {
          min_weight_edges[first_group_id] = edge;
        }
        if (!min_weight_edges[second_group_id] ||
            edge->weight < min_weight_edges[second_group_id]->weight) {
          min_weight_edges[second_group_id] = edge;
        }
      }
    }

    for (unsigned i = 0; i < n_nodes; ++i) {
      edge = min_weight_edges[i];
      if (edge && separator.Merge(edge->nodes[0], edge->nodes[1])) {
        spanning_tree_edges->push_back(*edge);
      }
    }
  } while (spanning_tree_edges->size() != n_nodes - 1);
}
