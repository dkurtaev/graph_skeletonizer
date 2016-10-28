#include <sys/time.h>

#include <iostream>
#include <string>

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
    "{ rng | random_seed | 324 | Random seed }"
    "{ i | input_file | "" | Graph definition input file }"
    "{ q | quiet | false | Output only times of processing, if true }";

void Measurement(void (*Method)(unsigned, const std::vector<Edge>&,
                                std::vector<Edge>*),
                 unsigned n_nodes, const std::vector<Edge>& edges,
                 std::string header, bool is_quiet);

int main(int argc, char** argv) {
  cv::CommandLineParser parser(argc, argv, kCmdParams);
  if (parser.get<bool>("help")) {
    parser.printParams();
    return 0;
  }

  unsigned n_nodes = parser.get<unsigned>("number_nodes");
  unsigned n_edges = parser.get<unsigned>("number_edges");
  const float min_weight = parser.get<float>("min_weight");
  const float max_weight = parser.get<float>("max_weight");
  const bool use_boruvka = parser.get<bool>("boruvka");
  const bool use_kruskal = parser.get<bool>("kruskal");
  const bool use_prim = parser.get<bool>("prim");
  const bool is_quiet = parser.get<bool>("quiet");
  const std::string input_file = parser.get<std::string>("input_file");

  std::vector<Edge> edges;
  if (input_file == "") {
    srand(parser.get<unsigned>("random_seed"));

    unsigned min_n_edges, max_n_edges;
    GraphGenerator::GetNumberOfEdgesLimits(n_nodes, &min_n_edges, &max_n_edges);
    if (n_edges < min_n_edges || max_n_edges < n_edges) {
      if (!is_quiet) {
        std::cout << "For graph with " << n_nodes << " nodes number of edges "
                  << "should be in [" << min_n_edges << ", " << max_n_edges << "]"
                  << std::endl;
      }
      return 1;
    }

    GraphGenerator::GenGraph(n_nodes, n_edges, min_weight, max_weight, &edges);
    if (!is_quiet) {
      std::cout << "Generated graph with " << n_nodes << " nodes and "
                << n_edges << " edges." << std::endl;
    }
  } else {
    Graph gr(input_file);
    gr.GetEdges(&edges);
    n_nodes = gr.GetNumberNodes();
    n_edges = edges.size();
    if (!is_quiet) {
      std::cout << "Readen graph with " << n_nodes << " nodes and "
                << n_edges << " edges." << std::endl;
    }
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

void Measurement(void (*Method)(unsigned, const std::vector<Edge>&,
                                std::vector<Edge>*),
                 unsigned n_nodes, const std::vector<Edge>& edges,
                 std::string header, bool is_quiet) {
  timeval start_time, end_time;
  std::vector<Edge> spanning_tree;

  gettimeofday(&start_time, 0);
  Method(n_nodes, edges, &spanning_tree);
  gettimeofday(&end_time, 0);

  unsigned elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1e+3 +
                          (end_time.tv_usec - start_time.tv_usec) * 1e-3;
   if (!is_quiet) {
     std::cout << header << elapsed_time << " ms" << std::endl;
     Graph gr(n_nodes, edges);
     gr.WriteDot("./graph.dot", spanning_tree);
   } else {
     std::cout << elapsed_time << std::endl;
   }
}
