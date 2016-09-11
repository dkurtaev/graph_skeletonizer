#include "include/graph.hpp"

int main(int argc, char** argv) {
  Graph gr(5);
  gr.WriteDot("./test.dot");
  return 0;
}
