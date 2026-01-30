cmake_minimum_required(VERSION 3.20)
project(BisectionSolver VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(MPI REQUIRED)
find_package(PkgConfig REQUIRED)

add_library(lab7_logic
    src/core/MpiSolver.cpp
    src/core/SequentialSolver.cpp
    src/core/BisectionSolver.cpp
)
target_include_directories( lab7_logic PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(lab7_logic
    PRIVATE
    MPI::MPI_CXX
)

add_executable(lab7_app
    src/gui/main.cpp
)

