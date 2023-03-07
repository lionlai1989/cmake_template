add_executable(test_image test_image.cpp)

target_link_libraries(
  test_image
  GTest::gtest_main
  myimage
)

target_include_directories(test_image PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_compile_features(test_image PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(test_image)
