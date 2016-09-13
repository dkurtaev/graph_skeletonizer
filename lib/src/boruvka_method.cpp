#include "include/boruvka_method.hpp"

#include <vector>

#include "glog/logging.h"

#include "include/skeleton.hpp"

void BoruvkaMethod::Process(unsigned n_nodes, const std::vector<float>& weights,
                            std::vector<unsigned>* spanning_tree_edges) {
  spanning_tree_edges->clear();
  std::vector<Edge*> all_edges;  // Store created edges for memory releasing.
  std::vector<Edge*>* edges = new std::vector<Edge*>[n_nodes];

  std::vector<Skeleton*> skeletons(n_nodes);
  for (unsigned i = 0; i < n_nodes; ++i) {
    skeletons[i] = new Skeleton();
  }

  unsigned weights_offset = 0;
  for (unsigned i = 0; i < n_nodes - 1; ++i) {
    for (unsigned j = i + 1; j < n_nodes; ++j) {
      float weight = weights[weights_offset];
      if (weight != 0) {
        unsigned edge_id = weights_offset;
        Edge* edge = new Edge(edge_id, weight, skeletons[i], skeletons[j]);
        edges[i].push_back(edge);
        edges[j].push_back(edge);
        all_edges.push_back(edge);
      }
      ++weights_offset;
    }
  }

  for (unsigned i = 0; i < n_nodes; ++i) {
    skeletons[i]->SetEdges(edges[i]);
  }

  std::vector<Edge*> minimal_weighted_edges;
  do {
    minimal_weighted_edges.clear();
    for (unsigned i = 0; i < n_nodes; ++i) {
      Edge* edge = skeletons[i]->GetMinimalWeightedEdge();
      if (edge != 0 && !edge->processed) {
        minimal_weighted_edges.push_back(edge);
        edge->processed = true;
        spanning_tree_edges->push_back(edge->id);
      }
    }

    unsigned n_edges = minimal_weighted_edges.size();
    for (unsigned i = 0; i < n_edges; ++i) {
      Skeleton::MergeBy(minimal_weighted_edges[i]);
    }
  } while (!minimal_weighted_edges.empty());
  CHECK_EQ(spanning_tree_edges->size(), n_nodes - 1);

  for (unsigned i = 0; i < n_nodes; ++i) {
    delete skeletons[i];
  }

  unsigned n_edges = all_edges.size();
  for (unsigned i = 0; i < n_edges; ++i) {
    delete all_edges[i];
  }

  delete[] edges;
}
