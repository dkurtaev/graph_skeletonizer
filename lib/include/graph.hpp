#ifndef INCLUDE_GRAPH_HPP_
#define INCLUDE_GRAPH_HPP_

#include <string>
#include <vector>

struct Edge {
  Edge(unsigned first_node_id = 0, unsigned second_node_id = 0,
       float weight = 0);

  unsigned nodes[2];  // Ids of incident graph nodes.
  float weight;
};

// Undirected, weighted graph without loops and without multiple edges.
class Graph {
 public:
  Graph(unsigned n_nodes, const std::vector<Edge>& edges);

  // Reading text file in format:
  // number of nodes (n);
  // number of edges (m);
  // node id, node id, weight (for each edge).
  explicit Graph(const std::string& file_path);

  // Writing .dot file for graph visualization.
  void WriteDot(const std::string& file_path) const;

  void GetEdges(std::vector<Edge>* edges) const;

  unsigned GetNumberNodes() const;

 private:
  unsigned n_nodes_;
  std::vector<Edge> edges_;
};

#endif  // INCLUDE_GRAPH_HPP_
