#include "core/SequentialSolver.hpp"
#include <vector>

namespace Core::Strategy {

[[nodiscard]] auto
SequentialSolver::Solve(const std::vector<Logic::Params> &tasks)
    -> std::vector<Logic::Result> {
  std::vector<Logic::Result> results;
  results.reserve(tasks.size());

  for (const auto &task : tasks) {
    results.push_back(Logic::BisectionSolver::Solve(task));
  }
  return results;
}

[[nodiscard]] auto SequentialSolver::GetType() const -> Strategy::Type {
  return Strategy::Type::Sequential;
}

} // namespace Core::Strategy
