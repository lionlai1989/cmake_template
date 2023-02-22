add_library(shapes circle.cpp square.cpp)
target_include_directories(shapes PUBLIC ${CMAKE_SOURCE_DIR})
