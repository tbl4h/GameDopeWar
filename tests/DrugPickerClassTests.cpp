#include "../include/DrugPicker.hpp"
#include "Constants.hpp"
#include <array>
#include <chrono>
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>

using std::array;
using std::cout;
using std::move;
using std::mt19937;
using std::string;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
/*
TEST(DrugPicker, GetDrugPickerMethodTest) {
  Locator l;
  DrugPicker &drug_picker = DrugPicker::get_drug_picker();
  DrugPicker &drug_picker2 = DrugPicker::get_drug_picker();

  EXPECT_EQ(drug_picker, drug_picker2);
}
*/
TEST(DrugPicker, DrugsOnListMethodTest) {
  unsigned int possible_drugs = 4;
  unsigned int real_possible_drugs = DrugPicker::drugs_on_list();

  EXPECT_EQ(possible_drugs, real_possible_drugs);
}
TEST(DrugPicker, PickDrugMethodTest) {
  __GE_INIT__
  constexpr unsigned int number_of_drugs = DrugPicker::drugs_on_list();
  DrugPicker &drug_picker = DrugPicker::get_drug_picker();
  Drug drug = drug_picker.pick_drug();
  array<string, number_of_drugs> potencial_drug_name = {
      {{"Weed"}, {"MDMA"}, {"Speed"}, {"Cocaine"}}};

  EXPECT_PRED2(
      [](Drug drug, array<string, number_of_drugs> names) {
        for (const auto &name : names)
          if (name == drug.get_name())
            return true;
        return false;
      },
      drug, potencial_drug_name);
}

// Picks a drugs untill in variable all_drugs wont be all possible drugs.
// The test needs to be shortened.
TEST(DrugPicker, PickDrugMethodTestAllPossibilities) {
  __GE_INIT__
  constexpr unsigned int number_of_drugs = DrugPicker::drugs_on_list();
  array<Drug, number_of_drugs> all_drugs;
  array<string, number_of_drugs> potencial_drug_name = {
      {{"Weed"}, {"MDMA"}, {"Speed"}, {"Cocaine"}}};
  DrugPicker &drug_picker = DrugPicker::get_drug_picker();

  cout << "Print values of all_drug for clarity.\n";
  for (const auto &drug : all_drugs) {
    cout << drug.get_name() << "\n";
  }

  for (unsigned int index = 0; index < number_of_drugs; index++) {
    if (all_drugs[index].get_name() == default_drug_name) {
      all_drugs[index] = drug_picker.pick_drug();
      // Remove same drugs
      if (index >= 1) {
        for (unsigned int j = 0; j < index; j++) {
          if (all_drugs[index].get_name() == all_drugs[j].get_name()) {
            all_drugs[index] = Drug{};
            index--;
            break;
          }
        }
      }
    }
  }

  cout << "Print values of all_drug for clarity.\n";
  for (const auto &drug : all_drugs) {
    cout << drug.get_name() << " Price: " << drug.get_price() << "\n";
  }

  for (unsigned int i = 0; i < potencial_drug_name.size(); i++) {
    EXPECT_PRED2(
        [](const array<Drug, number_of_drugs> &drugs, const string &name) {
          for (const auto &drug : drugs) {
            if (drug.get_name() == name) {
              return true;
            }
          }
          return false;
        },
        all_drugs, potencial_drug_name[i]);
  }
}

TEST(DrugPicker, PickDrugListMethodTest) {
  __GE_INIT__
  DrugPicker &drug_picker = DrugPicker::get_drug_picker();
  DrugsList dr = drug_picker.pick_drugs_list();
  for (const auto &d : dr) {
    cout << d.get_name() << "\n";
  }
}

TEST(DrugPicker, CreateDrugTest){
  __GE_INIT__
  array<DrugType,static_cast<unsigned int>(DrugType::DrugTypeSize)> list {
    DrugType::Weed,DrugType::MDMA,DrugType::Speed,DrugType::Cocaine
  };
  DrugsList drugs_list;
  for(unsigned int i =0;i<list.size();i++){
    drugs_list[i] = DrugPicker::create_drug(list[i]);
    
  }
  EXPECT_EQ(drugs_list[0].get_name(),"Weed");
  EXPECT_EQ(drugs_list[1].get_name(),"MDMA");
  EXPECT_EQ(drugs_list[2].get_name(),"Speed");
  EXPECT_EQ(drugs_list[3].get_name(),"Cocaine");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}