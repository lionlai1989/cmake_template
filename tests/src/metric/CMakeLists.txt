# add_library(GTest::GTest INTERFACE IMPORTED)
# target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(
    i2m_test
    i2m_test.cpp
)

target_link_libraries(
  i2m_test
  GTest::gtest_main
  metric
)

include(GoogleTest)
gtest_discover_tests(i2m_test)
