#include "include/graph.hpp"

#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <sstream>
#include <string>

#include "glog/logging.h"

Graph::Graph(unsigned n_nodes, float* weights)
  : n_nodes_(n_nodes) {
  const unsigned n_weights = n_nodes * (n_nodes - 1) / 2;
  weights_ = new float[n_weights];
  if (weights != 0) {
    memcpy(weights_, weights, sizeof(float) * n_weights);
  } else {
    for (unsigned i = 0; i < n_weights; ++i) {
      weights_[i] = static_cast<float>(rand() % 100 + 1) / 100;
    }
  }
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

void Graph::WriteDot(const std::string& file_path) {
  std::ofstream file(file_path.c_str());
  file << "graph {\n";

  unsigned offset = 0;
  for (unsigned i = 1; i < n_nodes_; ++i) {
    for (unsigned j = i; j < n_nodes_; ++j) {
      std::ostringstream ss;
      ss << i << "--" << j + 1 << "[label=\"" << weights_[offset] << "\"];\n";
      file << ss.str();
      ++offset;
    }
  }
  file << "}\n";
  file.close();
}
