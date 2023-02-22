add_subdirectory(metric)
add_subdirectory(geometry)

# add_library(calc_area calc_area.cpp)
# target_include_directories(calc_area PUBLIC ${CMAKE_SOURCE_DIR})

add_library(calc_obj OBJECT calc.cpp)
target_include_directories(calc_obj INTERFACE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)
set_target_properties(calc_obj PROPERTIES
    PUBLIC_HEADER src/include/src/calc.hpp
    POSITION_INDEPENDENT_CODE 1
)

add_library(calc_shared SHARED)
target_link_libraries(calc_shared calc_obj)
add_library(calc_static STATIC)
target_link_libraries(calc_static calc_obj)
