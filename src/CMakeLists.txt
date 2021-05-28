cmake_minimum_required(VERSION 3.5)

project(Calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Calculator
    main.cpp
    calculate.cpp calculate.h
    )
