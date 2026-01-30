#include "core/MpiWorker.hpp"

namespace Core {
void MpiWorker::Run() {
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  while (true) {
    int mpi_task_count = 0;
    MPI_Status status;
    MPI_Recv(&mpi_task_count, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD,
             &status);

    // Check if the Master sent a termination signal
    if (status.MPI_TAG == 1) {
      break;
    }
    if (mpi_task_count >
        static_cast<std::size_t>(std::numeric_limits<int>::max())) {
      throw std::runtime_error("Task count exceeds MPI capacity");
    }
    // Receive the actual data
    const auto task_count = static_cast<std::size_t>(mpi_task_count);
    std::vector<Logic::Params> tasks(task_count);
    MPI_Recv(tasks.data(), static_cast<int>(task_count * sizeof(Logic::Params)),
             MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Process the tasks
    std::vector<Logic::Result> results;
    results.reserve(task_count);
    for (const auto &task : tasks) {
      results.push_back(Logic::BisectionSolver::Solve(task));
    }

    // Send results back to Master
    MPI_Send(results.data(),
             static_cast<int>(task_count * sizeof(Logic::Result)), MPI_BYTE, 0,
             0, MPI_COMM_WORLD);
  }
}

} // namespace Core
