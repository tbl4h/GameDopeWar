#ifndef DRUG_HPP
#define DRUG_HPP
#pragma once
#include "../GameEngine/include/Logger.hpp"
#include "Constants.hpp"
#include "GameObject.hpp"
#include "Money.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <experimental/string_view>
#include <iostream>
#include <string>

/**
 * @brief Class representing a basic drug in the game.
 *
 */

class Drug : public GameObject {
private:
  // Private member
  std::string name;
  Money price;
  // Private method
  constexpr auto check_price_boundry(const int &CurrentPrice) const -> bool;
  auto compare_names(const std::string &Name) const -> bool;
  // Method from Boost library using for class serialization
  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive &archive, const unsigned int version) {
    archive &name;
    archive &price;
  }

public:
  // Constructors and destructor
  explicit Drug();
  explicit Drug(const std::string &Name, const unsigned int &Price);
  Drug(const Drug &DrugCopy);
  Drug(Drug &&DrugMove) noexcept;
  ~Drug();
  // Operators
  auto operator=(const Drug &DrugCopy) -> Drug &;
  auto operator=(Drug &&DrugMove) noexcept -> Drug &;
  auto operator==(const Drug &Rhs) const -> bool;
  auto operator!=(const Drug &Rhs) const -> bool;
  auto operator<(const Drug &Rhs) const -> bool;
  auto operator>(const Drug &Rhs) const -> bool;
  // Geters and seters
  inline auto get_name() const -> const std::string & { return this->name; }
  [[maybe_unused]] auto set_name(const std::string &Name) noexcept -> bool;
  constexpr inline auto get_price() const noexcept -> Money {
    return price;
  }
  [[maybe_unused]] auto set_price(const unsigned int &Price) noexcept -> bool;
  // Public methods
  inline void print_class_info() const {
    std::cout << "Name: " << name << ". Price: " << price.get_money() << std::endl;
  }
  auto log_properties_values() const -> void override;
};
#endif