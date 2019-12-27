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
using std::reference_wrapper;
using std::string;
using std::uniform_int_distribution;
using std::vector;


// ======================================================================================
// Helper Functions
// ======================================================================================

void chooseXRandomlyFrom(int x, vector<reference_wrapper<dnd::Skill> > list)
{
	// Since this uses std::reference_value, when the values in list change, the values in character, in this case, change also 

	// Randomize the order of entries and pick the first x
	std::shuffle(list.begin(), list.end(), default_random_engine(time(0)));

	for (int i = 0; i < x; ++i)
	{
		list[i].get().proficient = true;
	}
}

void getNonhumanNames(ifstream& in, string line, vector<string>& possibleNames)
{
	if (in)
	{
		while (getline(in, line))
		{
			possibleNames.push_back(line);
		}
	}
}

void getHumanNames(ifstream& in, string line, vector<string>& possibleNames, dnd::Character character)
{
	if (in)
	{
		while (getline(in, line))
		{
			if (line.find(character.ethnicity) != string::npos)
			{
				getline(in, line);

				// If the character is a Condathan Human, skip an extra line due to how the file is formatted
				if (character.ethnicity == "Chondathan")
				{
					getline(in, line);
				}

				while (line != "" && !in.eof())
				{
					possibleNames.push_back(line);
					getline(in, line);
				}
				in.seekg(0, in.end);
			}
		}
	}
}

namespace dnd 
{
	// ======================================================================================
	// Desriptors
	// ======================================================================================

	void generateClass(Character& character)
	{
		vector<string> classes = { "Barbarian", "Bard", "Cleric", "Druid", "Fighter", "Monk", "Paladin", "Ranger", "Rogue",
								"Sorcerer", "Warlock", "Wizard" };

		static default_random_engine engine(time(0));
		static uniform_int_distribution<unsigned> dist(0, classes.size() - 1);

		character.characterClass = classes[dist(engine)];
	}

	void generateRace(Character& character)
	{
		vector<string> races = { "Dwarf", "Hill Dwarf", "Mountain Dwarf", "Elf", "High Elf", "Wood Elf", "Dark Elf (Drow)", "Halfling", "Lightfoot Halfling", "Stout Halfling", "Human" };

		static default_random_engine engine(time(0));
		static uniform_int_distribution<unsigned> dist(0, races.size() - 1);

		character.race = races[dist(engine)];

		// Humans also have ethnicity (for name)
		if (character.race == "Human")
		{
			vector<string> ethnicities = { "Calishite", "Chondathan", "Damaran", "Illuskan", "Mulan", "Rashemi", "Shou", "Tethyrian", "Turami" };

			static default_random_engine engine2(time(0));
			static uniform_int_distribution<unsigned> dist2(0, 8);

			character.ethnicity = ethnicities[dist2(engine2)];
		}
	}

	void generateBackground(Character& character)
	{
		// Variants: Spy (Criminal), Gladiator (Entertainer), Guild Merchant (Guild Artisan), Knight (Noble), Pirate (Sailor)
		vector<string> backgrounds = { "Acolyte", "Charlatan", "Criminal", "Entertainer", "Folk Hero", "Gladiator", "Guild Artisan",
									"Guild Merchant", "Hermit", "Knight", "Noble", "Outlander", "Pirate", "Sage", "Sailor", "Soldier",
									"Spy", "Urchin" };

		static default_random_engine engine(time(0));
		static uniform_int_distribution<unsigned> dist(0, backgrounds.size() - 1);

		character.background = backgrounds[dist(engine)];
	}

	void generateAlignment(Character& character)
	{
		vector<string> alignments = { "Lawful Good", "Neutral Good", "Chaotic Good", "Lawful Neutral", "Neutral", "Chaotic Neutral",
									"Lawful Evil", "Neutral Evil", "Chaotic Evil" };

		static default_random_engine engine(time(0));
		static uniform_int_distribution<unsigned> dist(0, alignments.size() - 1);

		character.alignment = alignments[dist(engine)];
	}

	void generateSex(Character& character)
	{
		// Sex needed to generate random name
		if (character.sex == "")
		{
			vector<string> sexes = { "Male", "Female" };

			static default_random_engine engine(time(0));
			static uniform_int_distribution<unsigned> dist(0, sexes.size() - 1);

			character.sex = sexes[dist(engine)];

		}
	}

	void generateFirstName(Character& character)
	{
		vector<string> possibleNames;
		ifstream in;
		string line;

		if ((character.race == "Dwarf") || (character.race == "Hill Dwarf") || (character.race == "Mountain Dwarf"))
		{
			if (character.sex == "Male")
			{
				in.open("Lists/Names/Dwarf Names/Dwarf Male Names.txt");
				getNonhumanNames(in, line, possibleNames);
			}
			else if (character.sex == "Female")
			{
				in.open("Lists/Names/Dwarf Names/Dwarf Female Names.txt");
				getNonhumanNames(in, line, possibleNames);
			}
		}
		else if (character.race == "Elf" || character.race == "High Elf" || character.race == "Wood Elf" || character.race == "Dark Elf (Drow)")
		{
			if (character.sex == "Male")
			{
				in.open("Lists/Names/Elf Names/Elf Male Names.txt");
				getNonhumanNames(in, line, possibleNames);
			}
			else if (character.sex == "Female")
			{
				in.open("Lists/Names/Elf Names/Elf Female Names.txt");
				getNonhumanNames(in, line, possibleNames);
			}
		}
		else if (character.race == "Halfling" || character.race == "Lightfoot Halfling" || character.race == "Stout Halfling")
		{
			if (character.sex == "Male")
			{
				in.open("Lists/Names/Halfling Names/Halfling Male Names.txt");
				getNonhumanNames(in, line, possibleNames);
			}
			else if (character.sex == "Female")
			{
				in.open("Lists/Names/Halfling Names/Halfling Female Names.txt");
				getNonhumanNames(in, line, possibleNames);
			}
		}
		else if (character.race == "Human")
		{
			if (character.sex == "Male")
			{
				in.open("Lists/Names/Human Names/Human Male Names.txt");
				getHumanNames(in, line, possibleNames, character);
			}
			else if (character.sex == "Female")
			{
				in.open("Lists/Names/Human Names/Human Female Names.txt");
				getHumanNames(in, line, possibleNames, character);
			}
		}

		// Shuffle the list of possible names and pick the first one
		// Note: Done this way because choosing a random element as in the other functions
		// threw a "vector subscript out of range" exception
		std::shuffle(possibleNames.begin(), possibleNames.end(), default_random_engine(time(0)));
		character.firstName = possibleNames[0];
	}

