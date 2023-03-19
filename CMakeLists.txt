cmake_minimum_required(VERSION 3.22)
project(cmake_template VERSION 0.0.1 LANGUAGES CXX)

# Choose either `export`, set() or list() to setup the variable.
# Execute `export CMAKE_PREFIX_PATH="$CMAKE_PREFIX_PATH:/path/to/cmake_project/extern/eigen-3.4.0/"` in shell.
# set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/extern/eigen-3.4.0/")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/extern/eigen-3.4.0/")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extern/eigen-3.4.0/cmake")

list(APPEND CMAKE_PREFIX_PATH "/tmp/xtl-install")
list(APPEND CMAKE_PREFIX_PATH "/tmp/xtensor-install")
list(APPEND CMAKE_PREFIX_PATH "/tmp/xsimd-install")

find_package(xtl REQUIRED)
find_package(xtensor REQUIRED)
find_package(xsimd REQUIRED)
# target_link_libraries(first_example xtensor xtensor::optimize xtensor::use_xsimd)

find_package (Eigen3 3.4.0 REQUIRED)

add_subdirectory(src/mypackage)
add_subdirectory(examples)

include(GNUInstallDirs) # Defines the ${CMAKE_INSTALL_INCLUDEDIR} variable.
# Install the header files. Since header files are not listed as output artifacts, they have
# to be installed separately. 
install (
    DIRECTORY include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# It must be called before adding `tests` subdirectory.
enable_testing()
add_subdirectory(tests)

