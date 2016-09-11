#include "include/graph.hpp"

int main(int argc, char** argv) {
  Graph gr("./graph_test.txt");
  gr.WriteDot("./test.dot");
  return 0;
}
