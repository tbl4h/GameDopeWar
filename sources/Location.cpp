#include "Location.hpp"
#include "./../GameEngine/include/Locator.hpp"
#include "Constants.hpp"
#include <iostream>
#include <stdexcept>

Location::Location(const LocationName &Name) {
  switch (Name) {
  case LocationName::Default: {
    name = "Default location";
    break;
  }
  case LocationName::Bronx: {
    name = "Bronx";
    break;
  }
  case LocationName::Brooklyn: {
    name = "Brooklyn";
    break;
  }
  case LocationName::Queens: {
    name = "Queens";
    break;
  }
  case LocationName::Manhatan: {
    name = "Manhatan";
    break;
  }
  case LocationName::StatenIsland: {
    name = "Staten Island";
    break;
  }
  }
  log_properties_values();
}

[[maybe_unused]] auto
Location::set_drugs_list(const DrugsList &DrugListRef) noexcept -> bool {
  for (unsigned int i = 0; i < DrugListRef.size(); i++) {
    drugs_list[i] = std::move(DrugListRef[i]);
  }
  return true;
}

[[maybe_unused]] auto
Location::is_drug_on_list(const std::string &DrugType) const -> bool {
  for (const auto &drug : drugs_list) {
    if (drug.get_name() == DrugType) {
      return true;
    }
    return false;
  }
  /*
  Locator::get_logger().log_err_msg(__METHOD_NAME__, ":There is no ", DrugType,
                                    " on location list.");
                                    */
  return false;
}

auto Location::log_properties_values() const -> void {
  Locator::get_logger().log_msg("Name: ", name);
  Locator::get_logger().log_msg("DrugsList: ");
  for (const auto &drug : drugs_list) {
    drug.log_properties_values();
  }
}