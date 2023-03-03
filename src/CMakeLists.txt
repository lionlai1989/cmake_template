add_subdirectory(metric)
add_subdirectory(geometry)

# add_library(calc_area calc_area.cpp)
# target_include_directories(calc_area PUBLIC ${CMAKE_SOURCE_DIR})

# add_library(calc_obj OBJECT calc.cpp)
# target_include_directories(calc_obj INTERFACE
#   "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
#   "$<INSTALL_INTERFACE:include>"
# )
# set_target_properties(calc_obj PROPERTIES
#     PUBLIC_HEADER src/include/src/calc.hpp
#     POSITION_INDEPENDENT_CODE 1
# )

# add_library(calc_shared SHARED)
# target_link_libraries(calc_shared calc_obj)
# add_library(calc_static STATIC)
# target_link_libraries(calc_static calc_obj)


add_library(calc_static STATIC)
target_sources(calc_static PUBLIC calc.cpp)

target_link_libraries(calc_static metric shapes)
# Specify the include directories for the target named `ch4_ex02_static`
target_include_directories(calc_static PUBLIC ${CMAKE_SOURCE_DIR}/include geometry)

target_include_directories(
    calc_static PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
)

# Request compile features for target named `ch4_ex02_static`.
# Requested `cxx_std_11` feature determines the minimum C++ standard required
# to build this target. It's PRIVATE, since it is a build-time requirement only.
target_compile_features(calc_static PRIVATE cxx_std_14)

# include(GNUInstallDirs) # Defines the ${CMAKE_INSTALL_INCLUDEDIR} variable.
# Make executable target `ch4_ex02_static` installable. As mentioned before
# in Chapter 4 content, this will only install the output artifacts produced by the target.
# install(TARGETS calc_static)
# Install the header files. Since header files are not listed as output artifacts, they have
# to be installed separately. 
# install (
#     DIRECTORY include/
#     DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
# )
