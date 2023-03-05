add_executable(rgb2gray rgb2gray.cpp)

target_link_libraries(
  rgb2gray
  myimage
)

target_include_directories(rgb2gray PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_compile_features(rgb2gray PRIVATE cxx_std_14)
