#include "../include/Constants.hpp"
#include "../include/Location.hpp"
#include "DrugPicker.hpp"
#include <array>
#include <gtest/gtest.h>

TEST(Location, LocationConstructorsTests) {
  __GE_INIT__
  Location location;
  std::string expected_name = "Default location";
  DrugsList expected_list;
  DrugsList location_drugs_list = location.get_drugs_list();
  EXPECT_EQ(location.get_name(), expected_name);
  for (unsigned int i = 0; i < expected_list.size(); i++) {
    EXPECT_EQ(location_drugs_list[i].get_name(), expected_list[i].get_name());
    EXPECT_EQ(location_drugs_list[i].get_price(), expected_list[i].get_price());
  }
}

TEST(Location, TestAllPossibylitiesOfConstructor) {
  __GE_INIT__
  const unsigned int location_size =
      static_cast<unsigned int>(LocationName::StatenIsland);
  std::array<LocationName, location_size> locations;
  for (unsigned int i = static_cast<unsigned int>(LocationName::Default);
       i <= location_size; i++) {
    locations[i] = static_cast<LocationName>(i);
    Location l{locations[i]};
    if (i == 0) {
      EXPECT_EQ(l.get_name(), "Default location");
    } else if (i == 1) {
      EXPECT_EQ(l.get_name(), "Bronx");
    } else if (i == 2) {
      EXPECT_EQ(l.get_name(), "Brooklyn");
    } else if (i == 3) {
      EXPECT_EQ(l.get_name(), "Queens");
    } else if (i == 4) {
      EXPECT_EQ(l.get_name(), "Manhatan");
    } else if (i == 5) {
      EXPECT_EQ(l.get_name(), "Staten Island");
    }
  }
}

TEST(Location, SettersAndGetersTest) {
  __GE_INIT__
  Location l;
  DrugPicker &drug_picker = DrugPicker::get_drug_picker();
  DrugsList dr = drug_picker.pick_drugs_list();
  l.set_drugs_list(dr);
  DrugsList ldr = l.get_drugs_list();
  for (unsigned int i = 0; i < ldr.size(); i++) {
    EXPECT_EQ(dr[i].get_name(), ldr[i].get_name());
    EXPECT_EQ(dr[i].get_price(), ldr[i].get_price());
  }
}

TEST(Location, IsDrugOnTheListTest) {
  __GE_INIT__
  DrugsList dr;
  dr[0] = DrugPicker::create_drug(DrugType::Cocaine);
  Location l;
  l.set_drugs_list(dr);
  EXPECT_EQ(l.is_drug_on_list("Cocaine"), true);
  EXPECT_EQ(l.is_drug_on_list("Speed"),false);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}