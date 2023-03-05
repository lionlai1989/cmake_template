cmake_minimum_required(VERSION 3.22)
project(cmake_template VERSION 0.0.1 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "/home/lai/cmake_template/extern/eigen-3.4.0/cmake")
list(APPEND CMAKE_PREFIX_PATH "/home/lai/cmake_template/extern/eigen-3.4.0")

find_package (Eigen3 3.4 REQUIRED)

add_subdirectory(src/mypackage)
add_subdirectory(examples)

# It must be called before adding `tests` subdirectory.
enable_testing()
add_subdirectory(tests)

# install (
#     DIRECTORY include/
#     DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
# )
