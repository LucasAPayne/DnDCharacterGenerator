#include "dndCharacter.h"
#include "dndCharacterGenerator.h"
#include "Random.h"
#include <algorithm>
#include <fstream>
#include <random>
#include <string>
#include <vector>
using std::getline;
using std::ifstream;
using std::reference_wrapper;
using std::string;
using std::vector;


// ======================================================================================
// Helper Functions
// ======================================================================================

// Choose a number (x) of skill proficiencies randomly from a given list
void chooseXRandomlyFrom(int x, vector<reference_wrapper<dnd::Skill> > list)
{
	// Since this uses std::reference_wrapper, when the values in list change, the values in character change also 

	// Randomize the order of entries and pick the first x of them
	std::shuffle(list.begin(), list.end(), Random::getEngine());

	for (int i = 0; i < x; ++i)
	{
		list[i].get().proficient = true;
	}
}

void getNonhumanNames(ifstream& in, vector<string>& possibleNames)
{
	if (in)
	{
		string line;

		// Nonhuman names are stored as a single list, with one name per line, so read the whole file
		while (getline(in, line))
		{
			possibleNames.push_back(line);
		}
	}
}

void getHumanNames(ifstream& in, vector<string>& possibleNames, dnd::Character character)
{
	if (in)
	{
		string line;

		while (getline(in, line))
		{
			if (line.find(character.ethnicity) != string::npos)
			{
				// line is now the character's ethnicity, so skip a line to find the possible names
				getline(in, line);

				// If the character is a Condathan Human, skip an extra line since they share names with Tethyrian Humans,
				// making two labels to be skipped
				if (character.ethnicity == "Chondathan")
				{
					getline(in, line);
				}

				// Read names until a blank line or the end of file is reached
				// since names are grouped this way by ethnicity
				while (line != "" && !in.eof())
				{
					possibleNames.push_back(line);
					getline(in, line);
				}
			}
		}
	}
}


// ======================================================================================
// Character Generation
// ======================================================================================

namespace dnd 
{
	// ======================================================================================
	// Desriptors
	// ======================================================================================

	void generateClass(Character& character)
	{
		vector<string> classes = { "Barbarian", "Bard", "Cleric", "Druid", "Fighter", "Monk", "Paladin", "Ranger", "Rogue",
								"Sorcerer", "Warlock", "Wizard" };

		character.characterClass = classes[Random::drawNumber(0, classes.size() - 1)];
	}

	void generateRace(Character& character)
	{
		vector<string> races = { "Dwarf", "Hill Dwarf", "Mountain Dwarf", "Elf", "High Elf", "Wood Elf", "Dark Elf (Drow)", "Halfling", "Lightfoot Halfling", "Stout Halfling", "Human" };

		character.race = races[Random::drawNumber(0, races.size() - 1)];

		// Humans also have ethnicity (for name)
		if (character.race == "Human")
		{
			vector<string> ethnicities = { "Calishite", "Chondathan", "Damaran", "Illuskan", "Mulan", "Rashemi", "Shou", "Tethyrian", "Turami" };

			character.ethnicity = ethnicities[Random::drawNumber(0, ethnicities.size() - 1)];
		}
	}

	void generateBackground(Character& character)
	{
		// Variants: Spy (Criminal), Gladiator (Entertainer), Guild Merchant (Guild Artisan), Knight (Noble), Pirate (Sailor)
		vector<string> backgrounds = { "Acolyte", "Charlatan", "Criminal", "Entertainer", "Folk Hero", "Gladiator", "Guild Artisan",
									"Guild Merchant", "Hermit", "Knight", "Noble", "Outlander", "Pirate", "Sage", "Sailor", "Soldier",
									"Spy", "Urchin" };

		character.background = backgrounds[Random::drawNumber(0, backgrounds.size() - 1)];
	}

	void generateAlignment(Character& character)
	{
		vector<string> alignments = { "Lawful Good", "Neutral Good", "Chaotic Good", "Lawful Neutral", "Neutral", "Chaotic Neutral",
									"Lawful Evil", "Neutral Evil", "Chaotic Evil" };

		character.alignment = alignments[Random::drawNumber(0, alignments.size() - 1)];
	}

