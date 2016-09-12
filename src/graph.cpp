#include "include/graph.hpp"

#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include "glog/logging.h"

Graph::Graph(unsigned n_nodes, const std::vector<float>& weights)
  : n_nodes_(n_nodes), weights_(weights) {}

Graph::Graph(const std::string& file_path) {
  std::ifstream file(file_path.c_str());
  CHECK(file.is_open());

  file >> n_nodes_;
  const unsigned n_weights = n_nodes_ * (n_nodes_ - 1) / 2;
  weights_.resize(n_weights);
  for (unsigned i = 0; i < n_weights; ++i) {
    file >> weights_[i];
  }
  file.close();
}

void Graph::WriteDot(const std::string& file_path) const {
  std::ofstream file(file_path.c_str());
  file << "graph {\n";

  unsigned offset = 0;
  for (unsigned i = 1; i < n_nodes_; ++i) {
    for (unsigned j = i; j < n_nodes_; ++j) {
      float weight = weights_[offset++];
      if (weight == 0.0f) continue;

      std::ostringstream ss;
      ss << i << "--" << j + 1 << "[label=\"" << weight << "\"];\n";
      file << ss.str();
    }
  }
  file << "}\n";
  file.close();
}

void Graph::GetWeights(std::vector<float>* weights) const {
  weights->resize(weights_.size());
  std::copy(weights_.begin(), weights_.end(), weights->begin());
}

unsigned Graph::GetNumberNodes() const {
  return n_nodes_;
}
