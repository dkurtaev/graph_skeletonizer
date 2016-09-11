#include "include/graph.hpp"

#include <stdlib.h>
#include <string.h>

#include <fstream>

#include <glog/logging.h>

Graph::Graph(unsigned n_nodes, float* weights)
  : n_nodes_(n_nodes) {
  const unsigned n_weights = n_nodes * (n_nodes - 1) / 2;
  weights_ = new float[n_weights];
  memcpy(weights_, weights, sizeof(float) * n_weights);
}

Graph::Graph(const std::string& file_path) {
  std::ifstream file(file_path.c_str());
  CHECK(file.is_open());

  file >> n_nodes_;
  const unsigned n_weights = n_nodes_ * (n_nodes_ - 1) / 2;
  weights_ = new float[n_weights];
  for (unsigned i = 0; i < n_nodes_; ++i) {
    file >> weights_[i];
  }
  file.close();
}

Graph::~Graph() {
  delete[] weights_;
}
