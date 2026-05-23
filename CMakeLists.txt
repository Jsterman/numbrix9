cmake_minimum_required(VERSION 3.23)

project(numbrix9)

add_executable(numbrix9)

target_sources(numbrix9
  PRIVATE
    src/main.cpp
)

add_library(numbrix_board)

target_sources(numbrix_board
  PRIVATE
    src/NumbrixBoard.cpp
  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      include
    FILES
      include/NumbrixBoard.h
)

target_link_libraries(numbrix9
  numbrix_board
)