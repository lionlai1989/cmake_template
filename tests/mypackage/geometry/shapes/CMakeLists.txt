add_executable(
    square_test
    square_test.cpp
)

target_link_libraries(
  square_test
  GTest::gtest_main
  shapes
  metric
)

target_include_directories(square_test PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_compile_features(square_test PRIVATE cxx_std_14)

include(GoogleTest)
gtest_discover_tests(square_test)
