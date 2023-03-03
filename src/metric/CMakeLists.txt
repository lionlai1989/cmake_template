add_library(metric STATIC)
# This needs to be PUBLIC so it can be found by *.cpp in tests/.
target_sources(metric PUBLIC i2m.cpp)
target_include_directories(metric PUBLIC ${CMAKE_SOURCE_DIR})
