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
	cout << "Sex: " << character.sex << "\n";
	cout << "Race: " << character.race << "\n";
	cout << "Class: " << character.characterClass << "\n";
	cout << "Level: " << character.level << "\n";
	cout << "Experience Points: " << character.experience << "\n";
	cout << "Background: " << character.background << "\n";
	cout << "Alignment: " << character.alignment << "\n\n";
	cout << "Personality Traits: " << character.personalityTraits << "\n\n";
	cout << "Ideals: " << character.ideals << "\n\n";
	cout << "Bonds: " << character.bonds << "\n\n";
	cout << "Flaws: " << character.flaws << "\n\n";

	cout << "========\n";
	cout << "Abilites\n";
	cout << "========\n";
	cout << "Strength\n";
	cout << "Score: " << character.strength.score << "\n";
	cout << "Modifier: " << character.strength.modifier << "\n\n";
	cout << "Dexterity\n";
	cout << "Score: " << character.dexterity.score << "\n";
	cout << "Modifier: " << character.dexterity.modifier << "\n\n";
	cout << "Constitution\n";
	cout << "Score: " << character.constitution.score << "\n";
	cout << "Modifier: " << character.constitution.modifier << "\n\n";
	cout << "Intelligence\n";
	cout << "Score: " << character.intelligence.score << "\n";
	cout << "Modifier: " << character.intelligence.modifier << "\n\n";
	cout << "Wisdom\n";
	cout << "Score: " << character.wisdom.score << "\n";
	cout << "Modifier: " << character.wisdom.modifier << "\n\n";
	cout << "Charisma\n";
	cout << "Score: " << character.charisma.score << "\n";
	cout << "Modifier: " << character.charisma.modifier << "\n\n";
}