/* NOTE: This is a temporary file used for testing purposes
that will eventually be replaced by a wxWidgets application */

#include "dndCharacter.h"
#include "Random.h"

#include <iostream>

int main()
{
	Random::Init();

	while (1)
	{
		dnd::Character character;
		character.DisplayCharacterSheet();

		std::cout << "\n\n";
		system("pause");
		std::cout << "\n";
	}
}