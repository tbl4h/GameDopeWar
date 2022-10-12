#include "../include/Constants.hpp"
#include "../include/Drug.hpp"
#include "./../GameEngine/include/Locator.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <fstream>
#include <gtest/gtest.h>

class DrugTestFixtureToBeParametrized : public ::testing::Test {
protected:
  Locator l;
  Drug drug;
};

TEST_F(DrugTestFixtureToBeParametrized, DefaultConstructorTests) {
  l.initialize();
  EXPECT_EQ(drug.get_name(), default_drug_name);
  EXPECT_EQ(drug.get_price(), default_drug_price);
}

TEST_F(DrugTestFixtureToBeParametrized, SettersTests) {
  l.initialize();
  std::string name = "New Name";
  const int price = 100;

  drug.set_name(name);
  drug.set_price(price);

  EXPECT_EQ(drug.get_name(), name);
  EXPECT_EQ(drug.get_price(), price);
}

TEST_F(DrugTestFixtureToBeParametrized, PriceOutOfRange) {
  EXPECT_EQ(drug.set_price(minimum_drug_price), true);
  EXPECT_EQ(drug.set_price(maximum_drug_price), true);
  EXPECT_EQ(drug.set_price(minimum_drug_price - 1), false);
  EXPECT_EQ(drug.set_price(maximum_drug_price + 1), false);
}

TEST(DrugTestClass, ParametrizedConstructorTests) {
  __GE_INIT__
  std::string name_param = "Parametrized";
  const int price_param = 100;

  Drug drug(name_param, price_param);

  auto name = drug.get_name();
  auto price = drug.get_price();

  EXPECT_EQ(name_param, name);
  EXPECT_EQ(price, price_param);
}

TEST(DrugTestClass, ComparisionOperators) {
  __GE_INIT__
  std::string no_dafault_name = "No Default";
  const int add_to_default_price = 10;
  const int more_price = 200;
  const int less_price = 1;

  Drug default_drug_1;
  Drug default_drug_2;
  Drug no_default_drug(no_dafault_name,
                       default_drug_price + add_to_default_price);
  Drug more_drug(default_drug_name, more_price);
  Drug less_drug(default_drug_name, less_price);

  EXPECT_EQ(default_drug_1 == default_drug_2, true);
  EXPECT_EQ(default_drug_1 == no_default_drug, false);
  EXPECT_EQ(default_drug_1 != no_default_drug, true);
  EXPECT_EQ(default_drug_1 != default_drug_2, false);
  EXPECT_EQ(more_drug < less_drug, false);
  EXPECT_EQ(less_drug < more_drug, true);
  EXPECT_EQ(more_drug > less_drug, true);
  EXPECT_EQ(less_drug > more_drug, false);
}

TEST(DrugTestClass, SerializationTests) {
  __GE_INIT__
  std::string file_name = "DrugTestFile.txt";
  std::string serialized_name = "Serialized Drug";
  const int serialized_price = 100;

  std::ofstream ofs(file_name);
  Drug t1(serialized_name, serialized_price);
  Drug t2;

  {
    boost::archive::text_oarchive oa(ofs);
    oa << t1;
  }
  {
    std::ifstream ifs(file_name);
    boost::archive::text_iarchive ia(ifs);
    ia >> t2;
  }

  EXPECT_EQ(t2.get_name(), serialized_name);
  EXPECT_EQ(t2.get_price(), serialized_price);
}

TEST(DrugTestClass, PrintClassInfoTest) {
  __GE_INIT__
  Drug default_drug;
  std::string string_default_price = std::to_string(default_drug_price);
  std::string expected_string =
      "Name: " + default_drug_name + ". Price: " + string_default_price + "\n";

  testing::internal::CaptureStdout();
  default_drug.print_class_info();
  std::string std_output = testing::internal::GetCapturedStdout();

  EXPECT_EQ(expected_string, std_output);
}

TEST(Drug, SetPriceEdgeValues) {
  Drug d{};

  EXPECT_EQ(d.set_price(minimum_drug_price), true);
  EXPECT_EQ(d.set_price(maximum_drug_price), true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}