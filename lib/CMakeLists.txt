cmake_minimum_required(VERSION 2.8)

project(libskeleton)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB sources "./src/*.cpp")
file(GLOB headers "./include/*.hpp")

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}
)

add_library(${PROJECT_NAME} STATIC ${sources} ${headers})
target_link_libraries(${PROJECT_NAME}
  glog
)
