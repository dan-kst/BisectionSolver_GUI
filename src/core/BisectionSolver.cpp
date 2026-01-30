#include "core/BisectionSolver.hpp"

namespace Core::Logic {

[[nodiscard]] auto TargetFunction(double arg_x) -> double {
  const double kConstantTerm = 2.0;
  return (arg_x * arg_x * arg_x) - arg_x - kConstantTerm;
}

[[nodiscard]] auto BisectionSolver::Solve(const Logic::Params &task)
    -> Logic::Result {
  double param_a = task.a;
  double param_b = task.b;
  const double middle = 2.0;
  int iterations = 0;

  auto func_linear = [middle](double arg_x) {
    return (arg_x * arg_x * arg_x) - arg_x - middle;
  };

  if (func_linear(param_a) * func_linear(param_b) >= 0) {
    return {.root = 0.0, .iterations = 0, .converged = false};
  }

  double mid = param_a;
  while ((param_b - param_a) >= task.epsilon) {
    mid = (param_a + param_b) / middle;
    if (func_linear(mid) == 0.0) {
      break;
    }

    if (func_linear(mid) * func_linear(param_a) < 0) {
      param_b = mid;
    } else {
      param_a = mid;
    }

    iterations++;
  }
  return {.root = mid, .iterations = iterations, .converged = true};
}

} // namespace Core::Logic
