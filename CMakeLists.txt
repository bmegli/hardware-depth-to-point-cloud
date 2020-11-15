cmake_minimum_required(VERSION 3.0)

project(
    hdu
)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_compile_options(-march=native -O3)

add_library(hdu hdu.cpp)
target_link_libraries(hdu Eigen3::Eigen)

install(TARGETS hdu DESTINATION lib)
install(FILES hdu DESTINATION include)

add_executable(hdu-example examples/hdu_example.c)
target_link_libraries(hdu-example hdu)

