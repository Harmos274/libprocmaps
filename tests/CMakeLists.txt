cmake_minimum_required(VERSION 3.16)

add_executable(procmaps_tests test_parsing.c)

target_include_directories(procmaps_tests PRIVATE .)
target_compile_options(procmaps_tests PRIVATE -W -Wall -Wextra)
target_link_libraries(procmaps_tests procmaps)
