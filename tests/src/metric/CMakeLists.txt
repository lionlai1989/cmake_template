add_executable(i2m_test i2m_test.cpp)

target_link_libraries(
  i2m_test
  GTest::gtest_main
  metric
)

target_include_directories(i2m_test PUBLIC ${CMAKE_SOURCE_DIR})

target_compile_features(i2m_test PRIVATE cxx_std_14)

include(GoogleTest)
gtest_discover_tests(i2m_test)
