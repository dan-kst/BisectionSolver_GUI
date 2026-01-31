#include "MainWindow.hpp"

using json = nlohmann::json;

namespace GUI {
MainWindow::MainWindow() {
  set_title("MPI Bisection Solver");
  set_default_size(Constants::window_width, Constants::window_height);

  // --- Configuration Section ---
  config_grid_.set_row_spacing(Constants::config_grid_margin);
  config_grid_.set_column_spacing(Constants::config_grid_margin);

  auto add_entry = [&](const std::string &label, Gtk::Entry &entry, int row,
                       const std::string &def) {
    config_grid_.attach(*Gtk::make_managed<Gtk::Label>(label), 0, row);
    entry.set_text(def);
    config_grid_.attach(entry, 1, row);
  };

  add_entry("Interval A:", entry_a_, 0, "0.0");
  add_entry("Interval B:", entry_b_, 1, "5.0");
  add_entry("Epsilon:", entry_eps_, 2, "0.0000001");
  add_entry("Task Count:", entry_count_, 3, "1000000");

  // Setup Strategy Selector (DropDown)
  auto strategy_model = Gtk::StringList::create({"Sequential", "MPI Parallel"});
  strategy_selector_.set_model(strategy_model);
  strategy_selector_.set_selected(0);

  config_grid_.attach(*Gtk::make_managed<Gtk::Label>("Strategy:"), 0, 4);
  config_grid_.attach(strategy_selector_, 1, 4);

  // --- Controls ---
  buttons_box_.set_halign(Gtk::Align::CENTER);
  buttons_box_.append(run_button_);
  buttons_box_.append(save_button_);
  buttons_box_.append(load_button_);

  controls_box_.set_halign(Gtk::Align::BASELINE_CENTER);
  controls_box_.append(config_grid_);
  controls_box_.append(buttons_box_);

  // Layout Setup
  main_box_.set_margin(Constants::main_box_margin);
  main_box_.append(controls_box_);
  main_box_.append(status_label_);
  main_box_.append(spinner_);
  set_child(main_box_);

  // --- Signals ---
  dispatcher_.connect(sigc::mem_fun(*this, &MainWindow::OnWorkerFinished));
  run_button_.signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::OnRunClicked));
  save_button_.signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::OnSaveClicked));
  load_button_.signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::OnLoadClicked));
}

void MainWindow::OnRunClicked() {
  try {
    Core::Logic::Params entry_params{.a = std::stod(entry_a_.get_text()),
                                     .b = std::stod(entry_b_.get_text()),
                                     .epsilon =
                                         std::stod(entry_eps_.get_text())};
    int count = std::stoi(entry_count_.get_text());
    auto selected_idx = strategy_selector_.get_selected();

    run_button_.set_sensitive(false);
    spinner_.start();
    status_label_.set_text("Computing...");

    worker_thread_ = std::jthread([this, entry_params, count, selected_idx]() {
      std::vector<Core::Logic::Params> tasks(count, entry_params);
      std::unique_ptr<Core::Strategy::ISolverStrategy> solver;
      switch (selected_idx) {
      case 0:
        solver = std::make_unique<Core::Strategy::SolverSequential>();
        break;
      case 1:
        solver = std::make_unique<Core::Strategy::SolverMPI>();
        break;
      default:
        throw std::runtime_error("Select solver type.");
      }
      auto start = std::chrono::high_resolution_clock::now();
      auto results = solver->Solve(tasks);
      auto end = std::chrono::high_resolution_clock::now();

      if (!results.empty()) {
        last_execution_time_ =
            std::chrono::duration<double>(end - start).count();
      } else {
        last_execution_time_ = Constants::execution_time_failed;
      }
      dispatcher_.emit();
    });
  } catch (const std::exception &e) {
    status_label_.set_text("Error: " + std::string(e.what()));
  }
}

void MainWindow::OnSaveClicked() {
  auto dialog = Gtk::FileDialog::create();
  dialog->set_title("Save Equation Parameters");

  dialog->save(*this, [this,
                       dialog](const Glib::RefPtr<Gio::AsyncResult> &result) {
    try {
      auto file = dialog->save_finish(result);
      Core::Logic::Params entry_params{.a = std::stod(entry_a_.get_text()),
                                       .b = std::stod(entry_b_.get_text()),
                                       .epsilon =
                                           std::stod(entry_eps_.get_text())};
      std::ofstream ofs(file->get_path());
      json json_params = entry_params;
      ofs << json_params.dump(4);
      status_label_.set_text("Parameters saved to " + file->get_basename());
    } catch (...) {
      status_label_.set_text("Save cancelled or failed.");
    }
  });
}

void MainWindow::OnLoadClicked() {
  auto dialog = Gtk::FileDialog::create();
  dialog->set_title("Load Equation Parameters");

  dialog->open(*this,
               [this, dialog](const Glib::RefPtr<Gio::AsyncResult> &result) {
                 try {
                   auto file = dialog->open_finish(result);
                   std::ifstream ifs(file->get_path());
                   json json_params;
                   ifs >> json_params;
                   auto entry_params = json_params.get<Core::Logic::Params>();

                   entry_a_.set_text(std::to_string(entry_params.a));
                   entry_b_.set_text(std::to_string(entry_params.b));
                   entry_eps_.set_text(std::to_string(entry_params.epsilon));
                   status_label_.set_text("Loaded: " + file->get_basename());
                 } catch (...) {
                   status_label_.set_text("Load cancelled or failed.");
                 }
               });
}

void MainWindow::OnWorkerFinished() {
  spinner_.stop();
  run_button_.set_sensitive(true);
  if (last_execution_time_ > 0.0) {
    status_label_.set_text("Completed in " +
                           std::to_string(last_execution_time_) + "s");
  } else {
    status_label_.set_text("Equation was not calculated.");
  }
}
} // namespace GUI
