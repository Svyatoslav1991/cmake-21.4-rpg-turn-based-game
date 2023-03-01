#include "character.h"

Character& Character::operator=(const Character& character)
{
	if (this != &character)
	{
		typeCharacter = character.typeCharacter;
		name = character.name;
		pos = character.pos;
		life = character.life;
		armor = character.armor;
		damage = character.damage;
	}
	return *this;
}
