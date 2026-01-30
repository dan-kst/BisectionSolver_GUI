#ifndef MPI_WORKER_HPP
#define MPI_WORKER_HPP

#include "core/BisectionSolver.hpp"
#include <cstddef>
#include <limits>
#include <mpi.h>
#include <stdexcept>
#include <vector>

namespace Core {
class MpiWorker {
public:
  static void Run();
};

} // namespace Core

#endif
