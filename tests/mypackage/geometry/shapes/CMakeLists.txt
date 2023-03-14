add_executable(
    square_test
    square_test.cpp
)

# Is there a way to remove the metric here? Square depends on shapes
# library which depends on metric library. If metric library must be 
# added here, it means I need to dive into the chain of libraries. Why
# can't CMake figure out the dependencies, and I just need to attach
# the direct used library. In this case, shapes library.
target_link_libraries(
  square_test
  GTest::gtest_main
  shapes
  metric
)

target_include_directories(square_test PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_compile_features(square_test PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(square_test)
