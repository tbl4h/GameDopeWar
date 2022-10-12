#ifndef LOCATOR_HPP
#define LOCATOR_HPP
#pragma once
#include "./../include/Logger.hpp"
#include "./../include/NullRandomGenerator.hpp"
#include "./../include/RandomGenerator.hpp"
#include "./../interfaces/RandomGeneratorService.hpp"
#include <iterator>

// Data acquisition macro
#define __GE_INIT__                                                            \
  Locator locator;                                                             \
  locator.initialize();

class Locator {
public:
  Locator();
  ~Locator();
  // Initilize all services by default pre build values.
  static void initialize();
  static auto get_random_generator() -> RandomGeneratorService & {
    return *service_random_generator;
  }
  static auto get_logger() -> Logger & { return *logger; }
  static void provide_random_generator_service(RandomGeneratorService *service);

private:
  // Using the logger as a static class object to ensure its destruction.
  static Logger *logger;
  static RandomGeneratorService *service_random_generator;
  static NullRandomGenerator nullService_random_generator;
};

#endif