#include "dndCharacter.h"
#include "dndCharacterGenerator.h"
#include <algorithm>
#include <ctime>
#include <fstream>
#include <random>
#include <string>
#include <vector>
using std::default_random_engine;
using std::getline;
using std::ifstream;
using std::string;
using std::uniform_int_distribution;
using std::vector;

dndCharacterGenerator::dndCharacterGenerator()
{
}

// ======================================================================================
// Desriptors
// ======================================================================================

void dndCharacterGenerator::generateClass(dndCharacter& character)
{
	vector<string> classes = { "Barbarian", "Bard", "Cleric", "Druid", "Fighter", "Monk", "Paladin", "Ranger", "Rogue", 
							"Sorcerer", "Warlock", "Wizard" };

	static default_random_engine engine(time(0));
	static uniform_int_distribution<unsigned> dist(0, classes.size() - 1);

	character.characterClass = classes[dist(engine)];
}

void dndCharacterGenerator::generateRace(dndCharacter& character)
{
	vector<string> races = { "Dwarf", "Hill Dwarf", "Mountain Dwarf", "Elf", "High Elf", "Wood Elf", "Dark Elf (Drow)", "Halfling", "Lightfoot Halfling", "Stout Halfling", "Human" };

	static default_random_engine engine(time(0));
	static uniform_int_distribution<unsigned> dist(0, races.size() - 1);

	character.race = races[dist(engine)];
}

void dndCharacterGenerator::generateBackground(dndCharacter& character)
{
	// Variants: Spy (Criminal), Gladiator (Entertainer), Guild Merchant (Guild Artisan), Knight (Noble), Pirate (Sailor)
	vector<string> backgrounds = { "Acolyte", "Charlatan", "Criminal", "Entertainer", "Folk Hero", "Gladiator", "Guild Artisan", 
								"Guild Merchant", "Hermit", "Knight", "Noble", "Outlander", "Pirate", "Sage", "Sailor", "Soldier", 
								"Spy", "Urchin" };

	static default_random_engine engine(time(0));
	static uniform_int_distribution<unsigned> dist(0, backgrounds.size() - 1);

	character.background = backgrounds[dist(engine)];
}

void dndCharacterGenerator::generateAlignment(dndCharacter& character)
{
	vector<string> alignments = { "Lawful Good", "Neutral Good", "Chaotic Good", "Lawful Neutral", "Neutral", "Chaotic Neutral",
								"Lawful Evil", "Neutral Evil", "Chaotic Evil" };

	static default_random_engine engine(time(0));
	static uniform_int_distribution<unsigned> dist(0, alignments.size() - 1);

	character.alignment = alignments[dist(engine)];
}

void dndCharacterGenerator::generateName(dndCharacter& character)
{
	// Sex needed to generate random name
	if (character.sex == "")
	{
		// Probably overkill, but for for the sake of consistency . . .

		vector<string> sexes = { "Male", "Female" };

		static default_random_engine engine(time(0));
		static uniform_int_distribution<unsigned> dist(0, sexes.size() - 1);

		character.sex = sexes[dist(engine)];
	}

	// Generate Random Name
}

void dndCharacterGenerator::generatePersonalityTraits(dndCharacter & character)
{
	for (int i = 1; i <= 2; ++i) // Each character gets two personality traits
	{
		static default_random_engine engine(time(0));
		static uniform_int_distribution<unsigned> dist(0, 7);

		ifstream in("Lists/Personality Traits.txt");
		if (in)
		{
			string line;
			while (getline(in, line))
			{
				// If the current line in the file is the character's background
				if (line.find(character.background, 0) != string::npos)
				{
					// Roll a d8 to choose a personality trait, as there are 8 pre-made choices for each background in the Player's Handbook
					int target = dist(engine); 

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
					character.personalityTraits += line += " "; // The last line read is the trait
				}
			}

		}
	}
}

