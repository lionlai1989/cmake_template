cmake_minimum_required(VERSION 3.20.0)
project(cmake_template VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(src)
# add_subdirectory(examples)

# It must be called before adding `tests` subdirectory.
enable_testing()
add_subdirectory(tests)

install (
    DIRECTORY include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
