cmake_minimum_required(VERSION 3.10)
project(HoROS VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(horos_demo src/main.cpp)

target_compile_options(horos_demo PRIVATE -Wall -Wextra)
