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
	dndCharacter character;
	dndCharacterGenerator generator;

	generator.generateCharacter(character);
	displayCharacterSheet(character);
	
	cout << "\n\n";
}

void displayCharacterSheet(const dndCharacter& character)
{
	cout << "Gender: " << character.gender << "\n";
	cout << "Race: " << character.race << "\n";
	cout << "Class: " << character.characterClass << "\n";
	cout << "Background: " << character.background << "\n";
	cout << "Alignment: " << character.alignment << "\n";
}