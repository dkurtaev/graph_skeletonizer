include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty")

set(tests
  methods_test.cpp
  # optimal_methods_test.cpp
  graph_test.cpp
)

foreach(test ${tests})
  get_filename_component(target ${test} NAME_WE)
  add_executable(${target} ${test} main.cpp)
  target_link_libraries(
    ${target}
    gtest
    ${CMAKE_THREAD_LIBS_INIT}
    pthread
    libskeleton
  )
endforeach(test)
