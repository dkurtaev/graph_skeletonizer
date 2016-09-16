cmake_minimum_required(VERSION 2.8)

project(skeletonizer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(OpenCV REQUIRED)

file(GLOB sources "./*.cpp")

include_directories(
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME}
  ${OpenCV_LIBRARIES}
  glog
  libskeleton
)
