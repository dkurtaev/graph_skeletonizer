#include "include/boruvka_method.hpp"

#include <vector>
#include <algorithm>
#include <iostream>

void BoruvkaMethod::Process(unsigned n_nodes,
                            const std::vector<GraphEdge>& graph_edges,
                            std::vector<GraphEdge>* spanning_tree_edges) {
  spanning_tree_edges->clear();
  spanning_tree_edges->reserve(n_nodes - 1);

  std::vector<Skeleton*> skeletons(n_nodes);
  for (unsigned i = 0; i < n_nodes; ++i) {
    skeletons[i] = new Skeleton(i);
  }

  std::vector<GraphEdge> edges(graph_edges);
  unsigned n_edges = edges.size();
  for (unsigned i = 0; i < n_edges; ++i) {
    GraphEdge* edge = &edges[i];
    skeletons[edge->nodes[0]]->AddEdge(edge);
    skeletons[edge->nodes[1]]->AddEdge(edge);
  }

  GraphEdge* edge = 0;
  std::vector<GraphEdge*> min_weight_edges;
  do {
    // Collect minimal weighted edges.
    min_weight_edges.clear();
    for (unsigned i = 0; i < n_nodes; ++i) {
      edge = skeletons[i]->GetMinWeightEdge();
      if (edge) {
        min_weight_edges.push_back(edge);
      }
    }
    // Merge skeletons.
    n_edges = min_weight_edges.size();
    for (unsigned i = 0; i < n_edges; ++i) {
      edge = min_weight_edges[i];
      unsigned first_skeleton_id = edge->nodes[0];
      unsigned second_skeleton_id = edge->nodes[1];
      // If not merged already (with previous skeleton).
      if (first_skeleton_id != second_skeleton_id) {
        skeletons[first_skeleton_id]->MergeWith(skeletons[second_skeleton_id]);
        edge->nodes[0] = edge->nodes[1];  // Disable this edge.
        spanning_tree_edges->push_back(graph_edges[edge->id]);
      }
    }
  } while (spanning_tree_edges->size() != n_nodes - 1);

  for (unsigned i = 0; i < n_nodes; ++i) {
    delete skeletons[i];
  }
}

void BoruvkaMethod::Skeleton::AddEdge(GraphEdge* edge) {
  if (!minimal_weighted_edge_ ||
      edge->weight < minimal_weighted_edge_->weight ||
      edge->weight == minimal_weighted_edge_->weight &&
      edge->id < minimal_weighted_edge_->id) {
    minimal_weighted_edge_ = edge;
  }
  edges_from_.push_back(edge);
}

GraphEdge* BoruvkaMethod::Skeleton::GetMinWeightEdge() {
  return minimal_weighted_edge_;
}

void BoruvkaMethod::Skeleton::MergeWith(Skeleton* skeleton) {
  // Remove edges between [this] skeleton and merged.
  minimal_weighted_edge_ = 0;
  GraphEdge* edge = 0;
  unsigned n_edges = edges_from_.size();
  for (unsigned i = 0; i < n_edges; ++i) {
    edge = edges_from_[i];
    if (edge->nodes[0] != skeleton->id_ && edge->nodes[1] != skeleton->id_) {
      AddEdge(edge);  // Push at the end.
    }
  }
  edges_from_.erase(edges_from_.begin(), edges_from_.begin() + n_edges);

  // Add edges from merged skeleton, replace id.
  n_edges = skeleton->edges_from_.size();
  for (unsigned i = 0; i < n_edges; ++i) {
    edge = skeleton->edges_from_[i];
    if (edge->nodes[0] != this->id_ && edge->nodes[1] != this->id_) {
      // Replace ids for external edges.
      if (edge->nodes[0] == skeleton->id_) {
        edge->nodes[0] = this->id_;
      } else {
        edge->nodes[1] = this->id_;
      }
      AddEdge(edge);
    }
  }

  skeleton->minimal_weighted_edge_ = 0;
}
