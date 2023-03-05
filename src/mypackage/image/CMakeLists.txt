add_library(myimage STATIC)
# This needs to be PUBLIC so it can be found by *.cpp in tests/.
target_sources(myimage PUBLIC image.cpp)
target_include_directories(myimage PUBLIC ${CMAKE_SOURCE_DIR}/extern)

target_compile_features(myimage PRIVATE cxx_std_14)
