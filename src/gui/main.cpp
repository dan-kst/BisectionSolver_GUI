#include "MPIWorker.hpp"
#include "MainWindow.hpp"
#include <gtkmm.h>
#include <mpi.h>

/**
 * @brief Entry point for the MPI application.
 * Splits logic between the Master process (GUI) and Worker processes.
 */
auto main(int argc, char *argv[]) -> int {
  // 1. Initialize MPI immediately
  MPI_Init(&argc, &argv);

  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int result = 0;
  if (rank == 0) {
    // --- MASTER PROCESS (RANK 0) ---
    auto app = Gtk::Application::create("org.lab7.bisection.solver");

    // We run the GUI on Rank 0
    result = app->make_window_and_run<GUI::MainWindow>(argc, argv);

    // After the GUI closes, we must signal workers to terminate
    int world_size = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    for (int i = 1; i < world_size; ++i) {
      int exit_signal = 0;
      // Tag 1 is our custom signal for "Termination"
      MPI_Send(&exit_signal, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
    }
  } else {
    // --- WORKER PROCESSES (RANK > 0) ---
    // Workers run the blocking loop and exit when signaled
    Core::Logic::MPIWorker::Run();
  }

  // 2. Cleanup MPI resources
  MPI_Finalize();
  return result;
}
