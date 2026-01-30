#ifndef BISECTION_LOGIC_HPP
#define BISECTION_LOGIC_HPP

#include <nlohmann/json.hpp>

namespace Core::Logic {
struct Params {
  double a;
  double b;
  double epsilon;
};

struct Result {
  double root;
  int iterations;
  bool converged;
};

/**
 * @brief Pure mathematical implementation of the Bisection Method.
 */
class BisectionSolver {
private:
  [[nodiscard]] static auto TargetFunction(double arg_x) -> double;

public:
  [[nodiscard]] static auto Solve(const Logic::Params &task) -> Logic::Result;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Params, a, b, epsilon);
} // namespace Core::Logic

#endif
