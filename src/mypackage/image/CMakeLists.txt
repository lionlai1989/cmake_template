# set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/eigen-3.4.0)

# list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}"/extern/eigen-3.4.0")

add_library(myimage STATIC)

# target_link_libraries (myimage Eigen3::Eigen)

# This needs to be PUBLIC so it can be found by *.cpp in tests/.
target_sources(myimage PUBLIC image.cpp)
target_include_directories(myimage PUBLIC ${CMAKE_SOURCE_DIR}/extern)

target_compile_features(myimage PRIVATE cxx_std_14)
