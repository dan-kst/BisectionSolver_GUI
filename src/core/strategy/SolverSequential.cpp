#include "SolverSequential.hpp"
#include <vector>

namespace Core::Strategy {

[[nodiscard]] auto
SolverSequential::Solve(const std::vector<Logic::Params> &tasks)
    -> std::vector<Logic::Result> {
  std::vector<Logic::Result> results;
  results.reserve(tasks.size());

  for (const auto &task : tasks) {
    results.push_back(Logic::SolverBisection::Solve(task));
  }
  return results;
}

[[nodiscard]] auto SolverSequential::GetType() const -> Strategy::Type {
  return Strategy::Type::Sequential;
}

} // namespace Core::Strategy
