#ifndef THREADED_SOLVER_HPP
#define THREADED_SOLVER_HPP

#include "ISolverStrategy.hpp"
#include "SolverBisection.hpp"
#include <algorithm>
#include <thread>
#include <vector>

namespace Core::Strategy {

/**
 * @class SolverThreaded
 * @brief Multithreaded implementation using C++20 std::jthread.
 * Follows the Strategy pattern to provide shared-memory parallelism.
 */
class SolverThreaded : public ISolverStrategy {
public:
  ~SolverThreaded() override = default;

  [[nodiscard]] auto Solve(const std::vector<Core::Logic::Params> &inputs)
      -> std::vector<Core::Logic::Result> override;

  [[nodiscard]] auto GetType() const -> Type override;

private:
  /**
   * @brief Internal helper to process a specific range of tasks.
   */
  void ProcessChunk(const std::vector<Core::Logic::Params> &inputs,
                    std::vector<Core::Logic::Result> &results,
                    std::size_t start, std::size_t end);
};

} // namespace Core::Strategy

#endif
