/* NOTE: This is a temporary file used for testing purposes
that will eventually be replaced by a wxWidgets application */

#include "dndCharacter.h"
#include "dndCharacterGenerator.h"
#include "Random.h"

#include <iostream>
#include <ctime>

// Displays all character information
void displayCharacterSheet(const dnd::Character& character);

int main()
{
	Random::init();

	while (1)
	{
		dnd::Character character;

		generateCharacter(character);
		displayCharacterSheet(character);

		std::cout << "\n\n";
		system("pause");
		std::cout << "\n";
	}
}

void displayCharacterSheet(const dnd::Character& character)
{
	std::cout << std::boolalpha;
	
	std::cout << "Name: "			   << character.firstName << " " << character.surname << "\n";
	std::cout << "Sex: "				   << character.sex << "\n";
	std::cout << "Race: "			   << character.race << "\n";
	if (character.race == "Human")
	{
		std::cout << "Ethnicity: " << character.ethnicity << "\n";
	}
	std::cout << "Class: "			   << character.characterClass << "\n";
	std::cout << "Level: "			   << character.level << "\n";
	std::cout << "Experience Points: "  << character.experience << "\n";
	std::cout << "Proficiency Bonus: "  << character.proficiencyBonus << "\n";
	std::cout << "Hit Points: "		   << character.maxHitPoints << "\n";
	std::cout << "Speed: "			   << character.speed << "\n";
	std::cout << "Initiative: "		   << character.initiative << "\n";
	std::cout << "Background: "		   << character.background << "\n";
	std::cout << "Alignment: "		   << character.alignment << "\n\n";
	std::cout << "Personality Traits: " << character.personalityTraits << "\n\n";
	std::cout << "Ideals: "			   << character.ideals << "\n\n";
	std::cout << "Bonds: "			   << character.bonds << "\n\n";
	std::cout << "Flaws: "			   << character.flaws << "\n\n";

	std::cout << "Languages: ";
	for (int i = 0; i < character.languages.size(); ++i)
	{
		std::cout << character.languages[i];
		if (i != character.languages.size() - 1)
		{
			std::cout << ", ";
		}
	}
	std::cout << "\n\n";

	std::cout << "========\n";
	std::cout << "Abilites\n";
	std::cout << "========\n";
	std::cout << "Strength\n";
	std::cout << "Score: "	 << character.strength.score << "\n";
	std::cout << "Modifier: " << character.strength.modifier << "\n\n";
	std::cout << "Dexterity\n";
	std::cout << "Score: "	 << character.dexterity.score << "\n";
	std::cout << "Modifier: " << character.dexterity.modifier << "\n\n";
	std::cout << "Constitution\n";
	std::cout << "Score: "	 << character.constitution.score << "\n";
	std::cout << "Modifier: " << character.constitution.modifier << "\n\n";
	std::cout << "Intelligence\n";
	std::cout << "Score: "	 << character.intelligence.score << "\n";
	std::cout << "Modifier: " << character.intelligence.modifier << "\n\n";
	std::cout << "Wisdom\n";
	std::cout << "Score: "	 << character.wisdom.score << "\n";
	std::cout << "Modifier: " << character.wisdom.modifier << "\n\n";
	std::cout << "Charisma\n";
	std::cout << "Score: "	 << character.charisma.score << "\n";
	std::cout << "Modifier: " << character.charisma.modifier << "\n\n";

	std::cout << "=============\n";
	std::cout << "Saving Throws\n";
	std::cout << "=============\n";
	std::cout << "Proficiencies\n";
	std::cout << "Strength: "	 << character.strengthSave.proficient << "\n";
	std::cout << "Dexterity: "	 << character.dexteritySave.proficient << "\n";
	std::cout << "Constitution: " << character.constitutionSave.proficient << "\n";
	std::cout << "Intelligence: " << character.intelligenceSave.proficient << "\n";
	std::cout << "Wisdom: "		 << character.wisdomSave.proficient << "\n";
	std::cout << "Charisma: "	 << character.charismaSave.proficient << "\n\n";
	std::cout << "Modifiers\n";
	std::cout << "Strength: "	 << character.strengthSave.modifier << "\n";
	std::cout << "Dexterity: "	 << character.dexteritySave.modifier << "\n";
	std::cout << "Constitution: " << character.constitutionSave.modifier << "\n";
	std::cout << "Intelligence: " << character.intelligenceSave.modifier << "\n";
	std::cout << "Wisdom: "		 << character.wisdomSave.modifier << "\n";
	std::cout << "Charisma: "	 << character.charismaSave.modifier << "\n\n";

	std::cout << "======\n";
	std::cout << "Skills\n";
	std::cout << "======\n";
	std::cout << "Proficiencies\n";
	std::cout << "Acrobatics:      " << character.acrobatics.proficient << "\n";
	std::cout << "Animal Handling: " << character.animalHandling.proficient << "\n";
	std::cout << "Arcana:          " << character.arcana.proficient << "\n";
	std::cout << "Athletics:       " << character.athletics.proficient << "\n";
	std::cout << "Deception:       " << character.deception.proficient << "\n";
	std::cout << "History:         " << character.history.proficient << "\n";
	std::cout << "Insight:         " << character.insight.proficient << "\n";
	std::cout << "Intimidation:    " << character.intimidation.proficient << "\n";
	std::cout << "Investigation:   " << character.investigation.proficient << "\n";
	std::cout << "Medicine:        " << character.medicine.proficient << "\n";
	std::cout << "Nature:          " << character.nature.proficient << "\n";
	std::cout << "Perception:      " << character.perception.proficient << "\n";
	std::cout << "Performance:     " << character.performance.proficient << "\n";
	std::cout << "Persuasion:      " << character.persuasion.proficient << "\n";
	std::cout << "Religion:        " << character.religion.proficient << "\n";
	std::cout << "Sleight of Hand: " << character.sleightOfHand.proficient << "\n";
	std::cout << "Stealth:         " << character.stealth.proficient << "\n";
	std::cout << "Survival:        " << character.survival.proficient << "\n\n";
	std::cout << "Modifiers\n";
	std::cout << "Acrobatics:      " << character.acrobatics.modifier << "\n";
	std::cout << "Animal Handling: " << character.animalHandling.modifier << "\n";
	std::cout << "Arcana:          " << character.arcana.modifier << "\n";
	std::cout << "Athletics:       " << character.athletics.modifier << "\n";
	std::cout << "Deception:       " << character.deception.modifier << "\n";
	std::cout << "History:         " << character.history.modifier << "\n";
	std::cout << "Insight:         " << character.insight.modifier << "\n";
	std::cout << "Intimidation:    " << character.intimidation.modifier << "\n";
	std::cout << "Investigation:   " << character.investigation.modifier << "\n";
	std::cout << "Medicine:        " << character.medicine.modifier << "\n";
	std::cout << "Nature:          " << character.nature.modifier << "\n";
	std::cout << "Perception:      " << character.perception.modifier << "\n";
	std::cout << "Performance:     " << character.performance.modifier << "\n";
	std::cout << "Persuasion:      " << character.persuasion.modifier << "\n";
	std::cout << "Religion:        " << character.religion.modifier << "\n";
	std::cout << "Sleight of Hand: " << character.sleightOfHand.modifier << "\n";
	std::cout << "Stealth:         " << character.stealth.modifier << "\n";
	std::cout << "Survival:        " << character.survival.modifier << "\n\n";

	std::cout << "Passive Wisdom (Perception): " << character.passiveWisdom << "\n";
}