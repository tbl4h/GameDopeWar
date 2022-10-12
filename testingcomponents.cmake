enable_testing()

include_directories(include)

# Drug class section
###################################################
add_executable(
  drug_class_tests
  ./tests/DrugClassTests.cpp
  )
target_compile_options(drug_class_tests PUBLIC -Wno-unused-parameter )
target_link_libraries(
  drug_class_tests
  game_sources game_engine_sources
  GTest::gtest_main
  ${Boost_LIBRARIES}
)
gtest_discover_tests(drug_class_tests)

# DrugA class section
###################################################

add_executable(
  drug_a_class_tests
  ./tests/DrugAClassTests.cpp
  )
target_compile_options(drug_a_class_tests PUBLIC -Wno-unused-parameter )
target_link_libraries(
  drug_a_class_tests
  game_sources game_engine_sources
  GTest::gtest_main
  ${Boost_LIBRARIES}
)
gtest_discover_tests(drug_a_class_tests)

# DrugPicker class section
###################################################

add_executable(
  drug_picker_class_tests
  ./tests/DrugPickerClassTests.cpp
  )
target_compile_options(drug_picker_class_tests PUBLIC -Wno-unused-parameter -Wno-unused-variable)
target_link_libraries(
  drug_picker_class_tests
  game_sources game_engine_sources
  GTest::gtest_main
  ${Boost_LIBRARIES}
)
gtest_discover_tests(drug_picker_class_tests)

# Location class section
###################################################

add_executable(
  location_class_tests
  ./tests/LocationClassTests.cpp
  )
target_compile_options(location_class_tests PUBLIC -Wno-unused-parameter -Wno-unused-variable)
target_link_libraries(
  location_class_tests
  game_sources game_engine_sources
  GTest::gtest_main
  ${Boost_LIBRARIES}
)
gtest_discover_tests(location_class_tests)


# Map class section
###################################################

add_executable(
  map_class_tests
  ./tests/LocationClassTests.cpp
  )
target_compile_options(map_class_tests PUBLIC -Wno-unused-parameter -Wno-unused-variable)
target_link_libraries(
  map_class_tests
  game_sources game_engine_sources
  GTest::gtest_main
  ${Boost_LIBRARIES}
)
gtest_discover_tests(map_class_tests)