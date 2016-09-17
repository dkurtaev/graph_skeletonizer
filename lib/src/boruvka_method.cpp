#include "include/boruvka_method.hpp"

#include <vector>
#include <algorithm>
#include <iostream>

void BoruvkaMethod::Process(unsigned n_nodes,
                            const std::vector<GraphEdge>& graph_edges,
                            std::vector<GraphEdge>* spanning_tree_edges) {
  spanning_tree_edges->clear();
  spanning_tree_edges->reserve(n_nodes - 1);

  // For each node indicate group id.
  std::vector<unsigned> group_ids(n_nodes);
  for (unsigned i = 0; i < n_nodes; ++i) {
    group_ids[i] = i;
  }

  const unsigned n_edges = graph_edges.size();
  const GraphEdge* edge = 0;
  do {
    std::vector<const GraphEdge*> min_weight_edges(n_nodes, 0);
    for (unsigned i = 0; i < n_edges; ++i) {
      edge = &graph_edges[i];
      unsigned first_group_id = GetGroupId(edge->nodes[0], group_ids);
      unsigned second_group_id = GetGroupId(edge->nodes[1], group_ids);
      if (first_group_id != second_group_id) {
        if (!min_weight_edges[first_group_id] ||
            edge->weight < min_weight_edges[first_group_id]->weight ||
            edge->weight == min_weight_edges[first_group_id]->weight &&
            edge->id == min_weight_edges[first_group_id]->id) {
          min_weight_edges[first_group_id] = edge;
        }
        if (!min_weight_edges[second_group_id] ||
            edge->weight < min_weight_edges[second_group_id]->weight ||
            edge->weight == min_weight_edges[second_group_id]->weight &&
            edge->id == min_weight_edges[second_group_id]->id) {
          min_weight_edges[second_group_id] = edge;
        }
      }
    }

    for (unsigned i = 0; i < n_nodes; ++i) {
      edge = min_weight_edges[i];
      if (edge) {
        unsigned first_group_id = GetGroupId(edge->nodes[0], group_ids);
        unsigned second_group_id = GetGroupId(edge->nodes[1], group_ids);
        if (first_group_id != second_group_id) {
          spanning_tree_edges->push_back(*edge);
          Merge(second_group_id, first_group_id, &group_ids);
        }
      }
    }
  } while (spanning_tree_edges->size() != n_nodes - 1);
}

unsigned BoruvkaMethod::GetGroupId(unsigned node,
                                   const std::vector<unsigned>& group_ids) {
  return group_ids[node];
}

void BoruvkaMethod::Merge(unsigned src, unsigned dst,
                          std::vector<unsigned>* group_ids) {
  unsigned src_id = GetGroupId(src, *group_ids);
  unsigned dst_id = GetGroupId(dst, *group_ids);

  const unsigned n_groups = group_ids->size();
  for (unsigned i = 0; i < n_groups; ++i) {
    if (group_ids->operator[](i) == src_id) {
      group_ids->operator[](i) = dst_id;
    }
  }
}
