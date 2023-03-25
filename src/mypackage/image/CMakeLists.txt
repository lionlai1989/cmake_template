# Define stb library. Every cpp files need to link to this library.
add_library(stb_library STATIC)
target_sources(stb_library PUBLIC define_stb_image.cpp)
target_include_directories(stb_library PUBLIC ${CMAKE_SOURCE_DIR}/extern)

# set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/eigen-3.4.0)

# list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}"/extern/eigen-3.4.0")
add_executable(test_xtensor test_xtensor.cpp)
add_library(image_eigen STATIC)

target_link_libraries (image_eigen Eigen3::Eigen stb_library)

# This needs to be PUBLIC so it can be found by *.cpp in tests/.
target_sources(image_eigen PUBLIC image_eigen.cpp)
target_include_directories(image_eigen PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/extern)

target_compile_features(image_eigen PRIVATE cxx_std_17)
# NOTE: Using -Werror is not good if underlying libraries have warnings.
target_compile_options(image_eigen PRIVATE -Wall -Wextra -Wpedantic)

add_library(image_xtensor STATIC)

target_link_libraries (image_xtensor xtensor xtensor::optimize xtensor::use_xsimd stb_library)
target_link_libraries (test_xtensor xtensor xtensor::optimize xtensor::use_xsimd)

target_sources(image_xtensor PUBLIC image_xtensor.cpp)
target_include_directories(image_xtensor PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/extern)

target_compile_features(image_xtensor PRIVATE cxx_std_17)
# NOTE: Using -Werror is not good if underlying libraries have warnings.
target_compile_options(image_xtensor PRIVATE -Wall -Wextra -Wpedantic)

