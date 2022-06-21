cmake_minimum_required(VERSION 3.21)
project(tetris1)
set(CMAKE_CXX_STANDARD 20)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS graphics window system)

enable_testing()
add_subdirectory(external/doctest)


add_executable(tetris1 main.cpp texture.cpp lib.cpp)

target_link_libraries(tetris1 PUBLIC sfml-graphics sfml-window sfml-system)

add_executable(tests test_tetris.cpp lib.cpp)
target_link_libraries(tests PUBLIC doctest)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images/)



