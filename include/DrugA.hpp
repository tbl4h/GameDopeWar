#ifndef DRUGA_HPP
#define DRUGA_HPP
#pragma once
#include "Constants.hpp"
#include "Drug.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>
/**
 * @brief Class represent a Drug with amount property.
 *
 */
class DrugA : public Drug {
  // Private member
private:
  unsigned int amount;
  // Private methods
  constexpr auto check_amount_boundry(const unsigned int &Amount) const -> bool;
  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive &archive, const unsigned int version) {
    {
      archive &boost::serialization::base_object<Drug>(*this);
      archive &amount;
    }
  }

public:
  // Constructors
  explicit DrugA();
  explicit DrugA(const std::string &Name, const unsigned int &Price,
                 const unsigned int &Amount);
  DrugA(const DrugA &DrugACopy);
  DrugA(const DrugA &&DrugAMove) noexcept;
  ~DrugA() = default;
  // Operators
  auto operator=(const DrugA &DrugACopy) -> DrugA &;
  auto operator=(DrugA &&DrugAMove) noexcept -> DrugA &;
  auto operator==(const DrugA &Rhs) const -> bool;
  auto operator!=(const DrugA &Rhs) const -> bool;
  // Rest operators are inherited from base class
  // Geters and Setters
  inline auto get_amount() const -> unsigned int { return this->amount; }
  [[maybe_unused]] auto set_amount(const unsigned int &Amount) noexcept -> bool;
  inline void print_class_info() const {
    this->Drug::print_class_info();
    std::cout << "Amount: " << amount << std::endl;
  }
  auto log_properties_values() const -> void;
};
#endif