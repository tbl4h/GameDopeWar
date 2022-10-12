#include "DrugPicker.hpp"
#include <../GameEngine/interfaces/RandomGeneratorService.hpp>
#include "Constants.hpp"
#include "GameObject.hpp"
#include <chrono>
#include <stdexcept>
#include <string_view>

using std::runtime_error;
using std::string;
using std::string_view;

auto DrugPicker::remove_repeted_drug_up_to_index(DrugsList &CurrentList,
                                                 unsigned int &Index) 
    -> void {
  for (unsigned int j = 0; j < Index; j++) {
    if (CurrentList[Index].get_name() == CurrentList[j].get_name()) {
      CurrentList[Index] = Drug{};
      Index--;
      break;
    }
  }
}

constexpr auto DrugPicker::check_drug_type_boundry(DrugType &DrugTypeRef) -> bool {
    const unsigned int lower_bound = static_cast<int>(DrugType::Weed);
    const unsigned int upper_bound =
        static_cast<int>(DrugType::DrugTypeSize) - 1;
    const unsigned int value = static_cast<int>(DrugTypeRef);
    return (value >= lower_bound && value <= upper_bound);
  }

auto DrugPicker::get_drug_picker() -> DrugPicker & {
  static DrugPicker drug_picker;
  return drug_picker;
}

[[nodiscard]] auto DrugPicker::pick_drug() -> Drug {
  const unsigned int lower_bound = static_cast<int>(DrugType::Weed);
  const unsigned int upper_bound = static_cast<int>(DrugType::DrugTypeSize) - 1;
  RandomGeneratorService& random_generator = Locator::get_random_generator();
  unsigned int drug_index = random_generator.pick_int(lower_bound,upper_bound);
  string_view drug_name = drugs_names[drug_index];
  const unsigned int min_price = drugs_prices[drug_index].min_price;
  const unsigned int max_price = drugs_prices[drug_index].max_price;
  const unsigned int price = random_generator.pick_int(min_price,max_price);
  return Drug{drug_name.data(), price};
}

[[nodiscard]] auto DrugPicker::pick_drugs_list(const unsigned int Size)
    -> DrugsList {
  DrugsList drugs_list;
  if (Size > drugs_type_size) {
    Locator::get_logger().log_err_msg(__METHOD_NAME__, ":Size argument out of range.");
    throw runtime_error(
        Logger::error_msg(__METHOD_NAME__, ":Size argument out of range."));
  }
  for (unsigned int index = 0; index < Size; index++) {
    if (drugs_list[index].get_name() == default_drug_name) {
      drugs_list[index] = pick_drug();
      // Remove same drugs
      if (index >= 1) {
        remove_repeted_drug_up_to_index(drugs_list, index);
      }
    }
  }
  return drugs_list;
}

auto DrugPicker::create_drug(DrugType DrugTypeRef) ->Drug{
  const unsigned int drug_type_index = static_cast<unsigned int>(DrugTypeRef);
  if(check_drug_type_boundry(DrugTypeRef)){
    string_view name = drugs_names[drug_type_index];
    const unsigned int min_price = drugs_prices[drug_type_index].min_price;
    const unsigned int max_price = drugs_prices[drug_type_index].max_price;
    unsigned int price = Locator::get_random_generator().pick_int(min_price,max_price);
    return Drug{name.data(),price};
  }
  Locator::get_logger().log_err_msg(__METHOD_NAME__,":Drug type invalid. Cannot create drug.");
  throw runtime_error(Locator::get_logger().error_msg(__METHOD_NAME__,":Drug type invalid. Cannot create drug."));
}

auto DrugPicker::log_properties_values() const -> void {
  if (drugs_names.size() != drugs_prices.size()) {
    throw runtime_error(Locator::get_logger().error_msg(
        __METHOD_NAME__,
        " :Drugs names size is different than drugs prices size."));
  }
  Locator::get_logger().log_msg("Availabe drugs and its prices: ");
  for (unsigned int i = 0; i < drugs_names.size(); i++) {
    Locator::get_logger().log_msg(drugs_names[i], " min: ", drugs_prices[i].min_price,
                    " max: ", drugs_prices[i].max_price, ".");
  }
};
