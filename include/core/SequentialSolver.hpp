#ifndef SEQUENTIAL_SOLVER_HPP
#define SEQUENTIAL_SOLVER_HPP

#include "core/BisectionSolver.hpp"
#include "core/ISolverStrategy.hpp"

namespace Core::Strategy {
class SequentialSolver : public ISolverStrategy {
public:
  ~SequentialSolver() = default;

  [[nodiscard]] auto Solve(const std::vector<Logic::Params> &tasks)
      -> std::vector<Logic::Result> override;

  [[nodiscard]] auto GetType() const -> Strategy::Type override;
};
} // namespace Core::Strategy

#endif
