#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#pragma once
#include "../GameEngine/include/Logger.hpp"
#include "Constants.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

class GameObject {
public:
  // Constructors and destructor
  GameObject() = default;
  ~GameObject() = default;
  virtual void log_properties_values() const = 0;
};
#endif