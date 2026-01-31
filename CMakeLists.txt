cmake_minimum_required(VERSION 3.20)
project(SolverBisection VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(MPI REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-4.0)



add_library(lab7_logic
    src/core/logic/MPIWorker.cpp
    src/core/logic/SolverBisection.cpp
    src/core/logic/SolverFactory.cpp
    src/core/strategy/SolverMPI.cpp
    src/core/strategy/SolverSequential.cpp
    src/core/strategy/SolverThreaded.cpp
)
target_include_directories( lab7_logic PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include/core/logic
  ${CMAKE_CURRENT_SOURCE_DIR}/include/core/strategy
)
target_link_libraries(lab7_logic
    PRIVATE
    MPI::MPI_CXX
)


add_executable(lab7_app
    src/gui/main.cpp
    src/gui/MainWindow.cpp
)
target_include_directories( lab7_app PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include/gui
  ${CMAKE_CURRENT_SOURCE_DIR}/include/core/logic
)
target_link_libraries(lab7_app
    PRIVATE
    lab7_logic
    PkgConfig::GTKMM
)
