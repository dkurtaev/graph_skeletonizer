cmake_minimum_required(VERSION 2.8)

project(graph_skeletonizer)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB sources "./src/*.cpp")
file(GLOB headers "./include/*.hpp")

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory("./3rdparty/glog")

add_executable(${CMAKE_PROJECT_NAME} ${sources} ${headers})
target_link_libraries(
  ${CMAKE_PROJECT_NAME}
  glog
)
