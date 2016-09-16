cmake_minimum_required(VERSION 2.8)

project(graph_skeletonizer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
  ${CMAKE_SOURCE_DIR}
  "./lib"
)

add_subdirectory("./3rdparty/glog")
add_subdirectory("./3rdparty/googletest")
add_subdirectory("./lib")
add_subdirectory("./test")
add_subdirectory("./tools")
