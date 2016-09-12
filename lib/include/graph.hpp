#ifndef INCLUDE_GRAPH_HPP_
#define INCLUDE_GRAPH_HPP_

#include <string>
#include <vector>

// Undirected, weighted graph without loops and without multiple edges.
// If edge weight is zero - edge is not exists.
class Graph {
 public:
  explicit Graph(unsigned n_nodes, const std::vector<float>& weights);

  // Reading text file in format:
  // number of nodes (n), n(n-1)/2 weights.
  explicit Graph(const std::string& file_path);

  // Writing .dot file for graph visualization.
  void WriteDot(const std::string& file_path) const;

  void GetWeights(std::vector<float>* weights) const;

  unsigned GetNumberNodes() const;

 private:
  unsigned n_nodes_;
  // Contained weighs wij (between i and j nodes):
  // w12, w13, ..., w1n, w23, w24, ..., w2n, ..., w(n-1)n.
  // Totally n(n-1)/2.
  std::vector<float> weights_;
};

#endif  // INCLUDE_GRAPH_HPP_
