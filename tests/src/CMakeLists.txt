# add_subdirectory(geometry)
# add_subdirectory(metric)

add_executable(calc_test calc_test.cpp)

target_link_libraries(
  calc_test
  GTest::gtest_main
  calc_static
)

target_include_directories(calc_test PUBLIC ${CMAKE_SOURCE_DIR}/include/)
