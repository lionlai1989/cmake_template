add_subdirectory(geometry)
add_subdirectory(image)
add_subdirectory(metric)

add_executable(calc_test calc_test.cpp)

target_link_libraries(
  calc_test
  calc_static
  GTest::gtest_main
)

target_include_directories(calc_test PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_compile_features(calc_test PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(calc_test)
