#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <vector>
#include <list>
#include <map>

#include "constants.h"
#include "character.h"
#include "gift.h"

//variable value input function
template <typename T>
T myCin() noexcept
{
    bool good = true;

    T variable;

    do
    {
        std::cout << "Enter the value of the variable: ";
        std::cin >> variable;

        good = std::cin.good();

        if (!good)
        {
            std::cout << "You entered something wrong\n";
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (!good);

    return variable;
}

//Display game
void printGame(const std::vector<Character>& vCharacters, const std::list<Gift>& lGifts) noexcept;

//Create a main character
Character createMainCharacter() noexcept;

//create a random enemy
Character createRandomEnemy() noexcept;

//Place enemies on the map
void placeEnemiesOnMap(std::vector<Character>& vCharacters) noexcept;

//Display information about the game
void printInfornation(const std::vector<Character>& vCharacters) noexcept;

//Create a new game
void createNewGame(std::vector<Character>& vCharacters) noexcept;

//Make a move
int64_t makeMove(std::vector<Character>& vCharacters, std::list<Gift>& lGifts) noexcept;

//Make a move the main character
Point makeMainHeroMove(Character& character) noexcept;

//Check if the enemy is attacked
void checkIsEnemyAttacked(Point p, std::vector<Character>& vCharacters) noexcept;

//Enemies make a move
void makeAnemeiesMoves(std::vector<Character>& vCharacters, std::list<Gift>& lGifts) noexcept;

//Check the new position of the enemy
void checkNewEnemyPos(int64_t enemyNumber, std::vector<Character>& vCharacters, Point newPos) noexcept;

//The enemy attacks the main character
void enemyAttacs(std::vector<Character>& vCharacters, int64_t enemyNumber) noexcept;

//Checking that there is at least one living enemy
bool isEnemiesAlife(const std::vector<Character>& vCharacters) noexcept;

//Checking the game for completeness
Status checkGame(const std::vector<Character>& vCharacters) noexcept;

//save the game in a file
void saveGame(const std::vector<Character>& vCharacters, const std::list<Gift>& lGifts, int64_t step);

//read saved game in file
void readGame(std::vector<Character>& vCharacters, std::list<Gift>& lGifts, int64_t& step);

//creating a gift every fifth step
void createGift(std::list<Gift>& lGifts, std::vector<Character>& vCharacters) noexcept;

//Checking if a gift has been taken
void checkIsTookGift(Character& character, std::list<Gift>& lGifts) noexcept;

//Output players to the screen
void outputPlayers(const std::map<int64_t, std::string>& result) noexcept;

//Get game results from a file
std::map<int64_t, std::string> getResults();

//Get main characters name
std::string getMainCharactersName(const std::vector<Character>& vCharacters) noexcept;

//Save results to file result.bin
void saveResults(const std::map<int64_t, std::string>& result);

#endif // FUNCTION_H
