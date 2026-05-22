cmake_minimum_required(VERSION 3.23)

project(numbrix9)

add_executable(numbrix9)

target_sources(numbrix9
  PRIVATE
    src/main.cpp
    headers/NumbrixBoard.h
    src/NumbrixBoard.cpp
)