add_subdirectory(metric)
add_subdirectory(geometry)
add_subdirectory(image)

add_library(calc_static STATIC)
target_sources(calc_static PUBLIC calc.cpp)

target_link_libraries(calc_static metric shapes)

target_include_directories(calc_static PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

target_include_directories(
    calc_static PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
)

target_compile_features(calc_static PRIVATE cxx_std_17)

add_library(rgb2gray_static STATIC)
target_sources(rgb2gray_static PUBLIC rgb2gray.cpp)

target_link_libraries(rgb2gray_static image_eigen image_xtensor)

target_include_directories(rgb2gray_static PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

target_include_directories(
    rgb2gray_static PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
)

target_compile_features(rgb2gray_static PRIVATE cxx_std_17)


include(GNUInstallDirs) # Defines the ${CMAKE_INSTALL_INCLUDEDIR} variable.
install(TARGETS calc_static)
install(TARGETS rgb2gray_static)

add_executable(xtensor_first_example xtensor_first_example.cpp)

target_link_libraries(xtensor_first_example xtensor xtensor::optimize xtensor::use_xsimd)
