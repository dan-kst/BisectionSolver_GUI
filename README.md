# MPI Bisection Solver (Lab 7)

An expert-level C++20 application demonstrating a high-performance, parallelized nonlinear equation solver using the Bisection Method. The project features a modern GUI built with GTKmm 4 and distributed computing capabilities powered by MPI.

## Features

* **Hybrid Architecture**: Rank 0 handles the GTKmm 4 event loop and UI, while Ranks 1-N act as dedicated math workers.
* **Asynchronous Execution**: Calculations run in a background std::jthread with Glib::Dispatcher for thread-safe UI updates, ensuring the window never freezes.
* **Strategy Pattern**: Easily switch between Sequential and MPI Parallel solvers at runtime.
* **Persistence**: Save and load equation parameters using high-performance JSON serialization (nlohmann/json).
* **DRY Logic**: Shared mathematical kernel between sequential and parallel implementations.

## Prerequisites
There are two ways to install dependencies. 

### Manual Installation
You can install all dependencies on your system.
You will need a `C++20` compatible compiler (GCC 11+ or Clang 13+), `CMake`, and the `GTK4` development headers. Also you need `OpenMPI` to enable distributed processing:  

```bash
sudo apt update
sudo apt install build-essential cmake pkg-config libgtkmm-4.0-dev
sudo apt install libopenmpi-dev openmpi-bin
```

### Vcpkg (Recommended)  

You can install `vcpkg` dependency management tool. It will search for `vcpkg.json` manifest file and install all dependencies locally in your build directory.  

## Installation & Building

Clone the repository:
```bash
git clone <repository-url>
cd bisectionsolver_gui
```  
 
Configure with CMake and build the project.
It is recommended to use a build directory:
```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[path_to_vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
```

## Running the Application

### Sequential Mode

You can launch the application directly for single-threaded tasks:
```
./build/lab7_app
```

### MPI Parallel Mode (Required for Lab Task)

To utilize multiple CPU cores/processes, launch using mpiexec. For example, to use 4 processes (1 Master/GUI + 3 Workers):

```bash
mpiexec -n 4 ./build/lab7_app
```
*Note: argument `-n` is number of processor cores you have. More cores — faster calculations.*  

## How to Test (Lab Requirements)

1. Verification:   

	* Set `Interval A` to `0.0`
	* Set `Interval B` to `5.0`
	* Set `Epsilon` to `1e-7`.
	* Run in *Sequential mode*. Note the root.
	* Run in *MPI Parallel mode*. Verify the result is identical.

1. Performance Benchmark:    

	* Increase "Task Count" to a large number (e.g., 20,000,000).
	* Compare the execution time displayed in the status label for both modes.  

1. 5-Second Test:
	* Adjust the Task Count until the Sequential solver takes approximately 5 seconds.
	* Run the same workload in MPI mode to observe the speedup factor.  

## Project Structure
* `include/core/`: Strategy interfaces and bisection math logic.
* `include/gui/`: GTKmm window and constant definitions.
* `src/core/`: Implementations of MPI Master/Worker orchestration.
* `src/gui/`: Main entry point and UI signal handling.
