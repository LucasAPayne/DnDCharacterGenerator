/* NOTE: This is a temporary file used for testing purposes
that will eventually be replaced by a wxWidgets application */

#include "dndCharacter.h"
#include "dndCharacterGenerator.h"
#include <iostream>
using std::cout;

// Displays all character information
void displayCharacterSheet(const dndCharacter& character);

int main()
{
	while (1)
	{
		dndCharacter character;
		dndCharacterGenerator generator;

		generator.generateCharacter(character);
		displayCharacterSheet(character);

		cout << "\n\n";
		system("pause");
		cout << "\n";
	}
}

void displayCharacterSheet(const dndCharacter& character)
{
	cout << "Gender: " << character.gender << "\n";
	cout << "Race: " << character.race << "\n";
	cout << "Class: " << character.characterClass << "\n";
	cout << "Background: " << character.background << "\n";
	cout << "Alignment: " << character.alignment << "\n\n";
	cout << "Personality Traits: " << character.personalityTraits << "\n\n";
	cout << "Ideals: " << character.ideals << "\n\n";
	cout << "Bonds: " << character.bonds << "\n\n";
	cout << "Flaws: " << character.flaws << "\n";
}