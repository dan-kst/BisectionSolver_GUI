#include "SolverFactory.hpp"

namespace Core::Logic {
[[nodiscard]] auto SolverFactory::create(Core::Strategy::Type strategy_type)
    -> std::unique_ptr<Core::Strategy::ISolverStrategy> {
  using namespace Core::Strategy;
  switch (strategy_type) {
  case Type::MPI:
    return std::make_unique<SolverMPI>();
  case Type::Sequential:
    return std::make_unique<SolverSequential>();
  case Type::Threaded:
    return std::make_unique<SolverThreaded>();
  case Type::None:
    throw std::invalid_argument("Strategy Type was not defined.");
  default:
    throw std::invalid_argument("Unknown Type provided to Factory.");
  }
}

} // namespace Core::Logic
