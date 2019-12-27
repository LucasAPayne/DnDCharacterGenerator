/* NOTE: This is a temporary file used for testing purposes
that will eventually be replaced by a wxWidgets application */

#include "dndCharacter.h"
#include "dndCharacterGenerator.h"
#include <iostream>
#include <ctime>
using dnd::Character;
using std::cout;

// Displays all character information
void displayCharacterSheet(const Character& character);

int main()
{
	srand(time(0));

	while (1)
	{
		Character character;

		generateCharacter(character);
		displayCharacterSheet(character);

		cout << "\n\n";
		system("pause");
		cout << "\n";
	}
}

void displayCharacterSheet(const Character& character)
{
	cout << std::boolalpha;
	
	cout << "Name: "			   << character.firstName << " " << character.surname << "\n";
	cout << "Sex: "				   << character.sex << "\n";
	cout << "Race: "			   << character.race << "\n";
	if (character.race == "Human")
	{
		cout << "Ethnicity: " << character.ethnicity << "\n";
	}
	cout << "Class: "			   << character.characterClass << "\n";
	cout << "Level: "			   << character.level << "\n";
	cout << "Experience Points: "  << character.experience << "\n";
	cout << "Proficiency Bonus: "  << character.proficiencyBonus << "\n";
	cout << "Hit Points: "		   << character.maxHitPoints << "\n";
	cout << "Speed: "			   << character.speed << "\n";
	cout << "Initiative: "		   << character.initiative << "\n";
	cout << "Background: "		   << character.background << "\n";
	cout << "Alignment: "		   << character.alignment << "\n\n";
	cout << "Personality Traits: " << character.personalityTraits << "\n\n";
	cout << "Ideals: "			   << character.ideals << "\n\n";
	cout << "Bonds: "			   << character.bonds << "\n\n";
	cout << "Flaws: "			   << character.flaws << "\n\n";

	cout << "Languages: ";
	for (int i = 0; i < character.languages.size(); ++i)
	{
		cout << character.languages[i];
		if (i != character.languages.size() - 1)
		{
			cout << ", ";
		}
	}
	cout << "\n\n";

	cout << "========\n";
	cout << "Abilites\n";
	cout << "========\n";
	cout << "Strength\n";
	cout << "Score: "	 << character.strength.score << "\n";
	cout << "Modifier: " << character.strength.modifier << "\n\n";
	cout << "Dexterity\n";
	cout << "Score: "	 << character.dexterity.score << "\n";
	cout << "Modifier: " << character.dexterity.modifier << "\n\n";
	cout << "Constitution\n";
	cout << "Score: "	 << character.constitution.score << "\n";
	cout << "Modifier: " << character.constitution.modifier << "\n\n";
	cout << "Intelligence\n";
	cout << "Score: "	 << character.intelligence.score << "\n";
	cout << "Modifier: " << character.intelligence.modifier << "\n\n";
	cout << "Wisdom\n";
	cout << "Score: "	 << character.wisdom.score << "\n";
	cout << "Modifier: " << character.wisdom.modifier << "\n\n";
	cout << "Charisma\n";
	cout << "Score: "	 << character.charisma.score << "\n";
	cout << "Modifier: " << character.charisma.modifier << "\n\n";

	cout << "=============\n";
	cout << "Saving Throws\n";
	cout << "=============\n";
	cout << "Proficiencies\n";
	cout << "Strength: "	 << character.strengthSave.proficient << "\n";
	cout << "Dexterity: "	 << character.dexteritySave.proficient << "\n";
	cout << "Constitution: " << character.constitutionSave.proficient << "\n";
	cout << "Intelligence: " << character.intelligenceSave.proficient << "\n";
	cout << "Wisdom: "		 << character.wisdomSave.proficient << "\n";
	cout << "Charisma: "	 << character.charismaSave.proficient << "\n\n";
	cout << "Modifiers\n";
	cout << "Strength: "	 << character.strengthSave.modifier << "\n";
	cout << "Dexterity: "	 << character.dexteritySave.modifier << "\n";
	cout << "Constitution: " << character.constitutionSave.modifier << "\n";
	cout << "Intelligence: " << character.intelligenceSave.modifier << "\n";
	cout << "Wisdom: "		 << character.wisdomSave.modifier << "\n";
	cout << "Charisma: "	 << character.charismaSave.modifier << "\n\n";

	cout << "======\n";
	cout << "Skills\n";
	cout << "======\n";
	cout << "Proficiencies\n";
	cout << "Acrobatics:      " << character.acrobatics.proficient << "\n";
	cout << "Animal Handling: " << character.animalHandling.proficient << "\n";
	cout << "Arcana:          " << character.arcana.proficient << "\n";
	cout << "Athletics:       " << character.athletics.proficient << "\n";
	cout << "Deception:       " << character.deception.proficient << "\n";
	cout << "History:         " << character.history.proficient << "\n";
	cout << "Insight:         " << character.insight.proficient << "\n";
	cout << "Intimidation:    " << character.intimidation.proficient << "\n";
	cout << "Investigation:   " << character.investigation.proficient << "\n";
	cout << "Medicine:        " << character.medicine.proficient << "\n";
	cout << "Nature:          " << character.nature.proficient << "\n";
	cout << "Perception:      " << character.perception.proficient << "\n";
	cout << "Performance:     " << character.performance.proficient << "\n";
	cout << "Persuasion:      " << character.persuasion.proficient << "\n";
	cout << "Religion:        " << character.religion.proficient << "\n";
	cout << "Sleight of Hand: " << character.sleightOfHand.proficient << "\n";
	cout << "Stealth:         " << character.stealth.proficient << "\n";
	cout << "Survival:        " << character.survival.proficient << "\n\n";
	cout << "Modifiers\n";
	cout << "Acrobatics:      " << character.acrobatics.modifier << "\n";
	cout << "Animal Handling: " << character.animalHandling.modifier << "\n";
	cout << "Arcana:          " << character.arcana.modifier << "\n";
	cout << "Athletics:       " << character.athletics.modifier << "\n";
	cout << "Deception:       " << character.deception.modifier << "\n";
	cout << "History:         " << character.history.modifier << "\n";
	cout << "Insight:         " << character.insight.modifier << "\n";
	cout << "Intimidation:    " << character.intimidation.modifier << "\n";
	cout << "Investigation:   " << character.investigation.modifier << "\n";
	cout << "Medicine:        " << character.medicine.modifier << "\n";
	cout << "Nature:          " << character.nature.modifier << "\n";
	cout << "Perception:      " << character.perception.modifier << "\n";
	cout << "Performance:     " << character.performance.modifier << "\n";
	cout << "Persuasion:      " << character.persuasion.modifier << "\n";
	cout << "Religion:        " << character.religion.modifier << "\n";
	cout << "Sleight of Hand: " << character.sleightOfHand.modifier << "\n";
	cout << "Stealth:         " << character.stealth.modifier << "\n";
	cout << "Survival:        " << character.survival.modifier << "\n\n";

	cout << "Passive Wisdom (Perception): " << character.passiveWisdom << "\n";
}