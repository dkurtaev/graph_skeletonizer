#include <vector>

#include "include/graph.hpp"
#include "include/boruvka_method.hpp"

int main(int argc, char** argv) {
  Graph gr("../test_graph.txt");
  gr.WriteDot("./test.dot");

  std::vector<unsigned> spanning_tree_edges;
  std::vector<float> weights;
  gr.GetWeights(&weights);
  BoruvkaMethod::Process(gr.GetNumberNodes(), weights, &spanning_tree_edges);

  return 0;
}
