#ifndef NULLRANDOMGENERATOR_HPP
#define NULLRANDOMGENERATOR_HPP
#include "./../interfaces/RandomGeneratorService.hpp"

class NullRandomGenerator : public RandomGeneratorService {

  auto set_seed() -> void{};
  virtual auto pick_int(int lower_bound, int upper_bound) -> int { return 0; };
};
#endif