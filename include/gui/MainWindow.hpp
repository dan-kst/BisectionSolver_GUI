#include "ISolverStrategy.hpp"
#include "SolverFactory.hpp"
#include <cstddef>
#include <fstream>
#include <gtkmm.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <thread>

namespace GUI {
namespace Constants {
const std::size_t window_width = 500;
const std::size_t window_height = 500;
const std::size_t main_box_margin = 20;
const std::size_t config_grid_margin = 10;

const std::size_t task_workload = 1'000'000;

const double arg_a_test = 0.0;
const double arg_b_test = 10.0;
const double arg_epsilon_test = 1e-7;
const double execution_time_failed = -1.0;
} // namespace Constants
class MainWindow : public Gtk::Window {
public:
  MainWindow();

protected:
  // Layout
  Gtk::Box main_box_{Gtk::Orientation::VERTICAL, 10};
  Gtk::Box buttons_box_{Gtk::Orientation::VERTICAL, 10};
  Gtk::Box controls_box_{Gtk::Orientation::HORIZONTAL, 10};
  Gtk::Grid config_grid_;

  // Configuration UI
  Gtk::Entry entry_a_, entry_b_, entry_eps_, entry_count_;
  Gtk::DropDown strategy_selector_;

  // Controls
  Gtk::Button run_button_{"Start Solver"};
  Gtk::Button save_button_{"Save Config"};
  Gtk::Button load_button_{"Load Config"};
  Gtk::Label status_label_{"Ready"};
  Gtk::Spinner spinner_;

  // Threading logic
  Glib::Dispatcher dispatcher_;
  std::jthread worker_thread_;
  double last_execution_time_ = 0.0;

  void OnRunClicked();
  void OnSaveClicked();
  void OnLoadClicked();
  void OnWorkerFinished();
};
} // namespace GUI
