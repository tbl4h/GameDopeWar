#include "../include/Constants.hpp"
#include "../include/DrugA.hpp"
#include "./../GameEngine/include/Locator.hpp"
#include <fstream>
#include <gtest/gtest.h>

class DrugTestFixtureToBeParametrized : public ::testing::Test {
protected:
  Locator l;
  DrugA drug_a;
};

TEST_F(DrugTestFixtureToBeParametrized, DefaultConstructorTests) {
  l.initialize();
  EXPECT_EQ(drug_a.get_name(), default_drug_name);
  EXPECT_EQ(drug_a.get_price(), default_drug_price);
  EXPECT_EQ(drug_a.get_amount(), default_drug_amount);
}

TEST_F(DrugTestFixtureToBeParametrized, SettersTests) {
  l.initialize();
  EXPECT_EQ(drug_a.set_amount(minimum_drug_amount), true);
  EXPECT_EQ(drug_a.set_amount(maximum_drug_amount), true);
  EXPECT_EQ(drug_a.set_amount(minimum_drug_amount - 1), false);
  EXPECT_EQ(drug_a.set_amount(maximum_drug_amount + 1), false);
}

TEST(DrugTestClass, ParametrizedConstructorTests) {
  __GE_INIT__
  std::string name_as_parameter = "Parametrized";
  const int price_as_parameter = 100;
  const int amount_as_parameter = 100;
  DrugA parametrizedDrugA(name_as_parameter, price_as_parameter,
                          amount_as_parameter);
  auto name = parametrizedDrugA.get_name();
  auto price = parametrizedDrugA.get_price();
  auto amount = parametrizedDrugA.get_amount();
  EXPECT_EQ(name, name_as_parameter);
  EXPECT_EQ(price, price_as_parameter);
  EXPECT_EQ(amount, amount_as_parameter);
}

TEST(DrugTestClass, SerializationTests) {
  __GE_INIT__
  std::string file_name = "DrugATestDile.txt";
  std::string drug_name = "Serialized Drug";
  const int drug_price = 100;
  const int drug_amount = 1000;
  std::ofstream ofs(file_name);
  DrugA t1(drug_name, drug_price, drug_amount);
  DrugA t2;
  {
    boost::archive::text_oarchive oa(ofs);
    oa << t1;
  }
  {
    std::ifstream ifs(file_name);
    boost::archive::text_iarchive ia(ifs);
    ia >> t2;
  }
  EXPECT_EQ(t2.get_name(), drug_name);
  EXPECT_EQ(t2.get_price(), drug_price);
  EXPECT_EQ(t2.get_amount(), drug_amount);
}

TEST(DrugTestClass, PrintClassInfoTest) {
  __GE_INIT__
  DrugA default_drug_a;
  std::string string_default_price = std::to_string(default_drug_price);
  std::string string_default_amount = std::to_string(default_drug_amount);
  std::string expected_string = "Name: " + default_drug_name +
                                ". Price: " + string_default_price + "\n" +
                                "Amount: " + string_default_amount + "\n";

  testing::internal::CaptureStdout();
  default_drug_a.print_class_info();
  std::string std_output = testing::internal::GetCapturedStdout();

  EXPECT_EQ(expected_string, std_output);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}