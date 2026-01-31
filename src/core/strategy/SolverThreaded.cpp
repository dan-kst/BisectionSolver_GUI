#include "SolverThreaded.hpp"

namespace Core::Strategy {

[[nodiscard]] auto
SolverThreaded::Solve(const std::vector<Core::Logic::Params> &inputs)
    -> std::vector<Core::Logic::Result> {
  const std::size_t total_tasks = inputs.size();
  std::vector<Core::Logic::Result> all_results(total_tasks);

  if (total_tasks == 0) {
    return all_results;
  }

  // Determine number of threads (hardware concurrency)
  const unsigned int num_threads =
      std::max(1U, std::thread::hardware_concurrency());
  const std::size_t chunk_size = total_tasks / num_threads;

  std::vector<std::jthread> workers;
  workers.reserve(num_threads);

  for (unsigned int i = 0; i < num_threads; ++i) {
    std::size_t start = i * chunk_size;
    // Ensure the last thread takes any remaining tasks
    std::size_t end =
        (i == num_threads - 1) ? total_tasks : (i + 1) * chunk_size;

    // Launch worker thread using jthread (RAII)
    workers.emplace_back(&SolverThreaded::ProcessChunk, this, std::cref(inputs),
                         std::ref(all_results), start, end);
  }
  workers.clear();

  return all_results;
}

[[nodiscard]] auto SolverThreaded::GetType() const -> Type {
  return Type::Threaded; // You will need to add 'Threaded' to the Type enum
}

void SolverThreaded::ProcessChunk(
    const std::vector<Core::Logic::Params> &inputs,
    std::vector<Core::Logic::Result> &results, std::size_t start,
    std::size_t end) {
  for (std::size_t i = start; i < end; ++i) {
    results[i] = Logic::SolverBisection::Solve(inputs[i]);
  }
}

} // namespace Core::Strategy
