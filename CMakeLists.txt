#To specify how to use that cmake file vsit https://github.com/StableCoder/cmake-scripts#c-standards-c-standardscmake
#To make code coverage with make make ccov-DrugGame
#CMake command include all --> cmake -DCODE_COVERAGE=ON -DUSE_SANITIZER=Address,Undefined -DBUILD_DOCUMENTATION=ON ..
#Make command include all --> make clangformat clangtidy ccov-DrugGame doc-DrugGame
cmake_minimum_required(VERSION 3.5)
project(DrugGame)

include(clangformat.cmake)
include(cppcheck.cmake)
include(clangtidy.cmake)
include(cppstandards.cmake)
include(sanitizerbuild.cmake)
include(codecoverage.cmake)
include(doxygen.cmake)

include_directories("./include/")

cxx_20()
add_code_coverage() 
build_docs()
#Setup Google Test

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#Set Warnings flgs
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -std=c++20")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -pedantic -std=c++20")

file(GLOB SOURCES "./sources/*.cpp")
file(GLOB GAME_ENGINE_SOURCES "./GameEngine/sources/*.cpp")

add_library(game_sources SHARED ${SOURCES})
target_include_directories(game_sources PRIVATE "./include/")
target_compile_options(game_sources PRIVATE -Wno-unused-parameter)

add_library(game_engine_sources SHARED ${GAME_ENGINE_SOURCES})
target_include_directories(game_engine_sources PRIVATE "./GameEngine/include" "./GameEngine/interfaces")
target_compile_options(game_engine_sources PRIVATE -Wno-unused-parameter)

#Sanitizers compiled options
add_executable(DrugGame "./main.cpp")
target_link_libraries(DrugGame game_sources game_engine_sources)
target_compile_options(DrugGame PRIVATE -Wno-unused-parameter)
target_compile_features(DrugGame PRIVATE cxx_std_20)
target_code_coverage(DrugGame)

include(boostlibrary.cmake)

enable_testing()


include(GoogleTest)

include(testingcomponents.cmake)
