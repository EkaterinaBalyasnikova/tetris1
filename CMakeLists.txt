cmake_minimum_required(VERSION 3.21)
project(tetris1)
set(CMAKE_CXX_STANDARD 20)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS graphics window system)
add_executable(tetris1 main.cpp)
target_link_libraries(tetris1 PUBLIC sfml-graphics sfml-window sfml-system)

