#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include "constants.h"
#include "point.h"

struct Character
{
	Type typeCharacter;
	std::string name;
	Point pos;
	int64_t life;
	int64_t armor;
	int64_t damage;

	Character& operator=(const Character& character);
};

#endif // !CHARACTER_H
