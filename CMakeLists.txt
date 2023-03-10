cmake_minimum_required(VERSION 3.15)
project("4_rpg_turn_based_game" VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(4_rpg_turn_based_game include/character.h include/constants.h include/functions.h include/gift.h include/point.h src/character.cpp src/functions.cpp src/main.cpp src/point.cpp)
target_include_directories(4_rpg_turn_based_game PUBLIC ${MY_INCLUDE_DIR})