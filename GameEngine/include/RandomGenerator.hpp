#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP
#include "./../interfaces/RandomGeneratorService.hpp"

// Defined types
typedef std::uniform_int_distribution<int> IntRange;
typedef std::mt19937 RandomEngine;

class RandomGenerator : public RandomGeneratorService {
  // Private members
  uint64_t seed;
  RandomEngine random_engine;
  // Private methods
  virtual auto set_seed() -> void;

public:
  // Constructors and destructor
  RandomGenerator();
  ~RandomGenerator() = default;
  // Public methods
  virtual auto pick_int(int lower_bound, int upper_bound) -> int;
};
#endif