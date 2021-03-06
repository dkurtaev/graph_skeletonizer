#include "include/graph.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

#include "glog/logging.h"

Edge::Edge(unsigned first_node_id, unsigned second_node_id, float weight)
  : weight(weight) {
  nodes[0] = first_node_id;
  nodes[1] = second_node_id;
}

Graph::Graph(unsigned n_nodes, const std::vector<Edge>& edges)
  : n_nodes_(n_nodes), edges_(edges) {}

Graph::Graph(const std::string& file_path) {
  std::ifstream file(file_path.c_str());
  CHECK(file.is_open());

  unsigned n_edges;
  file >> n_nodes_;
  file >> n_edges;
  edges_.resize(n_edges);
  for (unsigned i = 0; i < n_edges; ++i) {
    file >> edges_[i].nodes[0];
    file >> edges_[i].nodes[1];
    file >> edges_[i].weight;
  }
  file.close();
}

void Graph::WriteDot(const std::string& file_path,
                     const std::vector<Edge>& spanning_tree_edges) const {
  std::ofstream file(file_path.c_str());
  file << "graph {\n";

  const unsigned n_edges = edges_.size();
  for (unsigned i = 0; i < n_edges; ++i) {
    std::ostringstream ss;
    ss << edges_[i].nodes[0] << "--" << edges_[i].nodes[1] << "[label=\""
       << edges_[i].weight << "\"";

    bool edge_in_spanning_tree = false;
    for (unsigned j = 0; j < spanning_tree_edges.size(); ++j) {
      const Edge* spanning_tree_edge = &spanning_tree_edges[j];
      if (spanning_tree_edge->nodes[0] == edges_[i].nodes[0] &&
          spanning_tree_edge->nodes[1] == edges_[i].nodes[1] ||
          spanning_tree_edge->nodes[0] == edges_[i].nodes[1] &&
          spanning_tree_edge->nodes[1] == edges_[i].nodes[0]) {
        edge_in_spanning_tree = true;
        break;
      }
    }
    if (edge_in_spanning_tree) {
      ss << ", color=\"red\", fontcolor=\"red\"";
    }
    ss << "];\n";
    file << ss.str();
  }
  file << "}\n";
  file.close();
}

void Graph::GetEdges(std::vector<Edge>* edges) const {
  edges->resize(edges_.size());
  std::copy(edges_.begin(), edges_.end(), edges->begin());
}

unsigned Graph::GetNumberNodes() const {
  return n_nodes_;
}

float Graph::WeightsSum(const std::vector<Edge>& edges) {
  const unsigned n_edges = edges.size();
  float cost = 0;
  for (unsigned i = 0; i < n_edges; ++i) {
    cost += edges[i].weight;
  }
  return cost;
}

bool Graph::CheckEdgesUniqueness(const std::vector<Edge>& edges) {
  std::set<const Edge*> unique_ids;
  const unsigned n_edges = edges.size();
  for (unsigned i = 0; i < n_edges; ++i) {
    if (!unique_ids.insert(&edges[i]).second) {
      return false;
    }
  }
  return true;
}
