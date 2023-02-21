add_library(pubsemicircleruler SHARED ../../../src/semicircle_ruler/semicircle_ruler.cpp)

# Configure the directories to search for header files.
target_include_directories(pubsemicircleruler PUBLIC ${CMAKE_SOURCE_DIR})
# Set the version property.
set_target_properties(pubsemicircleruler PROPERTIES VERSION ${PROJECT_VERSION})
# Set the shared object version property to the project's major version.
set_target_properties(pubsemicircleruler PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

# Set the public header property to the one with the actual API.
set_target_properties(pubsemicircleruler PROPERTIES PUBLIC_HEADER semicircle_ruler.h)