	void generateSurname(Character& character)
	{
		vector<string> possibleNames;
		ifstream in;
		string line;

		if (character.race == "Dwarf" || character.race == "Hill Dwarf" || character.race == "Mountain Dwarf")
		{
			in.open("Lists/Names/Dwarf Names/Dwarf Clan Names.txt");
			getNonhumanNames(in, line, possibleNames);
		}
		else if (character.race == "Elf" || character.race == "High Elf" || character.race == "Wood Elf" || character.race == "Dark Elf (Drow)")
		{
			in.open("Lists/Names/Elf Names/Elf Family Names.txt");
			getNonhumanNames(in, line, possibleNames);
		}
		else if (character.race == "Halfling" || character.race == "Lightfoot Halfling" || character.race == "Stout Halfling")
		{
			in.open("Lists/Names/Halfling Names/Halfling Family Names.txt");
			getNonhumanNames(in, line, possibleNames);
		}
		else if (character.race == "Human")
		{
			in.open("Lists/Names/Human Names/Human Surnames.txt");
			getHumanNames(in, line, possibleNames, character);
		}

		std::shuffle(possibleNames.begin(), possibleNames.end(), default_random_engine(time(0)));
		character.surname = possibleNames[0];
	}

	void generatePersonalityTraits(Character& character)
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
					if (line.find(character.background) != string::npos)
					{
						// Roll a d8 to choose a personality trait, as there are 8 pre-made choices for each background in the Player's Handbook
						// But here the d8 starts at 0 and goes to 7 because between 0 and 7 lines are skipped in the file when choosing traits
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

	void generateIdeals(Character& character)
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

	void generateBonds(Character& character)
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
					// Roll a d6 to choose a bond, as there are 6 pre-made choices for each background in the Player's Handbook
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

	void generateFlaws(Character& character)
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

	void generateLevel(Character& character)
	{
		// First entry null so that expForLevel[1] is how much exp is required for level one, etc.
		vector<int> expForLevel = { NULL, 0, 300, 900, 2700, 6500, 14000, 23000, 34000, 48000, 64000, 85000, 100000, 120000, 140000, 165000, 195000, 225000, 265000, 305000, 355000 };

		static default_random_engine engine(time(0));
		static uniform_int_distribution<unsigned> dist(1, 20);

		character.level = dist(engine);

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
		vector<string> possibleLanguages = { "Dwarvish", "Elvish", "Giant", "Gnomish", "Goblin", "Halfling", "Orc", // Common Languages
			"Abyssal", "Celestial", "Draconic", "Deep Speech", "Infernal", "Primordial", "Sylvan", "Undercommon" };			  // Exotic Languages

		static default_random_engine engine(time(0));
		static uniform_int_distribution<unsigned> dist(0, possibleLanguages.size() - 1);

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
				character.languages.push_back(possibleLanguages[dist(engine)]);
			}
		}
		else if (character.race == "Halfling" || character.race == "Lightfoot Halfling" || character.race == "Stout Halfling")
		{
			character.languages.push_back("Halfling");
		}
		else if (character.race == "Human")
		{
			// Humans can pick any language
			character.languages.push_back(possibleLanguages[dist(engine)]);
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

		static default_random_engine engine(time(0));

		// Health increases with level based on a hit die roll and constitution modifier
		if (character.level > 1)
		{
			if (character.characterClass == "Barbarian")
			{
				static uniform_int_distribution<unsigned> dist(1, 12);
				character.maxHitPoints += dist(engine) + character.constitution.modifier;
			}
			else if (character.characterClass == "Fighter" || character.characterClass == "Paladin" || character.characterClass == "Ranger")
			{
				static uniform_int_distribution<unsigned> dist(1, 10);
				character.maxHitPoints += dist(engine) + character.constitution.modifier;
			}
			else if (character.characterClass == "Bard" || character.characterClass == "Cleric" || character.characterClass == "Druid" || character.characterClass == "Monk"
				|| character.characterClass == "Rogue" || character.characterClass == "Warlock")
			{
				static uniform_int_distribution<unsigned> dist(1, 8);
				character.maxHitPoints += dist(engine) + character.constitution.modifier;
			}
			else if (character.characterClass == "Sorcerer" || character.characterClass == "Wizard")
			{
				static uniform_int_distribution<unsigned> dist(1, 6);
				character.maxHitPoints += dist(engine) + character.constitution.modifier;
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