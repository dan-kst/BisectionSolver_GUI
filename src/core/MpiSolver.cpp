#include "core/MpiSolver.hpp"

namespace Core::Strategy {
[[nodiscard]] auto MpiSolver::Solve(const std::vector<Logic::Params> &inputs)
    -> std::vector<Logic::Result> {

  int world_size = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  const int num_workers = world_size - 1;

  if (num_workers < 1) {
    throw std::runtime_error("MPI was not launched.");
  }

  const std::size_t total_tasks = inputs.size();
  if (total_tasks == 0) {
    return {};
  }

  const std::size_t chunk_size = total_tasks / num_workers;
  std::vector<Logic::Result> all_results(total_tasks);

  // Send data to workers
  for (int i = 1; i <= num_workers; ++i) {
    const std::size_t start_idx = (i - 1) * chunk_size;
    const std::size_t current_chunk =
        (i == num_workers) ? (total_tasks - start_idx) : chunk_size;

    if (current_chunk >
        static_cast<std::size_t>(std::numeric_limits<int>::max())) {
      throw std::runtime_error("Chunk size exceeds MPI integer limit.");
    }

    const int count = static_cast<int>(current_chunk);

    // First, inform the worker how many items are coming
    MPI_Send(&count, 1, MPI_INT, i, 0, MPI_COMM_WORLD);

    // Send the actual data block
    MPI_Send(&inputs[start_idx],
             static_cast<int>(count * sizeof(Logic::Params)), MPI_BYTE, i, 0,
             MPI_COMM_WORLD);
  }

  // Collect results
  for (int i = 1; i <= num_workers; ++i) {
    const std::size_t start_idx = (i - 1) * chunk_size;
    const std::size_t current_chunk =
        (i == num_workers) ? (total_tasks - start_idx) : chunk_size;

    // Use MPI_BYTE with the total size of the result block
    MPI_Recv(&all_results[start_idx],
             static_cast<int>(current_chunk * sizeof(Logic::Result)), MPI_BYTE,
             i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  return all_results;
}

[[nodiscard]] auto MpiSolver::GetType() const -> Type { return Type::MPI; }

} // namespace Core::Strategy
