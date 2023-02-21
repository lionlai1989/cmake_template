add_library(semicircleruler SHARED semicircle_ruler.cpp)

# Configure the directories to search for header files.
target_include_directories(semicircleruler PUBLIC ${CMAKE_SOURCE_DIR})
# Set the version property.
set_target_properties(semicircleruler PROPERTIES VERSION ${PROJECT_VERSION})
# Set the shared object version property to the project's major version.
set_target_properties(semicircleruler PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

# # Set the public header property to the one with the actual API.
# set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER source/convert.h)