	void generateSex(Character& character)
	{
		// Sex needed to generate random name
		if (character.sex == "")
		{
			vector<string> sexes = { "Male", "Female" };

			character.sex = sexes[Random::drawNumber(0, sexes.size() - 1)];
		}
	}

	void generateFirstName(Character& character)
	{
		vector<string> possibleNames;
		ifstream in;

		if ((character.race == "Dwarf") || (character.race == "Hill Dwarf") || (character.race == "Mountain Dwarf"))
		{
			if (character.sex == "Male")
			{
				in.open("Lists/Names/Dwarf Names/Dwarf Male Names.txt");
				getNonhumanNames(in, possibleNames);
			}
			else if (character.sex == "Female")
			{
				in.open("Lists/Names/Dwarf Names/Dwarf Female Names.txt");
				getNonhumanNames(in, possibleNames);
			}
		}
		else if (character.race == "Elf" || character.race == "High Elf" || character.race == "Wood Elf" || character.race == "Dark Elf (Drow)")
		{
			if (character.sex == "Male")
			{
				in.open("Lists/Names/Elf Names/Elf Male Names.txt");
				getNonhumanNames(in, possibleNames);
			}
			else if (character.sex == "Female")
			{
				in.open("Lists/Names/Elf Names/Elf Female Names.txt");
				getNonhumanNames(in, possibleNames);
			}
		}
		else if (character.race == "Halfling" || character.race == "Lightfoot Halfling" || character.race == "Stout Halfling")
		{
			if (character.sex == "Male")
			{
				in.open("Lists/Names/Halfling Names/Halfling Male Names.txt");
				getNonhumanNames(in, possibleNames);
			}
			else if (character.sex == "Female")
			{
				in.open("Lists/Names/Halfling Names/Halfling Female Names.txt");
				getNonhumanNames(in, possibleNames);
			}
		}
		else if (character.race == "Human")
		{
			if (character.sex == "Male")
			{
				in.open("Lists/Names/Human Names/Human Male Names.txt");
				getHumanNames(in, possibleNames, character);
			}
			else if (character.sex == "Female")
			{
				in.open("Lists/Names/Human Names/Human Female Names.txt");
				getHumanNames(in, possibleNames, character);
			}
		}

		// Shuffle the list of possible names and pick the first one
		// Note: Done this way because choosing a random element as in the other functions
		// threw a "vector subscript out of range" exception
		std::shuffle(possibleNames.begin(), possibleNames.end(), Random::getEngine());
		character.firstName = possibleNames[0];
	}

	void generateSurname(Character& character)
	{
		vector<string> possibleNames;
		ifstream in;

		if (character.race == "Dwarf" || character.race == "Hill Dwarf" || character.race == "Mountain Dwarf")
		{
			in.open("Lists/Names/Dwarf Names/Dwarf Clan Names.txt");
			getNonhumanNames(in, possibleNames);
		}
		else if (character.race == "Elf" || character.race == "High Elf" || character.race == "Wood Elf" || character.race == "Dark Elf (Drow)")
		{
			in.open("Lists/Names/Elf Names/Elf Family Names.txt");
			getNonhumanNames(in, possibleNames);
		}
		else if (character.race == "Halfling" || character.race == "Lightfoot Halfling" || character.race == "Stout Halfling")
		{
			in.open("Lists/Names/Halfling Names/Halfling Family Names.txt");
			getNonhumanNames(in, possibleNames);
		}
		else if (character.race == "Human")
		{
			in.open("Lists/Names/Human Names/Human Surnames.txt");
			getHumanNames(in, possibleNames, character);
		}

		std::shuffle(possibleNames.begin(), possibleNames.end(), Random::getEngine());
		character.surname = possibleNames[0];
	}

	void generatePersonalityTraits(Character& character)
	{
		vector<string> possibleTraits;
		ifstream in("Lists/Personality Traits.txt");

		if (in)
		{
			string line;
			while (getline(in, line))
			{
				// If the current line in the file is the character's background
				if (line.find(character.background) != string::npos)
				{
					getline(in, line);

					// If a character has a background that has a variant, skip an extra line due to the format of the file
					// Variants have the same traits as their base backgrounds
					if (character.background == "Criminal" || character.background == "Entertainer" || character.background == "Guild Artisan"
						|| character.background == "Noble" || character.background == "Sailor")
					{
						getline(in, line);
					}

					while (line != "" && !in.eof())
					{
						possibleTraits.push_back(line);
						getline(in, line);
					}
					
					// Each character gets two personality traits, so shuffle the list and pick the first two
					std::shuffle(possibleTraits.begin(), possibleTraits.end(), Random::getEngine());
					character.personalityTraits += possibleTraits[0] + " " + possibleTraits[1];
				}
			}
		}
	}

