#ifndef SOLVER_FACTORY_HPP
#define SOLVER_FACTORY_HPP

#include "ISolverStrategy.hpp"
#include "SolverMPI.hpp"
#include "SolverSequential.hpp"
#include <memory>
#include <stdexcept>

namespace Core::Logic {

/// @brief Factory class to handle polymorphic creation of ISolverStrategy-based
/// objects.
class SolverFactory {
public:
  /// @brief Creates a specific object based on the Core::Logic::Type.
  /// @param type The type of object to create.
  /// @param inputs AA range of parameters to calculate.
  /// @return A unique_ptr to the created object.
  [[nodiscard]] static auto create(Core::Strategy::Type strategy_type)
      -> std::unique_ptr<Core::Strategy::ISolverStrategy>;
};

} // namespace Core::Logic

#endif // SOLVER_FACTORY_HPP
