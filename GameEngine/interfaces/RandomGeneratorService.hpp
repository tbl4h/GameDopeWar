#ifndef RANDOMGENERATORSERVICE_HPP
#define RANDOMGENERATORSERVICE_HPP
#include <random>

class RandomGeneratorService {
public:
  virtual auto pick_int(int lower_bound, int upper_bound) -> int = 0;
  virtual auto set_seed() -> void = 0;
  virtual ~RandomGeneratorService() = default;
};
#endif