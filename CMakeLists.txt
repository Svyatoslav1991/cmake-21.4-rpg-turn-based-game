cmake_minimum_required(VERSION 3.15)
project("4_rpg_turn_based_game" VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

#Добавить game.bin и results.bin
add_custom_command(
	OUTPUT game.bin result.bin
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/game.bin ${CMAKE_CURRENT_BINARY_DIR}/game.bin
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/result.bin ${CMAKE_CURRENT_BINARY_DIR}/result.bin
)

#Создать цели для бинарников
add_custom_target(game_bin_target DEPENDS game.bin)
add_custom_target(results_bin_target DEPENDS results.bin)

add_executable(4_rpg_turn_based_game include/character.h include/constants.h include/functions.h include/gift.h include/point.h src/character.cpp src/functions.cpp src/main.cpp src/point.cpp)
target_include_directories(4_rpg_turn_based_game PUBLIC include)

#установить RUNTIME_OUTPUT_DIRECTORY
set_target_properties(4_rpg_turn_based_game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} OUTPUT_NAME "4_rpg_turn_based_game")

#Связать исполняемый файл с бинарными файлами
add_dependencies(4_rpg_turn_based_game game_bin_target results_bin_target)