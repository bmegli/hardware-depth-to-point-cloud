cmake_minimum_required(VERSION 3.0)

project(
    hdu
)

add_compile_options(-march=native -O3)

add_library(hdu hdu.c)
install(TARGETS hdu DESTINATION lib)
install(FILES hdu DESTINATION include)

add_executable(hdu-example examples/hdu_example.c)
target_link_libraries(hdu-example hdu)

