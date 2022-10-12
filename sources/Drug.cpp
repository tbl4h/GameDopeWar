#include "./../include/Drug.hpp"
#include "../include/Constants.hpp"
#include "./../GameEngine/include/Locator.hpp"
#include "GameObject.hpp"
#include <experimental/string_view>
#include <stdexcept>
#include <utility>

// Potencialy deleted code
/*
#ifndef _DEBUG
#define DEBUG(x) do { std::cerr << x << std::endl; } while (0)
#endif
*/

using std::exchange;
using std::runtime_error;
using std::string;

constexpr auto Drug::check_price_boundry(const int &CurrentPrice) const
    -> bool {
  return (CurrentPrice >= minimum_drug_price &&
          CurrentPrice <= maximum_drug_price);
}

auto Drug::compare_names(const string &Name) const -> bool {
  return (this->name == Name);
}

Drug::Drug() : name{"Default Drug"}, price{default_drug_price} {
  Locator::get_logger().log_msg(__METHOD_NAME__, ":Default constructor.");
  log_properties_values();
};

Drug::Drug(const string &Name, const unsigned int &Price) {
  name = Name;
  if (check_price_boundry(Price)) {
    price = Price;
  } else {
    Logger::error_msg(__METHOD_NAME__, ":Price is out of scope.");
    throw runtime_error(
        Logger::error_msg(__METHOD_NAME__, ":Price is out of scope."));
  }
  Locator::get_logger().log_msg(__METHOD_NAME__,
                                ":Constructor with two parametrized.");
  log_properties_values();
};

Drug::Drug(const Drug &DrugCopy) {
  this->name = DrugCopy.name;
  this->price = DrugCopy.price;
  Locator::get_logger().log_msg(__METHOD_NAME__, ":Copy Constructor.");
  log_properties_values();
}

Drug::Drug(Drug &&DrugMove) noexcept
    : name{std::move(DrugMove.name)}, price{DrugMove.price} {
  Locator::get_logger().log_msg(__METHOD_NAME__, ":Move Constructor.");
  log_properties_values();
}

Drug::~Drug() {
  Locator::get_logger().log_msg(__METHOD_NAME__, ":Destructor.");
}

auto Drug::operator=(const Drug &DrugCopy) -> Drug & {
  if (*this == DrugCopy) {
    Locator::get_logger().log_msg(__METHOD_NAME__, ":Copy Operator.");
    log_properties_values();
    return *this;
  }
  name = DrugCopy.name;
  price = DrugCopy.price;
  Locator::get_logger().log_msg(__METHOD_NAME__, ":Copy Operator.");
  log_properties_values();
  return *this;
};

auto Drug::operator=(Drug &&DrugMove) noexcept -> Drug & {
  if (this == &DrugMove) {
    Locator::get_logger().log_msg(__METHOD_NAME__, ":Move Operator.");
    log_properties_values();
    return *this;
  }
  name = exchange(DrugMove.name, default_drug_name);
  price = exchange(DrugMove.price, default_drug_price);
  Locator::get_logger().log_msg(__METHOD_NAME__, ":Move Operator.");
  log_properties_values();
  return *this;
}

auto Drug::operator==(const Drug &Rhs) const -> bool {
  return (this->name == Rhs.name && this->price == Rhs.price);
}

auto Drug::operator!=(const Drug &Rhs) const -> bool {
  return (this->name != Rhs.name && this->price != Rhs.price);
}
/**
 * @brief Comparision less then operator.
 *
 * @param Rhs
 * @return Return comparison from less than operand beetwen prices values.
 */
auto Drug::operator<(const Drug &Rhs) const -> bool {
  return (price < Rhs.price);
}

/**
 * @brief Comparision greater then operator.
 *
 * @param Rhs
 * @return Return comparison from greater than operand beetwen prices values.
 */
auto Drug::operator>(const Drug &Rhs) const -> bool {
  return (price > Rhs.price);
}

[[maybe_unused]] auto Drug::set_name(const string &Name) noexcept -> bool {
  if (compare_names(Name)) {
    return true;
  }
  name = Name;
  return true;
}

[[maybe_unused]] auto Drug::set_price(const unsigned int &Price) noexcept
    -> bool {
  if (check_price_boundry(Price)) {
    price = Price;
    return true;
  }
  Locator::get_logger().log_err_msg(__METHOD_NAME__, ":Price is out of scope.");
  return false;
}

auto Drug::log_properties_values() const -> void {
  Locator::get_logger().log_msg("Name: ", this->name);
  Locator::get_logger().log_msg("Price: ", this->price);
}