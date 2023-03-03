# add_library(GTest::GTest INTERFACE IMPORTED)
# target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(
    square_test
    square_test.cpp
)

target_link_libraries(
  square_test
  GTest::gtest_main
  shapes
)

target_include_directories(square_test PUBLIC ${CMAKE_SOURCE_DIR}/include/ ${CMAKE_SOURCE_DIR}/src/)


include(GoogleTest)
gtest_discover_tests(square_test)
