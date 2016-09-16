#include <sys/time.h>

#include <iostream>

#include "opencv2/opencv.hpp"

#include "include/graph_generator.hpp"
#include "include/boruvka_method.hpp"
#include "include/kruskal_method.hpp"
#include "include/prim_method.hpp"

const char* kCmdParams =
    "{ h | help | false | Print this message }"
    "{ n | number_nodes | 5 | Number of graph nodes }"
    "{ m | number_edges | 4 | Number of edges }"
    "{ min_w | min_weight | 0.1  | Lower limit of graph weights }"
    "{ max_w | max_weight | 1.0 | Upper limit of graph weights }"
    "{ boruvka | boruvka | false  | Using Boruvka's method }"
    "{ kruskal | kruskal | false | Using Kruskal's method }"
    "{ prim    | prim | false | Using Prim's method }"
    "{ q | quiet | false | Output only times of processing, if true }";

void Measurement(void (*Method)(unsigned, const std::vector<GraphEdge>&,
                                std::vector<GraphEdge>*),
                 unsigned n_nodes, const std::vector<GraphEdge>& edges,
                 std::string header, bool is_quiet);

int main(int argc, char** argv) {
  cv::CommandLineParser parser(argc, argv, kCmdParams);
  if (parser.get<bool>("help")) {
    parser.printParams();
    return 0;
  }

  const unsigned n_nodes = parser.get<unsigned>("number_nodes");
  const unsigned n_edges = parser.get<unsigned>("number_edges");
  const float min_weight = parser.get<float>("min_weight");
  const float max_weight = parser.get<float>("max_weight");
  const bool use_boruvka = parser.get<bool>("boruvka");
  const bool use_kruskal = parser.get<bool>("kruskal");
  const bool use_prim = parser.get<bool>("prim");
  const bool is_quiet = parser.get<bool>("quiet");

  if (!GraphGenerator::GraphParametersIsCorrect(n_nodes, n_edges)) {
    if (!is_quiet) {
      std::cout << "Incorrect graph parameters: " << n_nodes << " nodes and "
                << n_edges << " edges" << std::endl;
    }
    return 1;
  }

  std::vector<GraphEdge> edges;
  GraphGenerator::GenGraph(n_nodes, n_edges, min_weight, max_weight, &edges);
  if (!is_quiet) {
    std::cout << "Generated graph with " << n_nodes << " nodes and "
              << n_edges << " edges." << std::endl;
  }

  if (use_boruvka) {
    Measurement(BoruvkaMethod::Process, n_nodes, edges, "Boruvka's method: ",
                is_quiet);
  }
  if (use_kruskal) {
    Measurement(KruskalMethod::Process, n_nodes, edges, "Kruskal's method: ",
                is_quiet);
  }
  if (use_prim) {
    Measurement(PrimMethod::Process, n_nodes, edges, "Prim's method: ",
                is_quiet);
  }

  return 0;
}

void Measurement(void (*Method)(unsigned, const std::vector<GraphEdge>&,
                                std::vector<GraphEdge>*),
                 unsigned n_nodes, const std::vector<GraphEdge>& edges,
                 std::string header, bool is_quiet) {
  timeval start_time, end_time;
  std::vector<GraphEdge> spanning_tree;

  gettimeofday(&start_time, 0);
  Method(n_nodes, edges, &spanning_tree);
  gettimeofday(&end_time, 0);

  unsigned elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1e+3 +
                          (end_time.tv_usec - start_time.tv_usec) * 1e-3;
   if (!is_quiet) {
     std::cout << header << elapsed_time << " ms" << std::endl;
   } else {
     std::cout << elapsed_time << std::endl;
   }
}
