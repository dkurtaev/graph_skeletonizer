#include "include/kruskal_method.hpp"

#include <vector>
#include <algorithm>

KruskalMethod::Edge::Edge(unsigned id, float weight, unsigned from,
                          unsigned to)
  : id(id), weight(weight), from(from), to(to) {}

bool KruskalMethod::EdgesComparator(const Edge* first, const Edge* second) {
  return first->weight < second->weight;
}

void KruskalMethod::Process(unsigned n_nodes, const std::vector<float>& weights,
                            std::vector<unsigned>* spanning_tree_edges) {
  spanning_tree_edges->clear();
  std::vector<Edge*> edges;

  unsigned edge_id = 0;
  for (unsigned i = 0; i < n_nodes - 1; ++i) {
    for (unsigned j = i + 1; j < n_nodes; ++j) {
      float weight = weights[edge_id];
      if (weight != 0) {
        edges.push_back(new Edge(edge_id, weight, i, j));
      }
      ++edge_id;
    }
  }

  std::sort(edges.begin(), edges.end(), EdgesComparator);

  // Indicate number of group for each node.
  std::vector<unsigned> node_group_ids(n_nodes);
  // Indices of nodes
  std::vector<unsigned>* groups = new std::vector<unsigned>[n_nodes];
  for (unsigned i = 0; i < n_nodes; ++i) {
    node_group_ids[i] = i;
    groups[i].push_back(i);
  }

  const unsigned n_edges = edges.size();
  for (unsigned i = 0; i < n_edges; ++i) {
    Edge* edge = edges[i];
    unsigned first_group_id = node_group_ids[edge->from];
    unsigned second_group_id = node_group_ids[edge->to];
    if (first_group_id != second_group_id) {
      spanning_tree_edges->push_back(edge->id);

      // Merge groups.
      // Let source group with greater number of nodes.
      std::vector<unsigned>* first_group = &groups[first_group_id];
      std::vector<unsigned>* second_group = &groups[second_group_id];
      unsigned first_group_size = first_group->size();
      unsigned second_group_size = second_group->size();
      if (first_group_size <= second_group_size) {
        for (unsigned i = 0; i < first_group_size; ++i) {
          node_group_ids[first_group->operator[](i)] = second_group_id;
        }
        second_group->insert(second_group->end(), first_group->begin(),
                             first_group->end());
      } else {
        for (unsigned i = 0; i < second_group_size; ++i) {
          node_group_ids[second_group->operator[](i)] = first_group_id;
        }
        first_group->insert(first_group->end(), second_group->begin(),
                            second_group->end());
      }
    }
  }

  delete[] groups;
}
