add_subdirectory(metric)
add_subdirectory(geometry)

add_library(calc_static STATIC)
target_sources(calc_static PUBLIC calc.cpp)

target_link_libraries(calc_static metric shapes)

target_include_directories(calc_static PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR})

target_include_directories(
    calc_static PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
)

target_compile_features(calc_static PRIVATE cxx_std_14)
