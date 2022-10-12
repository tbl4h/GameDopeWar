#include <RandomGenerator.hpp>
#include <chrono>

using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;

auto RandomGenerator::set_seed() -> void {
  seed = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}

RandomGenerator::RandomGenerator() {
  set_seed();
  random_engine.seed(seed);
}

auto RandomGenerator::pick_int(int lower_bound, int upper_bound) -> int {
  IntRange range{lower_bound, upper_bound};
  return range(random_engine);
}