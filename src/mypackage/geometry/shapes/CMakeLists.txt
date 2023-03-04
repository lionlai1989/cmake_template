add_library(shapes STATIC)
# This needs to be PUBLIC so it can be found by *.cpp in tests/.
target_sources(shapes PUBLIC circle.cpp square.cpp)
target_include_directories(shapes PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_compile_features(shapes PRIVATE cxx_std_14)
