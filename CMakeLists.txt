cmake_minimum_required(VERSION 3.0)

project(
    hd2pc
)

add_library(hd2pc SHARED hd2pc.c)
install(TARGETS hd2pc DESTINATION lib)
install(FILES hd2pc DESTINATION include)

add_executable(hd2pc-example examples/hd2pc_example.c)
target_link_libraries(hd2pc-example hd2pc)

