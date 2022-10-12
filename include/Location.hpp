#ifndef LOCATION_HPP
#define LOCATION_HPP
#pragma once
#include "../GameEngine/include/Logger.hpp"
#include "Constants.hpp"
#include "Drug.hpp"
#include "GameObject.hpp"
#include <array>
#include <string>

class Location : public GameObject {
  // Private member
  std::string name;
  DrugsList drugs_list;

public:
  // Constructors
  explicit Location(const LocationName &Name = LocationName::Default);
  Location(Location &LocationCopy) = delete;
  Location(Location &&LocationMove) noexcept = delete;
  ~Location() = default;

  // Operators
  auto operator=(const Location &LocationCopy) -> Location & = delete;
  auto operator=(Location &&LocationMove) noexcept -> Location & = delete;

  // Public methods
  // Getters and Setters
  /**
   * @brief Get the name object
   *
   * @return std::string
   */
  inline auto get_name() const -> const std::string & { return name; }
  [[maybe_unused]] inline auto set_name(const std::string &NameRef) noexcept
      -> bool {
    name = NameRef;
    return true;
  }
  // Consider to remove that function.
  inline auto get_drugs_list() const -> const DrugsList & { return drugs_list; }
  [[maybe_unused]] auto set_drugs_list(const DrugsList &DrugListRef) noexcept
      -> bool;
  [[maybe_unused]] auto is_drug_on_list(const std::string &DrugType) const
      -> bool;

  auto log_properties_values() const -> void;
};

#endif