#ifndef INCLUDE_GRAPH_HPP_
#define INCLUDE_GRAPH_HPP_

#include <string>

// Undirected, weighted graph without loops and without multiple edges.
class Graph {
 public:
   Graph(unsigned n_nodes, float* weights);

   // Reading text file in format:
   // number of nodes (n), n(n-1)/2 weights.
   Graph(const std::string& file_path);

   ~Graph();

 private:
   unsigned n_nodes_;
   // Contained weighs wij (between i and j nodes):
   // w12, w13, ..., w1n, w23, w24, ..., w2n, ..., w(n-1)n.
   // Totally n(n-1)/2.
   float* weights_;
};

#endif  // INCLUDE_GRAPH_HPP_
