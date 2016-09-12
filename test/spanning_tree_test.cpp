#include <vector>
#include <iostream>

#include "gtest/gtest.h"

#include "include/graph.hpp"
#include "include/boruvka_method.hpp"

void GenGraph(unsigned n_nodes, std::vector<float>* weights);

// Add edges for graph connectivity.
void GenPath(unsigned n_nodes, std::vector<float>* weights);

float RandWeight();

TEST(BoruvkaMethod, spanning_tree) {
  static const unsigned kNumGenerations = 1000;
  static const unsigned kMinNumNodes = 5;
  static const unsigned kMaxNumNodes = 10;

  std::vector<float> weights;
  std::vector<unsigned> spanning_tree;
  for (unsigned iter = 0; iter < kNumGenerations; ++iter) {
    int n_nodes = rand() % (kMaxNumNodes - kMinNumNodes + 1) + kMinNumNodes;
    GenGraph(n_nodes, &weights);
    Graph gr(n_nodes, weights);
    gr.WriteDot("./test.dot");
    std::cout << iter << std::endl;
    BoruvkaMethod::Process(n_nodes, weights, &spanning_tree);
  }
}

void GenGraph(unsigned n_nodes, std::vector<float>* weights) {
  const unsigned n_weights = n_nodes * (n_nodes - 1) / 2;

  weights->resize(n_weights);
  std::fill(weights->begin(), weights->end(), 0.0f);

  GenPath(n_nodes, weights);

  for (unsigned i = 0; i < n_weights; ++i) {
    if (weights->operator[](i) == 0 && rand() % 2) {
      weights->operator[](i) = RandWeight();
    }
  }
}

void GenPath(unsigned n_nodes, std::vector<float>* weights) {
  std::vector<unsigned> unvisited_nodes(n_nodes - 1);
  for (unsigned i = 1; i < n_nodes; ++i) {
    unvisited_nodes[i - 1] = i;
  }

  unsigned node_from = 0;
  for (unsigned i = 1; i < n_nodes; ++i) {
    unsigned idx = rand() % unvisited_nodes.size();
    unsigned node_to = unvisited_nodes[idx];
    unvisited_nodes.erase(unvisited_nodes.begin() + idx);

    unsigned weight_offset = 0;
    if (node_from < node_to) {
      weight_offset = (2 * n_nodes - node_from - 1) * node_from / 2 +
                      node_to - node_from - 1;
    } else {
      weight_offset = (2 * n_nodes - node_to - 1) * node_to / 2 +
                      node_from - node_to - 1;
    }
    weights->operator[](weight_offset) = RandWeight();
    node_from = node_to;
  }
}

float RandWeight() {
  return static_cast<float>(rand() % 100 + 1) / 100;
}
