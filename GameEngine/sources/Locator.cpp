#include "Logger.hpp"
#include <Locator.hpp>

// Initialized static services member
Logger *Locator::logger = nullptr;
RandomGeneratorService *Locator::service_random_generator = nullptr;
NullRandomGenerator Locator::nullService_random_generator;

Locator::Locator() {
  logger = Logger::get_logger();
  service_random_generator = &nullService_random_generator;
}

Locator::~Locator() {
  logger->close_logger();
  if (service_random_generator != &nullService_random_generator) {
    delete service_random_generator;
  }
}

void Locator::initialize() { service_random_generator = new RandomGenerator; }

void Locator::provide_random_generator_service(
    RandomGeneratorService *service) {
  if (service_random_generator != service) {
    delete service_random_generator;
  }
  service_random_generator = service;
}