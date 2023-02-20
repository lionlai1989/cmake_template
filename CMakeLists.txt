cmake_minimum_required(VERSION 3.20.0)
project(cmake_template VERSION 0.0.1 LANGUAGES CXX)

enable_testing()


add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)