	void generateIdeals(Character& character)
	{
		ifstream in("Lists/Ideals.txt");

		if (in)
		{
			string line;
			string axis1 = character.alignment.substr(0, character.alignment.find(' ')); // Lawful, Neutral, or Chaotic
			string axis2 = character.alignment.substr(character.alignment.find(' ') + 1); // Good, Neutral, or Evil;
			bool flag = false;

			while (getline(in, line))
			{
				if (line.find(character.background, 0) != string::npos)
				{
					// Roll a d6 to choose an ideal, as there are 6 pre-made choices for each background in the Player's Handbook
					int target = Random::drawNumber(0, 5);

					if (character.background == "Criminal" || character.background == "Entertainer" || character.background == "Guild Artisan"
						|| character.background == "Noble" || character.background == "Sailor")
					{
						++target;
					}

					for (int skip = 0; skip < target; ++skip) // Skip the number of lines that was rolled
					{
						getline(in, line);
					}

					getline(in, line, '|'); // Now line is the axis of alignment associated with an ideal

					// If the ideal matches alignment
					if (line == axis1 || line == axis2 || line == "Any")
					{
						getline(in, line); // Read the rest of the line
						character.ideals += line += " "; // The last line read is the trait
						break;
					}
					else
					{
						in.seekg(0, in.beg); // Go back to the beginning of the file and pick a different ideal
					}
				}
			}
		}
	}

	void generateBonds(Character& character)
	{
		ifstream in("Lists/Bonds.txt");
		if (in)
		{
			string line;
			while (getline(in, line))
			{
				// If the current line in the file is the character's background
				if (line.find(character.background, 0) != string::npos)
				{
					// Roll a d6 to choose a bond, as there are 6 pre-made choices for each background in the Player's Handbook
					int target = Random::drawNumber(0, 5);

					// If a character has a background that has a variant, skip an extra line due to the format of the file
					// Variants have the same traits as their base backgrounds
					if (character.background == "Criminal" || character.background == "Entertainer" || character.background == "Guild Artisan"
						|| character.background == "Noble" || character.background == "Sailor")
					{
						++target;
					}

					for (int skip = 0; skip <= target; ++skip) // Skip the number of lines that was rolled
					{
						getline(in, line);
					}
					character.bonds += line += " "; // The last line read is the trait
				}
			}
		}
	}

	void generateFlaws(Character& character)
	{
		ifstream in("Lists/Flaws.txt");
		if (in)
		{
			string line;
			while (getline(in, line))
			{
				// If the current line in the file is the character's background
				if (line.find(character.background, 0) != string::npos)
				{
					// Roll a d6 to choose a flaw, as there are 6 pre-made choices for each background in the Player's Handbook
					int target = Random::drawNumber(0, 5);

					// If a character has a background that has a variant, skip an extra line due to the format of the file
					// Variants have the same traits as their base backgrounds
					if (character.background == "Criminal" || character.background == "Entertainer" || character.background == "Guild Artisan"
						|| character.background == "Noble" || character.background == "Sailor")
					{
						++target;
					}

					for (int skip = 0; skip <= target; ++skip) // Skip the number of lines that was rolled
					{
						getline(in, line);
					}
					character.flaws += line += " "; // The last line read is the trait
				}
			}
		}
	}

	// ======================================================================================
	// Skills, Abilities, and Level
	// ======================================================================================

	void generateLevel(Character& character)
	{
		// First entry null so that expForLevel[1] is how much exp is required for level one, etc.
		vector<int> expForLevel = { NULL, 0, 300, 900, 2700, 6500, 14000, 23000, 34000, 48000, 64000, 85000, 100000, 120000, 140000, 165000, 195000, 225000, 265000, 305000, 355000 };

		character.level = Random::drawNumber(1, 20);
		character.experience = expForLevel[character.level]; // Character starts with 0 progress toward next level
	}

