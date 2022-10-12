#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <array>
#include <string>

// Constant declaration for Drug and DrugA classes
/////////////////////////////////////////////////////
/**
 * @brief Code Generates potencialy problems according to [cert-err58-cpp]
 *        ,[fuchsia-statically-constructed-objects]
 *
 */
const std::string default_drug_name = "Default Drug";
constexpr const int default_drug_price = 10;
constexpr const int minimum_drug_price = 1;
constexpr const int maximum_drug_price = 1000;
constexpr const int default_drug_amount = 0;
constexpr const int minimum_drug_amount = 1;
constexpr const int maximum_drug_amount = 10000;

// Constant declaration for DrugPicker class
/////////////////////////////////////////////////////
class Drug;
enum class DrugType { Weed, MDMA, Speed, Cocaine, DrugTypeSize };
// Ensure that the drugs lists are same size.
typedef std::array<Drug, static_cast<unsigned int>(DrugType::DrugTypeSize)>
    DrugsList;

constexpr const int minimum_Weed_price = minimum_drug_price;
constexpr const int maximum_Weed_price = 40;
constexpr const int minimum_MDMA_price = 30;
constexpr const int maximum_MDMA_price = 150;
constexpr const int minimum_Speed_price = 50;
constexpr const int maximum_Speed_price = 150;
constexpr const int minimum_Cocaine_price = 200;
constexpr const int maximum_Cocaine_price = maximum_drug_price;

struct PriceRange {
  int min_price = 0;
  int max_price = 0;
};

// Constant declaration for Location class
/////////////////////////////////////////////////////
enum class LocationName {
  Default,
  Bronx,
  Brooklyn,
  Queens,
  Manhatan,
  StatenIsland,
};
#endif
