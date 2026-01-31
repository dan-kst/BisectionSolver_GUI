#ifndef I_SOLVER_STRATEGY_HPP
#define I_SOLVER_STRATEGY_HPP

#include "SolverBisection.hpp"
#include <vector>

namespace Core::Strategy {
enum class Type { None, Sequential, MPI, Threaded };

class ISolverStrategy {
public:
  virtual ~ISolverStrategy() = default;

  virtual auto Solve(const std::vector<Logic::Params> &inputs)
      -> std::vector<Logic::Result> = 0;

  virtual auto GetType() const -> Type = 0;
};
} // namespace Core::Strategy

#endif