	void generateProficiencyBonus(Character& character)
	{
		if (character.level >= 1 && character.level <= 4)
		{
			character.proficiencyBonus = 2;
		}
		else if (character.level >= 5 && character.level <= 8)
		{
			character.proficiencyBonus = 3;
		}
		else if (character.level >= 9 && character.level <= 12)
		{
			character.proficiencyBonus = 4;
		}
		else if (character.level >= 13 && character.level <= 16)
		{
			character.proficiencyBonus = 5;
		}
		else if (character.level >= 17 && character.level <= 20)
		{
			character.proficiencyBonus = 6;
		}
	}

	void generateAbilityScores(Character& character)
	{
		// Roll four d6 and record the sum of the highest three results
		// Do this for each of the six abilities
		vector<int> results;
		vector<int> totals;

		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				results.push_back(Random::drawNumber(1, 6));
			}

			std::sort(results.begin(), results.end(), std::greater<int>()); // Put the results in order of greatest to least
			totals.push_back(results[0] + results[1] + results[2]); // Add the greatest three results of this run and put the sum in totals
		}

		// Assign ability scores to the values in totals
		character.strength.score = totals[0];
		character.dexterity.score = totals[1];
		character.constitution.score = totals[2];
		character.intelligence.score = totals[3];
		character.wisdom.score = totals[4];
		character.charisma.score = totals[5];
	}

	void generateRacialAbilityBonuses(Character& character)
	{
		// Subraces also get parent race benefits
		if (character.race == "Dwarf" || character.race == "Hill Dwarf" || character.race == "Mountain Dwarf")
		{
			character.constitution.score += 2;
		}
		if (character.race == "Hill Dwarf")
		{
			character.wisdom.score++;
		}
		if (character.race == "Mountain Dwarf")
		{
			character.strength.score += 2;
		}

		if (character.race == "Elf" || character.race == "High Elf" || character.race == "Wood Elf" || character.race == "Dark Elf (Drow)")
		{
			character.dexterity.score += 2;
		}
		if (character.race == "High Elf")
		{
			character.intelligence.score++;
		}
		if (character.race == "Wood Elf")
		{
			character.wisdom.score++;
		}
		if (character.race == "Dark Elf (Drow)")
		{
			character.charisma.score++;
		}

		if (character.race == "Halfling" || character.race == "Lightfoot Halfling" || character.race == "Stout Halfling")
		{
			character.dexterity.score += 2;
		}
		if (character.race == "Lightfoot Halfling")
		{
			character.charisma.score++;
		}
		if (character.race == "Stout Halfling")
		{
			character.constitution.score++;
		}

		if (character.race == "Human")
		{
			character.strength.score++;
			character.dexterity.score++;
			character.constitution.score++;
			character.intelligence.score++;
			character.wisdom.score++;
			character.charisma.score++;
		}
	}

	void generateAbilityModifiers(Character& character)
	{
		vector<Ability> abilities = { character.strength, character.dexterity, character.constitution, character.intelligence, character.wisdom, character.charisma };

		for (int i = 0; i < abilities.size(); ++i)
		{
			abilities[i].modifier = floor((float)(abilities[i].score - 10) / 2);
		}

		character.strength.modifier = abilities[0].modifier;
		character.dexterity.modifier = abilities[1].modifier;
		character.constitution.modifier = abilities[2].modifier;
		character.intelligence.modifier = abilities[3].modifier;
		character.wisdom.modifier = abilities[4].modifier;
		character.charisma.modifier = abilities[5].modifier;
	}

	void generateSkillProficiencies(Character& character)
	{
		if (character.characterClass == "Barbarian")
		{
			chooseXRandomlyFrom(2, { character.animalHandling, character.athletics, character.intimidation, character.nature, character.perception, character.survival });
		}
		if (character.characterClass == "Bard")
		{
			// Pick any three skills
			chooseXRandomlyFrom(3, { character.acrobatics, character.animalHandling, character.arcana, character.athletics, character.deception, character.history, character.insight,
				character.intimidation, character.investigation, character.medicine, character.nature, character.perception, character.performance, character.persuasion, character.religion,
				character.sleightOfHand, character.stealth, character.survival });
		}
		if (character.characterClass == "Cleric")
		{
			chooseXRandomlyFrom(2, { character.history, character.insight, character.medicine, character.persuasion, character.religion });
		}
		if (character.characterClass == "Druid")
		{
			chooseXRandomlyFrom(2, { character.arcana, character.animalHandling, character.insight, character.medicine, character.nature, character.perception, character.religion, character.survival });
		}
		if (character.characterClass == "Fighter")
		{
			chooseXRandomlyFrom(2, { character.acrobatics, character.animalHandling, character.athletics, character.history, character.insight, character.intimidation, character.perception,
				character.survival });
		}
		if (character.characterClass == "Monk")
		{
			chooseXRandomlyFrom(2, { character.acrobatics, character.athletics, character.history, character.insight, character.religion, character.stealth });
		}
		if (character.characterClass == "Paladin")
		{
			chooseXRandomlyFrom(2, { character.athletics, character.insight, character.intimidation, character.medicine, character.persuasion, character.religion });
		}
		if (character.characterClass == "Ranger")
		{
			chooseXRandomlyFrom(3, { character.animalHandling, character.athletics, character.insight, character.investigation, character.nature, character.perception,
				character.stealth, character.survival });
		}
		if (character.characterClass == "Rogue")
		{
			chooseXRandomlyFrom(4, { character.acrobatics, character.athletics, character.deception, character.insight, character.intimidation,
				character.investigation, character.perception, character.performance, character.persuasion, character.sleightOfHand, character.stealth });
		}
		if (character.characterClass == "Sorceror")
		{
			chooseXRandomlyFrom(2, { character.arcana, character.deception, character.insight, character.intimidation, character.persuasion, character.religion });
		}
		if (character.characterClass == "Warlock")
		{
			chooseXRandomlyFrom(2, { character.arcana, character.deception, character.history, character.intimidation, character.investigation, character.nature, character.religion });
		}
		if (character.characterClass == "Wizard")
		{
			chooseXRandomlyFrom(2, { character.arcana, character.history, character.insight, character.investigation, character.medicine, character.religion });
		}
	}

	void generateSkillModifiers(Character& character)
	{
		// Skill modifiers are based on the abilities that govern them
		character.athletics.parent = character.strength;
		character.acrobatics.parent = character.sleightOfHand.parent = character.stealth.parent = character.dexterity;
		character.arcana.parent = character.history.parent = character.investigation.parent = character.nature.parent = character.religion.parent = character.intelligence;
		character.animalHandling.parent = character.insight.parent = character.medicine.parent = character.perception.parent = character.survival.parent = character.wisdom;
		character.deception.parent = character.intimidation.parent = character.performance.parent = character.persuasion.parent = character.charisma;

		vector<reference_wrapper<Skill> > skills = { character.acrobatics, character.animalHandling, character.arcana, character.athletics, character.deception, character.history, character.insight,
			character.intimidation,character.investigation, character.medicine, character.nature, character.perception, character.performance, character.persuasion, character.religion,
			character.sleightOfHand, character.stealth, character.survival };

		for (int i = 0; i < skills.size(); ++i)
		{
			// Start at parent ability's modifier
			skills[i].get().modifier = skills[i].get().parent.modifier;

			// If the character is proficient in a skill, add proficiency bonus to the modifier
			if (skills[i].get().proficient)
			{
				skills[i].get().modifier += character.proficiencyBonus;
			}

			// Add other proficiencies
		}
	}

	void generateSavingThrowProficiencies(Character& character)
	{
		if (character.characterClass == "Barbarian")
		{
			character.strengthSave.proficient = true;
			character.constitutionSave.proficient = true;
		}
		if (character.characterClass == "Bard")
		{
			character.dexteritySave.proficient = true;
			character.charismaSave.proficient = true;
		}
		if (character.characterClass == "Cleric")
		{
			character.wisdomSave.proficient = true;
			character.charismaSave.proficient = true;
		}
		if (character.characterClass == "Druid")
		{
			character.intelligenceSave.proficient = true;
			character.wisdomSave.proficient = true;
		}
		if (character.characterClass == "Fighter")
		{
			character.strengthSave.proficient = true;
			character.constitutionSave.proficient = true;
		}
		if (character.characterClass == "Monk")
		{
			character.strengthSave.proficient = true;
			character.dexteritySave.proficient = true;
		}
		if (character.characterClass == "Paladin")
		{
			character.wisdomSave.proficient = true;
			character.charismaSave.proficient = true;
		}
		if (character.characterClass == "Ranger")
		{
			character.strengthSave.proficient = true;
			character.dexteritySave.proficient = true;
		}
		if (character.characterClass == "Rogue")
		{
			character.dexteritySave.proficient = true;
			character.intelligenceSave.proficient = true;
		}
		if (character.characterClass == "Sorceror")
		{
			character.constitutionSave.proficient = true;
			character.charismaSave.proficient = true;
		}
		if (character.characterClass == "Warlock")
		{
			character.wisdomSave.proficient = true;
			character.charismaSave.proficient = true;
		}
		if (character.characterClass == "Wizard")
		{
			character.intelligenceSave.proficient = true;
			character.wisdomSave.proficient = true;
		}
	}

	void generateSavingThrowModifiers(Character& character)
	{
		character.strengthSave.parent = character.strength;
		character.dexteritySave.parent = character.dexterity;
		character.constitutionSave.parent = character.constitution;
		character.intelligenceSave.parent = character.intelligence;
		character.wisdomSave.parent = character.wisdom;
		character.charismaSave.parent = character.charisma;

		vector<reference_wrapper<Skill> > saves = { character.strengthSave, character.dexteritySave, character.constitutionSave, character.intelligenceSave,
			character.wisdomSave, character.charismaSave };

		// Start at parent ability's modifier
		for (int i = 0; i < saves.size(); ++i)
		{
			saves[i].get().modifier = saves[i].get().parent.modifier;
		}

		// Add profiency bonus if proficient in saving throw
		for (int i = 0; i < saves.size(); ++i)
		{
			if (saves[i].get().proficient)
			{
				saves[i].get().modifier += character.proficiencyBonus;
			}
		}
	}

	void generatePassiveWisdom(Character& character)
	{
		// Passive wisdom is wisdom modifier + 10 + proficiency bonus (if proficient in perception)
		character.passiveWisdom = character.wisdom.modifier + 10;

		if (character.perception.proficient)
		{
			character.passiveWisdom += character.proficiencyBonus;
		}
	}


	// ======================================================================================
	// Feats, Traits, Proficiencies, Languages
	// ======================================================================================


	void generateRacialTraits(Character & character)
	{
	}

	void generateFeatsAndTraits(Character& character)
	{

	}

	void generateProficiencies(Character & character)
	{
	}

	void generateLanguages(Character & character)
	{
		character.languages.push_back("Common"); // All characters can speak, read, and write in the Common tongue

		// Common is not a possible language because every character already knows it
		vector<string> possibleLanguages = { "Elvish", "Dwarvish", "Giant", "Gnomish", "Goblin", "Halfling", "Orc", // Common Languages
			"Abyssal", "Celestial", "Draconic", "Deep Speech", "Infernal", "Primordial", "Sylvan", "Undercommon" };	// Exotic Languages

		if (character.race == "Dwarf" || character.race == "Hill Dwarf" || character.race == "Mountain Dwarf")
		{
			character.languages.push_back("Dwarvish");
		}
		else if (character.race == "Elf" || character.race == "High Elf" || character.race == "Wood Elf" || character.race == "Dark Elf (Drow)")
		{
			character.languages.push_back("Elvish");

			// High Elves have the Extra Language Trait
			if (character.race == "High Elf")
			{
				// 1 is the minimum number to avoid picking Elvish twice
				character.languages.push_back(possibleLanguages[Random::drawNumber(1, possibleLanguages.size() - 1)]);
			}
		}
		else if (character.race == "Halfling" || character.race == "Lightfoot Halfling" || character.race == "Stout Halfling")
		{
			character.languages.push_back("Halfling");
		}
		else if (character.race == "Human")
		{
			// Humans can pick any language
			character.languages.push_back(possibleLanguages[Random::drawNumber(0, possibleLanguages.size() - 1)]);
		}
	}


	// ======================================================================================
	// Equipment and Combat
	// ======================================================================================

	void generateHitDice(Character & character)
	{
		if (character.characterClass == "Barbarian")
		{
			character.hitDice.type = "d12";
		}
		else if (character.characterClass == "Fighter" || character.characterClass == "Paladin" || character.characterClass == "Ranger")
		{
			character.hitDice.type = "d10";
		}
		else if (character.characterClass == "Bard" || character.characterClass == "Cleric" || character.characterClass == "Druid" || character.characterClass == "Monk"
			|| character.characterClass == "Rogue" || character.characterClass == "Warlock")
		{
			character.hitDice.type = "d8";
		}
		else if (character.characterClass == "Sorceror" || character.characterClass == "Wizard")
		{
			character.hitDice.type = "d6";
		}

		character.hitDice.number = character.level;
	}

	void generateHitPoints(Character & character)
	{
		// At level 1, characters start with the max roll of their hit die plus their constitution modifier
		if (character.characterClass == "Barbarian")
		{
			character.maxHitPoints = 12 + character.constitution.modifier;
		}
		else if (character.characterClass == "Fighter" || character.characterClass == "Paladin" || character.characterClass == "Ranger")
		{
			character.maxHitPoints = 10 + character.constitution.modifier;
		}
		else if (character.characterClass == "Bard" || character.characterClass == "Cleric" || character.characterClass == "Druid" || character.characterClass == "Monk"
			|| character.characterClass == "Rogue" || character.characterClass == "Warlock")
		{
			character.maxHitPoints = 8 + character.constitution.modifier;
		}
		else if (character.characterClass == "Sorcerer" || character.characterClass == "Wizard")
		{
			character.maxHitPoints = 6 + character.constitution.modifier;
		}

		// Health increases with level based on a hit die roll and constitution modifier
		if (character.level > 1)
		{
			if (character.characterClass == "Barbarian")
			{
				character.maxHitPoints += Random::drawNumber(1, 12) + character.constitution.modifier;
			}
			else if (character.characterClass == "Fighter" || character.characterClass == "Paladin" || character.characterClass == "Ranger")
			{
				character.maxHitPoints += Random::drawNumber(1, 10) + character.constitution.modifier;
			}
			else if (character.characterClass == "Bard" || character.characterClass == "Cleric" || character.characterClass == "Druid" || character.characterClass == "Monk"
				|| character.characterClass == "Rogue" || character.characterClass == "Warlock")
			{
				character.maxHitPoints += Random::drawNumber(1, 8) + character.constitution.modifier;
			}
			else if (character.characterClass == "Sorcerer" || character.characterClass == "Wizard")
			{
				character.maxHitPoints += Random::drawNumber(1, 6) + character.constitution.modifier;
			}
		}

		// Add other modifiers
	}

	void generateSpeed(Character & character)
	{
		if (character.race == "Dwarf" || character.race == "Hill Dwarf" || character.race == "Mountain Dwarf"
			|| character.race == "Halfling" || character.race == "Lightfoot Halfling" || character.race == "Stout Halfling")
		{
			character.speed = 25;
		}
		else if (character.race == "Elf" || character.race == "High Elf" || character.race == "Wood Elf" || character.race == "Dark Elf (Drow)"
			|| character.race == "Human")
		{
			character.speed = 30;
		}
	}

	void generateInitiative(Character & character)
	{
		character.initiative = character.dexterity.modifier;

		// Add other modifiers
	}

	void generateEquipment(Character& character)
	{
	}

	void generateAttacks(Character& character)
	{
	}

	void generateSpellcastingTraits(Character& character)
	{
	}


	// ======================================================================================
	// Generate Character
	// ======================================================================================

	void generateCharacter(Character& character)
	{
		Random::init();

		// Descriptors
		generateClass(character);
		generateRace(character);
		generateBackground(character);
		generateAlignment(character);
		generateSex(character);
		generateFirstName(character);
		generateSurname(character);
		generatePersonalityTraits(character);
		generateIdeals(character);
		generateBonds(character);
		generateFlaws(character);

		// Skills, Abilities, and Level
		generateLevel(character);
		generateProficiencyBonus(character);

		generateAbilityScores(character);
		generateRacialAbilityBonuses(character);
		generateAbilityModifiers(character);
		generateSkillProficiencies(character);
		generateSkillModifiers(character);
		generateSavingThrowProficiencies(character);
		generateSavingThrowModifiers(character);
		generatePassiveWisdom(character);

		// Feats, Traits, Proficiencies, Languages
		generateFeatsAndTraits(character);
		generateLanguages(character);

		// Equipment and Combat
		generateHitDice(character);
		generateHitPoints(character);
		generateSpeed(character);
		generateInitiative(character);
		generateEquipment(character);
		generateAttacks(character);
		generateSpellcastingTraits(character);
	}
}