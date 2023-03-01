#include "constants.h"
#include "functions.h"
#include "character.h"
#include "constants.h"
#include "gift.h"

#include <vector>
#include <list>
#include <ctime>
#include <cstdlib>
#include <fstream>

int main() {

	std::cout << "\tTask number 4\n";
	std::cout << "\tRPG turn-based game\n\n";
	std::srand(std::time(NULL));

	std::vector<Character> vCharacters;
	std::list<Gift> lGifts;
	vCharacters.resize(6);
	int64_t step;

	try
	{
		std::ifstream file("game.bin", std::ios::binary);

		if (file.is_open())
		{
			file.close();
			readGame(vCharacters, lGifts, step);
		}
		else
		{
			createNewGame(vCharacters);
			step = 1;
		}


		printGame(vCharacters, lGifts);
		printInfornation(vCharacters);

		Status status = Status::play;

		int64_t solution = 1;

		do
		{
			if (status == Status::play)
			{
				//do
				//{
				//	std::cout << "\nEnter 1 - to continue the game\n";
				//	std::cout << "Enter 2 - to start a new game\n";
				//	std::cout << "Enter 3 - to save and exit\n";
				//	solution = myCin<decltype(solution)>();
				//} while (!(solution == 1 || solution == 2 || solution == 3));

				if (solution == 1)
				{

					std::cout << "Move number " << step << "\n";
					solution = makeMove(vCharacters, lGifts);

					if (solution == 1)
					{
						step++;
						printInfornation(vCharacters);

						status = checkGame(vCharacters);

						if (step % 5 == 0)
						{
							createGift(lGifts, vCharacters);
							printGame(vCharacters, lGifts);
						}
					}
				}
				
				if (solution == 2)
				{
					createNewGame(vCharacters);
					lGifts.clear();
					step = 1;
					printGame(vCharacters, lGifts);
					solution = 1;
				}
				else if (solution == 3)
				{
					saveGame(vCharacters, lGifts, step);
				}
			}
			else
			{
				if (status == Status::vin)
				{
					std::cout << "\nYou won the game in " << step << " moves\n";

					std::map<int64_t, std::string> result = getResults();
					result.emplace(step, getMainCharactersName(vCharacters));
					outputPlayers(result);
					saveResults(result);
				}
				else
				{
					std::cout << "\nYou lost\n";
				}

				do
				{
					std::cout << "\nEnter 2 - to start a new game\n";
					std::cout << "Enter 3 - to exit\n";
					solution = myCin<decltype(solution)>();
				} while (!(solution == 2 || solution == 3));

				if (solution == 2)
				{
					createNewGame(vCharacters);
					lGifts.clear();
					step = 1;
					status = Status::play;
					printGame(vCharacters, lGifts);
				}
			}


		} while (solution != 3);

	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";
	}
	catch (...)
	{
		std::cerr << "Something went wrong\n";
	}



	return 0;
}