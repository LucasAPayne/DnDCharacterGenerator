/* NOTE: This is a temporary file used for testing purposes
that will eventually be replaced by a wxWidgets application */

#include "DnDCharacter.h"
#include "FillPDF.h"
#include "Utils/Random.h"

#include <iostream>

int main()
{
	Random::Init();

	while (1)
	{
		dnd::Character character;
		character.DisplayCharacterSheet();

		fillCharacterSheet_1Page(character);

		std::cout << "\n\n";
		system("pause");
		std::cout << "\n";
	}
}
