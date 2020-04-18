cmake_minimum_required(VERSION 3.16)

project(libprocmaps)

add_library(procmaps STATIC src/parse_procmaps.c)

target_include_directories(procmaps PUBLIC ./include)
target_compile_options(procmaps PRIVATE -W -Wall -Wextra)

if (CMAKE_BUILD_TPYE MATCHES "Release")
    target_compile_options(procmaps PRIVATE -O2)
endif()

install(TARGETS procmaps DESTINATION lib)
install(FILES include/procmaps.h DESTINATION include)