void dndCharacterGenerator::generateIdeals(dndCharacter & character)
{
	static default_random_engine engine(time(0));
	static uniform_int_distribution<unsigned> dist(0, 5);

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
				int target = dist(engine);

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

void dndCharacterGenerator::generateBonds(dndCharacter & character)
{
	static default_random_engine engine(time(0));
	static uniform_int_distribution<unsigned> dist(0, 5);

	ifstream in("Lists/Bonds.txt");
	if (in)
	{
		string line;
		while (getline(in, line))
		{
			// If the current line in the file is the character's background
			if (line.find(character.background, 0) != string::npos)
			{
				// Roll a d6 to choose a personality trait, as there are 6 pre-made choices for each background in the Player's Handbook
				int target = dist(engine);

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

void dndCharacterGenerator::generateFlaws(dndCharacter & character)
{
	static default_random_engine engine(time(0));
	static uniform_int_distribution<unsigned> dist(0, 5);

	ifstream in("Lists/Flaws.txt");
	if (in)
	{
		string line;
		while (getline(in, line))
		{
			// If the current line in the file is the character's background
			if (line.find(character.background, 0) != string::npos)
			{
				// Roll a d6 to choose a personality trait, as there are 6 pre-made choices for each background in the Player's Handbook
				int target = dist(engine);

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

void dndCharacterGenerator::generateLevel(dndCharacter& character)
{
	// First entry null so that expForLevel[1] is how much exp is required for level one, etc.
	vector<int> expForLevel = { NULL, 0, 300, 900, 2700, 6500, 14000, 23000, 34000, 48000, 64000, 85000, 100000, 120000, 140000, 165000, 195000, 225000, 265000, 305000, 355000 };

	static default_random_engine engine(time(0));
	static uniform_int_distribution<unsigned> dist(1, 20);

	character.level = dist(engine);
	character.experience = expForLevel[character.level]; // Character starts with 0 progress toward next level
}

void dndCharacterGenerator::generateProficiencyBonus(dndCharacter & character)
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

void dndCharacterGenerator::generateAbilityScores(dndCharacter & character)
{
	// Roll four d6 and record the sum of the highest three results
	// Do this for each of the six abilities
	static default_random_engine engine(time(0));
	static uniform_int_distribution<unsigned> dist(1, 6);
	vector<int> results;
	vector<int> totals;

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			results.push_back(dist(engine));
		}

		
		std::sort(results.begin(), results.end(), std::greater<int>()); // Put the results in order of greatest to least
		totals.push_back(results[0] + results[1] + results[2]); // Add the greatest three results of this run and put the sum in totals
	}

	// Assign ability scores to the values in totals
	character.strength.score     = totals[0];
	character.dexterity.score    = totals[1];
	character.constitution.score = totals[2];
	character.intelligence.score = totals[3];
	character.wisdom.score       = totals[4];
	character.charisma.score     = totals[5];
}

void dndCharacterGenerator::generateRacialAbilityBonuses(dndCharacter & character)
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

void dndCharacterGenerator::generateAbilityModifiers(dndCharacter & character)
{
	vector<Ability> abilities = { character.strength, character.dexterity, character.constitution, character.intelligence, character.wisdom, character.charisma };

	for (int i = 0; i < 6; ++i)
	{
		abilities[i].modifier = floor((float)(abilities[i].score - 10) / 2);
	}

	character.strength.modifier     = abilities[0].modifier;
	character.dexterity.modifier    = abilities[1].modifier;
	character.constitution.modifier = abilities[2].modifier;
	character.intelligence.modifier = abilities[3].modifier;
	character.wisdom.modifier       = abilities[4].modifier;
	character.charisma.modifier     = abilities[5].modifier;
}

void dndCharacterGenerator::generateSkills(dndCharacter & character)
{

}

void dndCharacterGenerator::generateSavingThrows(dndCharacter & character)
{
}

void dndCharacterGenerator::generatePassiveWisdom(dndCharacter & character)
{
}



// ======================================================================================
// Feats, Traits, Proficiencies, Languages
// ======================================================================================

void dndCharacterGenerator::generateFeatsAndTraits(dndCharacter & character)
{
}

void dndCharacterGenerator::generateProficienciesAndLanguages(dndCharacter & character)
{
}


// ======================================================================================
// Equipment and Combat
// ======================================================================================

void dndCharacterGenerator::generateEquipment(dndCharacter & character)
{
}

void dndCharacterGenerator::generateCombatValues(dndCharacter & character)
{
}

void dndCharacterGenerator::generateAttacks(dndCharacter & character)
{
}

void dndCharacterGenerator::generateSpellcastingTraits(dndCharacter & character)
{
}


// ======================================================================================
// Generate Character
// ======================================================================================

void dndCharacterGenerator::generateCharacter(dndCharacter & character)
{
	// Descriptors
	generateClass(character);
	generateRace(character);
	generateBackground(character);
	generateAlignment(character);
	generateName(character);
	generatePersonalityTraits(character);
	generateIdeals(character);
	generateBonds(character);
	generateFlaws(character);

	// Values
	generateLevel(character);

	generateProficiencyBonus(character);
	generatePassiveWisdom(character);

	// Skills and Abilities
	generateAbilityScores(character);
	generateRacialAbilityBonuses(character);
	generateAbilityModifiers(character);
	generateSkills(character);
	generateSavingThrows(character);

	// Feats, Traits, Proficiencies, Languages
	generateFeatsAndTraits(character);
	generateProficienciesAndLanguages(character);

	// Equipment and Combat
	generateEquipment(character);
	generateCombatValues(character);
	generateAttacks(character);
	generateSpellcastingTraits(character);
}