#ifndef DRUGPICKER_HPP
#define DRUGPICKER_HPP
#pragma once
#include "../GameEngine/include/Locator.hpp"
#include "../GameEngine/include/Logger.hpp"
#include "Constants.hpp"
#include "Drug.hpp"
#include "GameObject.hpp"
#include <array>
#include <chrono>
#include <gtest/gtest.h>
#include <random>
#include <stdexcept>
#include <string>
#include <string_view>

/**
 * @brief
 *
 */

/**
 * @brief Class designed to construct Drugs classes require in DrugList class.
 * Class requre that seed and random_engine be set up before class will
 * be declared. That restriction will be enforced in class construction method.
 *
 */
class DrugPicker : public GameObject {
  // Private members
  FRIEND_TEST(DrugPicker, DrugPickerPrivatePropertiesTest);
  FRIEND_TEST(DrugPicker, GetDrugPickerMethodTest);

  static constexpr unsigned int drugs_type_size =
      static_cast<unsigned int>(DrugType::DrugTypeSize);

  static constexpr std::array<PriceRange, drugs_type_size> drugs_prices = {
      {{minimum_Weed_price, maximum_Weed_price},
       {minimum_MDMA_price, maximum_MDMA_price},
       {minimum_Speed_price, maximum_Speed_price},
       {minimum_Cocaine_price, maximum_Cocaine_price}}};

  static constexpr std::array<std::string_view, drugs_type_size> drugs_names = {
      {{"Weed"}, {"MDMA"}, {"Speed"}, {"Cocaine"}}};

  static auto remove_repeted_drug_up_to_index(DrugsList &CurrentList,
                                              unsigned int &Index) -> void;
  static constexpr auto check_drug_type_boundry(DrugType &DrugTypeRef) -> bool;
  // Protected members
protected:
  DrugPicker(){};

public:
  // Constructors
  DrugPicker(const DrugPicker &DrugPickerCopy) = delete;
  DrugPicker(const DrugPicker &&DrugPickerMove) noexcept = delete;
  ~DrugPicker() = default;

  // Operators
  auto operator=(const DrugPicker &Rhs) -> DrugPicker & = delete;
  auto operator=(DrugPicker &&Rhs) noexcept -> DrugPicker & = delete;

  constexpr auto operator==(const DrugPicker &Rhs) noexcept -> bool {
    return (this == &Rhs);
  };

  // Singleton constructor method
  static auto get_drug_picker() -> DrugPicker &;

  // Public methods
  [[nodiscard]] static auto pick_drug() -> Drug;
  [[nodiscard]] static auto
  pick_drugs_list(const unsigned int Size = drugs_type_size) -> DrugsList;
  /**
   * @brief
   *
   * @return Return number of possible drugs to pick. Unsigned int.
   */
  static constexpr inline auto drugs_on_list() -> unsigned int {
    return drugs_type_size;
  }
  static auto create_drug(DrugType DrugTypeRef) -> Drug;
  auto log_properties_values() const -> void;
};

#endif