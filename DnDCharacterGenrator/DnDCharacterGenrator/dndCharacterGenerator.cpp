#include "dndCharacter.h"
#include "dndCharacterGenerator.h"
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
	vector<string> races = { "Dwarf", "Elf", "Halfling", "Human" };

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
	// Gender needed to generate random name
	if (character.gender == "")
	{
		// Probably overkill, but for for the sake of consistency . . .

		vector<string> genders = { "Male", "Female" };

		static default_random_engine engine(time(0));
		static uniform_int_distribution<unsigned> dist(0, genders.size() - 1);

		character.gender = genders[dist(engine)];
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
// Values
// ======================================================================================

void dndCharacterGenerator::generateLevel(dndCharacter& character)
{
}

void dndCharacterGenerator::generateProficiencyBonus(dndCharacter & character)
{
}

void dndCharacterGenerator::generatePassiveWisdom(dndCharacter & character)
{
}


// ======================================================================================
// Skills and Abilities
// ======================================================================================


void dndCharacterGenerator::generateAbilities(dndCharacter & character)
{
}

void dndCharacterGenerator::generateSkills(dndCharacter & character)
{
}

void dndCharacterGenerator::generateSavingThrows(dndCharacter & character)
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
	generateAbilities(character);
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