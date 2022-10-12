#include "../include/DrugA.hpp"
#include "../include/Constants.hpp"
#include "./../GameEngine/include//Locator.hpp"
#include <stdexcept>
#include <string>
#include <utility>

using std::exchange;
using std::move;
using std::runtime_error;
using std::string;

constexpr auto DrugA::check_amount_boundry(const unsigned int &Amount) const
    -> bool {
  return (Amount >= minimum_drug_amount && Amount <= maximum_drug_amount);
}

DrugA::DrugA() : amount{default_drug_amount} {
  Locator::get_logger().log_msg(__METHOD_NAME__, ":Default constructor.");
  log_properties_values();
}

DrugA::DrugA(const string &Name, const unsigned int &Price,
             const unsigned int &Amount)
    : Drug{Name, Price} {
  if (check_amount_boundry(Amount)) {
    amount = Amount;
    Locator::get_logger().log_msg(__METHOD_NAME__,
                                  ":Constructor with three parameters.");
    log_properties_values();
  } else {
    Locator::get_logger().log_err_msg(__METHOD_NAME__,
                                      ":Amount of drug is out of scope.");
    throw runtime_error(
        Logger::error_msg(__METHOD_NAME__, ":Amount of drug is out of scope."));
  }
}

auto DrugA::operator=(const DrugA &DrugACopy) -> DrugA & {
  if (*this != DrugACopy) {
    Drug::operator=(DrugACopy);
    amount = DrugACopy.amount;
  }
  Locator::get_logger().log_msg(__METHOD_NAME__, ":Copy operator.");
  log_properties_values();
  return *this;
}

auto DrugA::operator=(DrugA &&DrugAMove) noexcept -> DrugA & {
  if (*this != DrugAMove) {
    amount = std::exchange(DrugAMove.amount, default_drug_amount);
    Drug::operator=(move(DrugAMove));
  }
  Locator::get_logger().log_msg(__METHOD_NAME__, ":Move operator.");
  log_properties_values();
  return *this;
}

auto DrugA::operator==(const DrugA &Rhs) const -> bool {
  return (Drug::operator==(Rhs) && amount == Rhs.amount);
}

auto DrugA::operator!=(const DrugA &Rhs) const -> bool {
  return (Drug::operator!=(Rhs) && amount != Rhs.amount);
}

[[maybe_unused]] auto DrugA::set_amount(const unsigned int &Amount) noexcept
    -> bool {
  if (check_amount_boundry(Amount)) {
    amount = Amount;
    return true;
  }
  Locator::get_logger().log_err_msg(__METHOD_NAME__, ":Amount out of scope.");
  return false;
}

auto DrugA::log_properties_values() const -> void {
  Drug::log_properties_values();
  Locator::get_logger().log_msg("Amount: ", amount);
}