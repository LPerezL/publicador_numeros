cmake_minimum_required(VERSION 3.16)

project(PublicadorNumeros VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

if(NOT MSVC)
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(publicador main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(publicador PRIVATE Threads::Threads)
