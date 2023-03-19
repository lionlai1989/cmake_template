# set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/eigen-3.4.0)

# list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}"/extern/eigen-3.4.0")

add_library(myimage STATIC)

target_link_libraries (myimage Eigen3::Eigen)

# This needs to be PUBLIC so it can be found by *.cpp in tests/.
target_sources(myimage PUBLIC image.cpp)
target_include_directories(myimage PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/extern)

target_compile_features(myimage PRIVATE cxx_std_17)
# NOTE: Using -Werror is not good if underlying libraries have warnings.
target_compile_options(myimage PRIVATE -Wall -Wextra -Wpedantic)

add_library(image_xtensor STATIC)

target_link_libraries (image_xtensor xtensor xtensor::optimize xtensor::use_xsimd)
target_sources(image_xtensor PUBLIC image_xtensor.cpp)
target_include_directories(image_xtensor PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/extern)

target_compile_features(image_xtensor PRIVATE cxx_std_17)
# NOTE: Using -Werror is not good if underlying libraries have warnings.
target_compile_options(image_xtensor PRIVATE -Wall -Wextra -Wpedantic)

