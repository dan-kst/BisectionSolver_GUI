#ifndef MPI_WORKER_HPP
#define MPI_WORKER_HPP

#include "SolverBisection.hpp"
#include <cstddef>
#include <limits>
#include <mpi.h>
#include <stdexcept>
#include <vector>

namespace Core::Logic {
class MPIWorker {
public:
  static void Run();
};

} // namespace Core::Logic

#endif
