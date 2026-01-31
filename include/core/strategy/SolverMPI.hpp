#ifndef MPI_SOLVER_HPP
#define MPI_SOLVER_HPP

#include "ISolverStrategy.hpp"
#include "SolverBisection.hpp"
#include <cstddef>
#include <limits>
#include <mpi.h>
#include <stdexcept>

namespace Core::Strategy {
class SolverMPI : public ISolverStrategy {
public:
  ~SolverMPI() = default;

  [[nodiscard]] auto Solve(const std::vector<Logic::Params> &inputs)
      -> std::vector<Logic::Result> override;

  [[nodiscard]] auto GetType() const -> Type override;
};
} // namespace Core::Strategy

#endif
