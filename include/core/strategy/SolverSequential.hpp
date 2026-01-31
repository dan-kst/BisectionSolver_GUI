#ifndef SEQUENTIAL_SOLVER_HPP
#define SEQUENTIAL_SOLVER_HPP

#include "ISolverStrategy.hpp"
#include "SolverBisection.hpp"

namespace Core::Strategy {
class SolverSequential : public ISolverStrategy {
public:
  ~SolverSequential() = default;

  [[nodiscard]] auto Solve(const std::vector<Logic::Params> &tasks)
      -> std::vector<Logic::Result> override;

  [[nodiscard]] auto GetType() const -> Strategy::Type override;
};
} // namespace Core::Strategy

#endif
