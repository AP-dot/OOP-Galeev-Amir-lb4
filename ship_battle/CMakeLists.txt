cmake_minimum_required(VERSION 3.20)
set(CMAKE_CPP_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(battle)

include_directories("./src/headers")

aux_source_directory("./src/source" SRC)

configure_file(${CMAKE_SOURCE_DIR}/save.json ${CMAKE_BINARY_DIR}/save.json COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/commands.json ${CMAKE_BINARY_DIR}/commands.json COPYONLY)

add_executable(battle
  ./src/main.cpp
  ${SRC}
)