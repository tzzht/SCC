cmake_minimum_required(VERSION 3.10)

project(SimpleCarChecker)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CPP_SOURCE main.cpp blif2aag.cpp blifparser.cpp converter.cpp merger.cpp blif.cpp aiger.cpp)

add_executable(SCC ${CPP_SOURCE})

target_include_directories(SCC PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
