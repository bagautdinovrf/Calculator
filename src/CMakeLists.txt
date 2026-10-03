cmake_minimum_required(VERSION 3.5)

project(Calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(calculator_core
    calculator.cpp calculator.h
    mymath.cpp mymath.h
    token.cpp token.h
    )

target_include_directories(calculator_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Calculator main.cpp)
target_link_libraries(Calculator PRIVATE calculator_core)

include(CTest)
if(BUILD_TESTING)
    add_executable(calculator_tests ../tests/calculator_tests.cpp)
    target_link_libraries(calculator_tests PRIVATE calculator_core)
    add_test(NAME calculator_regressions COMMAND calculator_tests)
endif()
