#include "functions.h"
#include <string>
#include <Windows.h>
#include <fstream>
#include <iostream>

#include "point.h"



//Display game
void printGame(const std::vector<Character>& vCharacters, const std::list<Gift>& lGifts) noexcept
{
	char field[N][N];

	for (int64_t i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			field[i][j] = '.';
		}
	}

	field[vCharacters[0].pos.y][vCharacters[0].pos.x] = 'P';


	for (int64_t i = 1; i < vCharacters.size(); ++i)
	{
		if (vCharacters[i].life)
		{
			int64_t x = vCharacters[i].pos.x;
			int64_t y = vCharacters[i].pos.y;

			field[y][x] = 'E';
		}
	} 

	for (const auto& gift : lGifts)
	{
		int64_t x = gift.pos.x;
		int64_t y = gift.pos.y;

		switch (gift.present)
		{
		case Present::armor:
			field[y][x] = 'a';
			break;
		case Present::damage:
			field[y][x] = 'd';
			break;
		case Present::life:
			field[y][x] = 'l';
			break;
		default:
			break;
		}
	}



	std::cout << "\n";
	for (int64_t i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cout << field[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

//*********************************************************************************

//Create a main character
Character createMainCharacter() noexcept
{
	Character hero;
	hero.typeCharacter = Type::hero;

	std::cout << "\nMain character's name\n";
	hero.name = myCin<decltype(hero.name)>();

	do
	{
		std::cout << "The amount of life of the main character (>0)\n";
		hero.life = myCin<decltype(hero.life)>();
	} while (hero.life <= 0);

	do
	{
		std::cout << "The amount of armor of the main character (>=0)\n";
		hero.armor = myCin<decltype(hero.armor)>();
	} while (hero.armor < 0);

	do
	{
		std::cout << "Main character damage dealt (>0)\n";
		hero.damage = myCin<decltype(hero.damage)>();
	} while (hero.damage < 0);

	do
	{
		std::cout << "Start position x (1-20)\n";
		hero.pos.x = myCin<decltype(hero.pos.x)>();
	} while (hero.pos.x < 1 || hero.pos.x > 20);

	hero.pos.x--;

	do
	{
		std::cout << "Start position y (1-20)\n";
		hero.pos.y = myCin<decltype(hero.pos.y)>();
	} while (hero.pos.y < 1 || hero.pos.y > 20);

	hero.pos.y--;

	return hero;
}

//*********************************************************************************

//create a random enemy
Character createRandomEnemy() noexcept
{
	Character enemy;

	static int64_t i = 1;

	enemy.name = "Enemy#" + std::to_string(i++);

	enemy.life = rand()%101 + 50;
	enemy.armor = rand()%51;
	enemy.damage = rand()%16 + 15;

	return enemy;
}

//*********************************************************************************

//Place enemies on the map
void placeEnemiesOnMap(std::vector<Character>& vCharacters) noexcept
{
	for (int64_t i = 1; i < vCharacters.size();)
	{
		int64_t x = rand() % 20;
		int64_t y = rand() % 20;

		bool isEmptyField = true;
		
		for (int64_t j = i - 1; j >= 0; j--)
		{
			if (x == vCharacters[j].pos.x && y == vCharacters[j].pos.y)
			{
				isEmptyField = false;
				break;
			}
		}

		if (isEmptyField)
		{
			vCharacters[i].pos.x = x;
			vCharacters[i].pos.y = y;
			++i;
		}
	}
}

//*********************************************************************************

//Display information about the game
void printInfornation(const std::vector<Character>& vCharacters) noexcept
{
	std::cout << "\n";
	for (const auto& unit : vCharacters)
	{
		if (unit.life)
		{
			std::cout << unit.name << "\tPos: " << unit.pos.x + 1 << " " << unit.pos.y + 1
				<< "\tLife: " << unit.life << "\tArmor: " << unit.armor << "\tDamage: "
				<< unit.damage << "\n";
		}
		else
		{
			std::cout << unit.name << "\t" << "KILLED\n";
		}
	}
	std::cout << "\n";
}

//*********************************************************************************

//Create a new game
void createNewGame(std::vector<Character>& vCharacters) noexcept
{
	std::vector<Character> v;

	v.reserve(6);

	v.push_back(createMainCharacter());

	for (int i = 0; i < 5; ++i)
	{
		v.push_back(createRandomEnemy());
	}

	vCharacters = v;


	placeEnemiesOnMap(vCharacters);
}

//*********************************************************************************

//Make a move
int64_t makeMove(std::vector<Character>& vCharacters, std::list<Gift>& lGifts) noexcept
{
	Point p = makeMainHeroMove(vCharacters[0]);

	if (p.x == 22)
	{
		return 2;
	}
	else if (p.x == 23)
	{
		return 3;
	}

	checkIsEnemyAttacked(p, vCharacters);
	checkIsTookGift(vCharacters[0], lGifts);

	printGame(vCharacters, lGifts);

	if (isEnemiesAlife)
	{
		makeAnemeiesMoves(vCharacters, lGifts);
	}
	
	return 1;
}

//*********************************************************************************

//Make a move the main character
Point makeMainHeroMove(Character& character) noexcept
{
	int64_t x = character.pos.x;
	int64_t y = character.pos.y;

	char step;
	
	if (x == 0 && y == 0)
	{
		do
		{
			std::cout << "Enter 2 - to start a new game\n";
			std::cout << "Enter 3 - to save and exit\n";
			std::cout << "Enter s - go down\n";
			std::cout << "Enter d - go right\n";
			step = myCin<decltype(step)>();
		} while (step != 's' && step != 'd' && step != '2' && step != '3');
	}
	else if (x == N - 1 && y == N - 1)
	{
		do
		{
			std::cout << "Enter 2 - to start a new game\n";
			std::cout << "Enter 3 - to save and exit\n";
			std::cout << "Enter w - go up\n";
			std::cout << "Enter a - go left\n";
			step = myCin<decltype(step)>();
		} while (step != 'w' && step != 'a' && step != '2' && step != '3');
	}
	else if (x == N - 1 && y == 0)
	{
		do
		{
			std::cout << "Enter 2 - to start a new game\n";
			std::cout << "Enter 3 - to save and exit\n";
			std::cout << "Enter s - go down\n";
			std::cout << "Enter a - go left\n";
			step = myCin<decltype(step)>();
		} while (step != 's' && step != 'a' && step != '2' && step != '3');
	}
	else if (x == 0 && y == N - 1)
	{
		do
		{
			std::cout << "Enter 2 - to start a new game\n";
			std::cout << "Enter 3 - to save and exit\n";
			std::cout << "Enter w - go up\n";
			std::cout << "Enter d - go right\n";
			step = myCin<decltype(step)>();
		} while (step != 'w' && step != 'd' && step != '2' && step != '3');
	}
	else if (x == 0)
	{
		do
		{
			std::cout << "Enter 2 - to start a new game\n";
			std::cout << "Enter 3 - to save and exit\n";
			std::cout << "Enter w - go up\n";
			std::cout << "Enter s - go down\n";
			std::cout << "Enter d - go right\n";
			step = myCin<decltype(step)>();
		} while (step != 'w' && step != 'd' && step != 's' && step != '2' && step != '3');
	}
	else if (x == N-1)
	{
		do
		{
			std::cout << "Enter 2 - to start a new game\n";
			std::cout << "Enter 3 - to save and exit\n";
			std::cout << "Enter w - go up\n";
			std::cout << "Enter s - go down\n";
			std::cout << "Enter a - go left\n";
			step = myCin<decltype(step)>();
		} while (step != 'w' && step != 'a' && step != 's' && step != '2' && step != '3');
	}
	else if (y == 0)
	{
		do
		{
			std::cout << "Enter 2 - to start a new game\n";
			std::cout << "Enter 3 - to save and exit\n";
			std::cout << "Enter a - go left\n";
			std::cout << "Enter s - go down\n";
			std::cout << "Enter d - go right\n";
			step = myCin<decltype(step)>();
		} while (step != 'a' && step != 'd' && step != 's' && step != '2' && step != '3');
	}
	else if (y == N - 1)
	{
		do
		{
			std::cout << "Enter 2 - to start a new game\n";
			std::cout << "Enter 3 - to save and exit\n";
			std::cout << "Enter a - go left\n";
			std::cout << "Enter w - go up\n";
			std::cout << "Enter d - go right\n";
			step = myCin<decltype(step)>();
		} while (step != 'a' && step != 'd' && step != 'w' && step != '2' && step != '3');
	}
	else
	{
		do
		{
			std::cout << "Enter 2 - to start a new game\n";
			std::cout << "Enter 3 - to save and exit\n";
			std::cout << "Enter w - go up\n";
			std::cout << "Enter s - go down\n";
			std::cout << "Enter a - go left\n";
			std::cout << "Enter d - go right\n";
			step = myCin<decltype(step)>();
		} while (step != 'a' && step != 'd' && step != 'w' && step != 's' && step != '2' && step != '3');
	}

	Point p;
	if (step == '2')
	{
		p.x = 22;
		p.y = 22;
	}
	else if (step == '3')
	{
		p.x = 23;
		p.y = 23;
	}
	else if (step == 'w')
	{
		p.y = y - 1;
		p.x = x;
	}
	else if (step == 's')
	{
		p.y = y + 1;
		p.x = x;
	}
	else if (step == 'd')
	{
		p.y = y;
		p.x = x + 1;
	}
	else
	{
		p.y = y;
		p.x = x - 1;
	}

	return p;
}

//*********************************************************************************

//Check if the enemy is attacked
void checkIsEnemyAttacked(Point p, std::vector<Character>& vCharacters) noexcept
{
	for (int64_t i = 1; i < vCharacters.size(); ++i)
	{
		if (vCharacters[i].life)
		{
			if (p == vCharacters[i].pos)
			{
				std::cout << vCharacters[0].name << " attacks " << vCharacters[i].name << "\n";
				if (vCharacters[i].armor)
				{
					vCharacters[i].armor -= vCharacters[0].damage;
					if (vCharacters[i].armor < 0)
					{
						vCharacters[i].life += vCharacters[i].armor;
						vCharacters[i].armor = 0;

						if (vCharacters[i].life <= 0)
						{
							vCharacters[i].life = 0;
							vCharacters[0].pos = vCharacters[i].pos;
						}
					}
				}
				else
				{
					vCharacters[i].life -= vCharacters[0].damage;
					if (vCharacters[i].life <= 0)
					{
						vCharacters[i].life = 0;
						vCharacters[0].pos = vCharacters[i].pos;
					}
				}
				return;
			}
		}
	}

	vCharacters[0].pos = p;
}

//*********************************************************************************

//Enemies make a move
void makeAnemeiesMoves(std::vector<Character>& vCharacters, std::list<Gift>& lGifts) noexcept
{
	int64_t direction;
	Point newPos;
	for (int64_t i = 1; i < vCharacters.size(); ++i)
	{
		if (vCharacters[i].life)
		{
			newPos = vCharacters[i].pos;
			direction = rand() % 4;

			switch (direction)
			{
			case 0://left
				newPos.x--;
				break;
			case 1://right
				newPos.x++;
				break;
			case 2://up
				newPos.y--;
				break;
			case 3://down
				newPos.y++;
				break;
			default:
				break;
			}

			checkNewEnemyPos(i, vCharacters, newPos);

			checkIsTookGift(vCharacters[i], lGifts);

			Sleep(500);

			std::cout << "\nStep player " << vCharacters[i].name;
			printGame(vCharacters, lGifts);

			if (vCharacters[0].life == 0)
			{
				break;
			}
		}
	}
}

//*********************************************************************************

//Check the new position of the enemy
void checkNewEnemyPos(int64_t enemyNumber, std::vector<Character>& vCharacters, Point newPos) noexcept
{
	if (enemyNumber > 0)//Checking that the main character is not selected
	{
		//Out-of-field check
		if (newPos.x < 0 || newPos.x == N || newPos.y < 0 || newPos.y == N)
		{
			return;
		}

		//Checking for a match with the main character field
		if (newPos == vCharacters[0].pos)
		{
			std::cout << vCharacters[enemyNumber].name << " attacs " << vCharacters[0].name << "\n";
			enemyAttacs(vCharacters, enemyNumber);
			return;
		}

		//Checking for a match with another enemy's field
		for (int64_t i = 1; i < vCharacters.size(); ++i)
		{
			if (i != enemyNumber)
			{
				if (newPos == vCharacters[i].pos)
				{
					return;
				}
			}
		}

		vCharacters[enemyNumber].pos = newPos;
	}
}

//*********************************************************************************

//The enemy attacks the main character
void enemyAttacs(std::vector<Character>& vCharacters, int64_t enemyNumber) noexcept
{
	if (enemyNumber > 0 && enemyNumber < vCharacters.size())//Checking if the main character is not selected
	{
		if (vCharacters[enemyNumber].life)//Checking if a unit is alive
		{
			int64_t damage = vCharacters[enemyNumber].damage;
			if (vCharacters[0].armor)
			{
				vCharacters[0].armor -= damage;
				if (vCharacters[0].armor < 0)
				{
					damage = -1 * vCharacters[0].armor;
					vCharacters[0].armor = 0;
				}
				else
				{
					damage = 0;
				}
			}

			if (damage)
			{
				vCharacters[0].life -= damage;
				if (vCharacters[0].life < 0)
				{
					vCharacters[0].life = 0;
				}
			}
		}
	}
}

//*********************************************************************************

//Checking that there is at least one living enemy
bool isEnemiesAlife(const std::vector<Character>& vCharacters) noexcept
{
	for (int64_t i = 1; i < vCharacters.size(); ++i)
	{
		if (vCharacters[i].life)
		{
			return true;
		}
	}

	return false;
}

//*********************************************************************************

//Checking the game for completeness
Status checkGame(const std::vector<Character>& vCharacters) noexcept
{
	if (!vCharacters[0].life)
	{
		return Status::lose;
	}
	else if (isEnemiesAlife(vCharacters))
	{
		return Status::play;
	}
	else
	{
		return Status::vin;
	}
}

//*********************************************************************************

//save the game in a file
void saveGame(const std::vector<Character>& vCharacters, const std::list<Gift>& lGifts, int64_t step)
{
	std::ofstream file("game.bin", std::ios::binary);

	if (file.is_open())
	{
		file.write((char*)&step, sizeof(step));

		for (const auto& character : vCharacters)
		{
			file.write((char*)&character.typeCharacter, sizeof(character.typeCharacter));

			////////////09.03.23///////////////////////////
			int64_t sizeName = character.name.size();
			file.write((char*)&sizeName, sizeof(sizeName));
			file.write(character.name.c_str(), sizeName);
			///////////////////////////////////////////////

			file.write((char*)&character.pos, sizeof(character.pos));
			file.write((char*)&character.life, sizeof(character.life));
			file.write((char*)&character.armor, sizeof(character.armor));
			file.write((char*)&character.damage, sizeof(character.damage));
		}

		int64_t giftSize = lGifts.size();
		file.write((char*)&giftSize, sizeof(giftSize));

		for (const auto& gift : lGifts)
		{
			file.write((char*)&gift.pos, sizeof(gift.pos));
			file.write((char*)&gift.present, sizeof(gift.present));
		}


		file.close();
	}
	else
	{
		throw std::exception("Can't open file game.bin for writing");
	}
}

//*********************************************************************************

//read saved game in file
void readGame(std::vector<Character>& vCharacters, std::list<Gift>& lGifts, int64_t& step)
{
	std::ifstream file("game.bin", std::ios::binary);

	if (file.is_open())
	{
		file.read((char*)&step, sizeof(step));

		for (auto& character : vCharacters)
		{
			file.read((char*)&character.typeCharacter, sizeof(character.typeCharacter));

			////////////09.03.23//////////////////////////////////
			int64_t sizeName;
			file.read((char*)&sizeName, sizeof(sizeName));
			character.name.resize(sizeName);
			file.read((char*)character.name.c_str(), sizeName);
			//////////////////////////////////////////////////////

			file.read((char*)&character.pos, sizeof(character.pos));
			file.read((char*)&character.life, sizeof(character.life));
			file.read((char*)&character.armor, sizeof(character.armor));
			file.read((char*)&character.damage, sizeof(character.damage));
		}
		
		int64_t giftSize;
		file.read((char*)&giftSize, sizeof(giftSize));

		for (int64_t i = 0; i < giftSize; ++i)
		{
			Gift gift;
			file.read((char*)&gift.pos, sizeof(gift.pos));
			file.read((char*)&gift.present, sizeof(gift.present));
			lGifts.push_back(gift);
		}


		file.close();
	}
	else
	{
		throw std::exception("Can't open file game.bin for reading");
	}
}

//*********************************************************************************

//creating a gift every fifth step
void createGift(std::list<Gift>& lGifts, std::vector<Character>& vCharacters) noexcept
{
	bool isPosOccupied;

	Gift gift;
	gift.present = static_cast<Present>(rand() % 3);
	Point newPos; 

	do
	{
		newPos = Point(rand() % N, rand() % N);

		isPosOccupied = false;

		for (auto& g : lGifts)
		{
			if (g.pos == newPos)
			{
				isPosOccupied = true;
				break;
			}
		}

		if (!isPosOccupied)
		{
			for (auto& c : vCharacters)
			{
				if (c.pos == newPos)
				{
					isPosOccupied = true;
					break;
				}
			}
		}

	} while (isPosOccupied);

	gift.pos = newPos;

	lGifts.push_back(gift);
}

//*********************************************************************************

//Checking if a gift has been taken
void checkIsTookGift(Character& character, std::list<Gift>& lGifts) noexcept
{
	for (auto it = lGifts.begin(); it != lGifts.end(); it++)
	{
		if (character.pos == (*it).pos)
		{
			std::cout << "Player " << character.name << " takes a ";
			switch ((*it).present)
			{
			case Present::armor:
				character.armor += 8 + rand() % 8;
				std::cout << " armor points\n";
				break;
			case Present::life:
				character.life += 15 + rand() % 16;
				std::cout << " life points\n";
				break;
			case Present::damage:
				character.damage += 10 + rand() % 10;
				std::cout << " damage points\n";
				break;
			default:
				break;
			}

			lGifts.erase(it);
			break;
		}
	}

}

//*********************************************************************************

//Output players to the screen
void outputPlayers(const std::map<int64_t, std::string>& result) noexcept
{
	std::cout << "\n\tRESULTS\n";
	for (auto it = result.crbegin(); it != result.crend(); it++)
	{
		std::cout << (*it).second << "\t" << (*it).first << "\n";
	}
	std::cout << "\n";
}

//*********************************************************************************

//Get game results from a file
std::map<int64_t, std::string> getResults()
{
	std::map<int64_t, std::string> result;

	std::ifstream file("results.bin", std::ios::binary);

	if (file.is_open())
	{
		int64_t value;
		std::string name;

		while (file.eof())
		{
			file.read((char*)&value, sizeof(value));
			file.read((char*)&name, sizeof(name));

			result.emplace(value, name);
		}

		file.close();
	}
	else
	{
		throw std::exception("Can't open file results.bin for reading");
	}

	return result;
}

//*********************************************************************************

//Get main characters name
std::string getMainCharactersName(const std::vector<Character>& vCharacters) noexcept
{
	return vCharacters[0].name;
}

//*********************************************************************************

void saveResults(const std::map<int64_t, std::string>& result)
{
	std::ofstream file("results.bin", std::ios::binary);

	if (file.is_open())
	{
		for (const auto& p : result)
		{
			file.write((char*)&p.first, sizeof(p.first));
			file.write((char*)&p.second, sizeof(p.second));
		}

		file.close();
	}
	else
	{
		throw std::exception("Can't open file results.bin for writing");
	}
}




