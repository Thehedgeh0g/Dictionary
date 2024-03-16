cmake_minimum_required(VERSION 3.27)
project(Dictionary)

set(CMAKE_CXX_STANDARD 23)

add_executable(Dictionary main.cpp
        Dictionary.cpp
        Dictionary.h)
