#include "dndCharacter.h"
#include "Random.h"

#include <algorithm>
#include <fstream>
#include <random>
#include <string>
#include <vector>

// Temporary
#include <iostream>

namespace dnd {

// ======================================================================================
// Helper Functions
// ======================================================================================

// Choose a number (x) of skill proficiencies randomly from a given list
	void chooseXRandomlyFrom(int x, std::vector<std::reference_wrapper<dnd::Skill> > list)
	{
		// Since this uses std::reference_wrapper, when the values in list change, the values in character change also 

		// Randomize the order of entries and pick the first x of them
		std::shuffle(list.begin(), list.end(), Random::GetEngine());

		for (int i = 0; i < x; ++i)
		{
			list[i].get().Proficient = true;
		}
	}

	void getNonhumanNames(std::ifstream& in, std::vector<std::string>& possibleNames)
	{
		if (in)
		{
			std::string line;

			// Nonhuman names are stored as a single list, with one name per line, so read the whole file
			while (std::getline(in, line))
			{
				possibleNames.push_back(line);
			}
		}
	}

	void getHumanNames(std::ifstream& in, std::vector<std::string>& possibleNames, const Character& character)
	{
		if (in)
		{
			std::string line;

			while (std::getline(in, line))
			{
				if (line.find(character.GetEthnicity()) != std::string::npos)
				{
					// line is now the character's ethnicity, so skip a line to find the possible names
					getline(in, line);

					// If the character is a Condathan Human, skip an extra line since they share names with Tethyrian Humans,
					// making two labels to be skipped
					if (character.GetEthnicity() == "Chondathan")
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


	Character::Character()
	{
		// Descriptors
		GenerateClass();
		GenerateRace();
		GenerateBackground();
		GenerateAlignment();
		GenerateGender();
		GenerateFirstName();
		GenerateSurname();
		GeneratePersonalityTraits();
		GenerateIdeals();
		GenerateBonds();
		GenerateFlaws();

		// Skills, Abilities, and Level
		GenerateLevel();
		GenerateProficiencyBonus();

		GenerateAbilityScores();
		GenerateRacialAbilityBonuses();
		GenerateAbilityModifiers();
		GenerateSkillProficiencies();
		GenerateSkillModifiers();
		GenerateSavingThrowProficiencies();
		GenerateSavingThrowModifiers();
		GeneratePassiveWisdom();

		// Feats, Traits, Proficiencies, Languages
		GenerateFeatsAndTraits();
		GenerateLanguages();

		// Equipment and Combat
		GenerateHitDice();
		GenerateHitPoints();
		GenerateSpeed();
		GenerateInitiative();
		GenerateEquipment();
		GenerateAttacks();
		GenerateSpellcastingTraits();
	}	


	// ======================================================================================
	// Desriptors
	// ======================================================================================

	void Character::GenerateClass()
	{
		std::vector<std::string> classes = { "Barbarian", "Bard", "Cleric", "Druid", "Fighter", "Monk", "Paladin", "Ranger", "Rogue",
								"Sorcerer", "Warlock", "Wizard" };

		m_Class = classes[Random::Int(0, classes.size() - 1)];
	}

	void Character::GenerateRace()
	{
		std::vector<std::string> races = { "Dwarf", "Hill Dwarf", "Mountain Dwarf", "Elf", "High Elf", "Wood Elf", "Dark Elf (Drow)", "Halfling", "Lightfoot Halfling", "Stout Halfling", "Human" };

		m_Race = races[Random::Int(0, races.size() - 1)];

		// Humans also have ethnicity (for name)
		if (m_Race == "Human")
		{
			std::vector<std::string> ethnicities = { "Calishite", "Chondathan", "Damaran", "Illuskan", "Mulan", "Rashemi", "Shou", "Tethyrian", "Turami" };

			m_Ethnicity = ethnicities[Random::Int(0, ethnicities.size() - 1)];
		}
	}

	void Character::GenerateBackground()
	{
		// Variants: Spy (Criminal), Gladiator (Entertainer), Guild Merchant (Guild Artisan), Knight (Noble), Pirate (Sailor)
		std::vector<std::string> backgrounds = { "Acolyte", "Charlatan", "Criminal", "Entertainer", "Folk Hero", "Gladiator", "Guild Artisan",
									"Guild Merchant", "Hermit", "Knight", "Noble", "Outlander", "Pirate", "Sage", "Sailor", "Soldier",
									"Spy", "Urchin" };

		m_Background = backgrounds[Random::Int(0, backgrounds.size() - 1)];
	}

	void Character::GenerateAlignment()
	{
		std::vector<std::string> alignments = { "Lawful Good", "Neutral Good", "Chaotic Good", "Lawful Neutral", "Neutral", "Chaotic Neutral",
									"Lawful Evil", "Neutral Evil", "Chaotic Evil" };

		m_Alignment = alignments[Random::Int(0, alignments.size() - 1)];
	}

	void Character::GenerateGender()
	{
		// Gender needed to generate random name
		if (m_Gender == "")
		{
			std::vector<std::string> genders = { "Male", "Female" };

			m_Gender = genders[Random::Int(0, genders.size() - 1)];
		}
	}

	void Character::GenerateFirstName()
	{
		std::vector<std::string> possibleNames;
		std::ifstream in;

		if ((m_Race == "Dwarf") || (m_Race == "Hill Dwarf") || (m_Race == "Mountain Dwarf"))
		{
			if (m_Gender == "Male")
			{
				in.open("Lists/Names/DwarfNames/DwarfMaleNames.txt");
				getNonhumanNames(in, possibleNames);
			}
			else if (m_Gender == "Female")
			{
				in.open("Lists/Names/DwarfNames/DwarfFemaleNames.txt");
				getNonhumanNames(in, possibleNames);
			}
		}
		else if (m_Race == "Elf" || m_Race == "High Elf" || m_Race == "Wood Elf" || m_Race == "Dark Elf (Drow)")
		{
			if (m_Gender == "Male")
			{
				in.open("Lists/Names/ElfNames/ElfMaleNames.txt");
				getNonhumanNames(in, possibleNames);
			}
			else if (m_Gender == "Female")
			{
				in.open("Lists/Names/ElfNames/ElfFemaleNames.txt");
				getNonhumanNames(in, possibleNames);
			}
		}
		else if (m_Race == "Halfling" || m_Race == "Lightfoot Halfling" || m_Race == "Stout Halfling")
		{
			if (m_Gender == "Male")
			{
				in.open("Lists/Names/HalflingNames/HalflingMaleNames.txt");
				getNonhumanNames(in, possibleNames);
			}
			else if (m_Gender == "Female")
			{
				in.open("Lists/Names/HalflingNames/HalflingFemaleNames.txt");
				getNonhumanNames(in, possibleNames);
			}
		}
		else if (m_Race == "Human")
		{
			if (m_Gender == "Male")
			{
				in.open("Lists/Names/HumanNames/HumanMaleNames.txt");
				getHumanNames(in, possibleNames, *this);
			}
			else if (m_Gender == "Female")
			{
				in.open("Lists/Names/HumanNames/HumanFemaleNames.txt");
				getHumanNames(in, possibleNames, *this);
			}
		}

		// Shuffle the list of possible names and pick the first one
		// Note: Done this way because choosing a random element as in the other functions
		// threw a "vector subscript out of range" exception
		std::shuffle(possibleNames.begin(), possibleNames.end(), Random::GetEngine());
		m_FirstName = possibleNames[0];
	}

	void Character::GenerateSurname()
	{
		std::vector<std::string> possibleNames;
		std::ifstream in;

		if (m_Race == "Dwarf" || m_Race == "Hill Dwarf" || m_Race == "Mountain Dwarf")
		{
			in.open("Lists/Names/DwarfNames/DwarfClanNames.txt");
			getNonhumanNames(in, possibleNames);
		}
		else if (m_Race == "Elf" || m_Race == "High Elf" || m_Race == "Wood Elf" || m_Race == "Dark Elf (Drow)")
		{
			in.open("Lists/Names/ElfNames/ElfFamilyNames.txt");
			getNonhumanNames(in, possibleNames);
		}
		else if (m_Race == "Halfling" || m_Race == "Lightfoot Halfling" || m_Race == "Stout Halfling")
		{
			in.open("Lists/Names/HalflingNames/HalflingFamilyNames.txt");
			getNonhumanNames(in, possibleNames);
		}
		else if (m_Race == "Human")
		{
			in.open("Lists/Names/HumanNames/HumanSurnames.txt");
			getHumanNames(in, possibleNames, *this);
		}

		std::shuffle(possibleNames.begin(), possibleNames.end(), Random::GetEngine());
		m_Surname = possibleNames[0];
	}

	void Character::GeneratePersonalityTraits()
	{
		std::vector<std::string> possibleTraits;
		std::ifstream in("Lists/PersonalityTraits.txt");

		if (in)
		{
			std::string line;
			while (std::getline(in, line))
			{
				// If the current line in the file is the character's background
				if (line.find(m_Background) != std::string::npos)
				{
					getline(in, line);

					// If a character has a background that has a variant, skip an extra line due to the format of the file
					// Variants have the same traits as their base backgrounds
					if (m_Background == "Criminal" || m_Background == "Entertainer" || m_Background == "Guild Artisan"
						|| m_Background == "Noble" || m_Background == "Sailor")
					{
						getline(in, line);
					}

					while (line != "" && !in.eof())
					{
						possibleTraits.push_back(line);
						getline(in, line);
					}
					
					// Each character gets two personality traits, so shuffle the list and pick the first two
					std::shuffle(possibleTraits.begin(), possibleTraits.end(), Random::GetEngine());
					m_PersonalityTraits += possibleTraits[0] + " " + possibleTraits[1];
				}
			}
		}
	}

	void Character::GenerateIdeals()
	{
		std::ifstream in("Lists/Ideals.txt");

		if (in)
		{
			std::string line;
			std::string axis1 = m_Alignment.substr(0, m_Alignment.find(' ')); // Lawful, Neutral, or Chaotic
			std::string axis2 = m_Alignment.substr(m_Alignment.find(' ') + 1); // Good, Neutral, or Evil;
			bool flag = false;

			while (getline(in, line))
			{
				if (line.find(m_Background, 0) != std::string::npos)
				{
					// Roll a d6 to choose an ideal, as there are 6 pre-made choices for each background in the Player's Handbook
					int target = Random::Int(0, 5);

					if (m_Background == "Criminal" || m_Background == "Entertainer" || m_Background == "Guild Artisan"
						|| m_Background == "Noble" || m_Background == "Sailor")
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
						m_Ideals += line += " "; // The last line read is the trait
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

	void Character::GenerateBonds()
	{
		std::ifstream in("Lists/Bonds.txt");
		if (in)
		{
			std::string line;
			while (std::getline(in, line))
			{
				// If the current line in the file is the character's background
				if (line.find(m_Background, 0) != std::string::npos)
				{
					// Roll a d6 to choose a bond, as there are 6 pre-made choices for each background in the Player's Handbook
					int target = Random::Int(0, 5);

					// If a character has a background that has a variant, skip an extra line due to the format of the file
					// Variants have the same traits as their base backgrounds
					if (m_Background == "Criminal" || m_Background == "Entertainer" || m_Background == "Guild Artisan"
						|| m_Background == "Noble" || m_Background == "Sailor")
					{
						++target;
					}

					for (int skip = 0; skip <= target; ++skip) // Skip the number of lines that was rolled
					{
						getline(in, line);
					}
					m_Bonds += line += " "; // The last line read is the trait
				}
			}
		}
	}

	void Character::GenerateFlaws()
	{
		std::ifstream in("Lists/Flaws.txt");
		if (in)
		{
			std::string line;
			while (getline(in, line))
			{
				// If the current line in the file is the character's background
				if (line.find(m_Background, 0) != std::string::npos)
				{
					// Roll a d6 to choose a flaw, as there are 6 pre-made choices for each background in the Player's Handbook
					int target = Random::Int(0, 5);

					// If a character has a background that has a variant, skip an extra line due to the format of the file
					// Variants have the same traits as their base backgrounds
					if (m_Background == "Criminal" || m_Background == "Entertainer" || m_Background == "Guild Artisan"
						|| m_Background == "Noble" || m_Background == "Sailor")
					{
						++target;
					}

					for (int skip = 0; skip <= target; ++skip) // Skip the number of lines that was rolled
					{
						getline(in, line);
					}
					m_Flaws += line += " "; // The last line read is the trait
				}
			}
		}
	}

	// ======================================================================================
	// Skills, Abilities, and Level
	// ======================================================================================

	void Character::GenerateLevel()
	{
		// First entry null so that expForLevel[1] is how much exp is required for level one, etc.
		std::vector<int> expForLevel = { NULL, 0, 300, 900, 2700, 6500, 14000, 23000, 34000, 48000, 64000, 85000, 100000, 120000, 140000, 165000, 195000, 225000, 265000, 305000, 355000 };

		m_Level = Random::Int(1, 20);
		m_Experience = expForLevel[m_Level]; // Character starts with 0 progress toward next level
	}

	void Character::GenerateProficiencyBonus()
	{
		if (m_Level >= 1 && m_Level <= 4)
		{
			m_ProficiencyBonus = 2;
		}
		else if (m_Level >= 5 && m_Level <= 8)
		{
			m_ProficiencyBonus = 3;
		}
		else if (m_Level >= 9 && m_Level <= 12)
		{
			m_ProficiencyBonus = 4;
		}
		else if (m_Level >= 13 && m_Level <= 16)
		{
			m_ProficiencyBonus = 5;
		}
		else if (m_Level >= 17 && m_Level <= 20)
		{
			m_ProficiencyBonus = 6;
		}
	}

	void Character::GenerateAbilityScores()
	{
		// Roll four d6 and record the sum of the highest three results
		// Do this for each of the six abilities
		std::vector<int> results;
		std::vector<int> totals;

		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				results.push_back(Random::Int(1, 6));
			}

			std::sort(results.begin(), results.end(), std::greater<int>()); // Put the results in order of greatest to least
			totals.push_back(results[0] + results[1] + results[2]); // Add the greatest three results of this run and put the sum in totals
		}

		// Assign ability scores to the values in totals
		m_Strength.Score = totals[0];
		m_Dexterity.Score = totals[1];
		m_Constitution.Score= totals[2];
		m_Intelligence.Score= totals[3];
		m_Wisdom.Score= totals[4];
		m_Charisma.Score= totals[5];
	}

	void Character::GenerateRacialAbilityBonuses()
	{
		// Subraces also get parent race benefits
		if (m_Race == "Dwarf" || m_Race == "Hill Dwarf" || m_Race == "Mountain Dwarf")
		{
			m_Constitution.Score+= 2;
		}
		if (m_Race == "Hill Dwarf")
		{
			m_Wisdom.Score++;
		}
		if (m_Race == "Mountain Dwarf")
		{
			m_Strength.Score+= 2;
		}

		if (m_Race == "Elf" || m_Race == "High Elf" || m_Race == "Wood Elf" || m_Race == "Dark Elf (Drow)")
		{
			m_Dexterity.Score+= 2;
		}
		if (m_Race == "High Elf")
		{
			m_Intelligence.Score++;
		}
		if (m_Race == "Wood Elf")
		{
			m_Wisdom.Score++;
		}
		if (m_Race == "Dark Elf (Drow)")
		{
			m_Charisma.Score++;
		}

		if (m_Race == "Halfling" || m_Race == "Lightfoot Halfling" || m_Race == "Stout Halfling")
		{
			m_Dexterity.Score+= 2;
		}
		if (m_Race == "Lightfoot Halfling")
		{
			m_Charisma.Score++;
		}
		if (m_Race == "Stout Halfling")
		{
			m_Constitution.Score++;
		}

		if (m_Race == "Human")
		{
			m_Strength.Score++;
			m_Dexterity.Score++;
			m_Constitution.Score++;
			m_Intelligence.Score++;
			m_Wisdom.Score++;
			m_Charisma.Score++;
		}
	}

	void Character::GenerateAbilityModifiers()
	{
		std::vector<Ability> abilities = { m_Strength, m_Dexterity, m_Constitution, m_Intelligence, m_Wisdom, m_Charisma };

		for (size_t i = 0; i < abilities.size(); ++i)
		{
			// Always round down (toward -inf)
			int temp = abilities[i].Score- 10;

			if (temp >= 0)
				abilities[i].Modifier = temp / 2;
			else
				abilities[i].Modifier = (temp - 1) / 2;
		}

		m_Strength.Modifier = abilities[0].Modifier;
		m_Dexterity.Modifier = abilities[1].Modifier;
		m_Constitution.Modifier = abilities[2].Modifier;
		m_Intelligence.Modifier = abilities[3].Modifier;
		m_Wisdom.Modifier = abilities[4].Modifier;
		m_Charisma.Modifier = abilities[5].Modifier;
	}

	void Character::GenerateSkillProficiencies()
	{
		if (m_Class == "Barbarian")
		{
			chooseXRandomlyFrom(2, { m_AnimalHandling, m_Athletics, m_Intimidation, m_Nature, m_Perception, m_Survival });
		}
		if (m_Class == "Bard")
		{
			// Pick any three skills
			chooseXRandomlyFrom(3, { m_Acrobatics, m_AnimalHandling, m_Arcana, m_Athletics, m_Deception, m_History, m_Insight,
				m_Intimidation, m_Investigation, m_Medicine, m_Nature, m_Perception, m_Performance, m_Persuasion, m_Religion,
				m_SleightOfHand, m_Stealth, m_Survival });
		}
		if (m_Class == "Cleric")
		{
			chooseXRandomlyFrom(2, { m_History, m_Insight, m_Medicine, m_Persuasion, m_Religion });
		}
		if (m_Class == "Druid")
		{
			chooseXRandomlyFrom(2, { m_Arcana, m_AnimalHandling, m_Insight, m_Medicine, m_Nature, m_Perception, m_Religion, m_Survival });
		}
		if (m_Class == "Fighter")
		{
			chooseXRandomlyFrom(2, { m_Acrobatics, m_AnimalHandling, m_Athletics, m_History, m_Insight, m_Intimidation, m_Perception,
				m_Survival });
		}
		if (m_Class == "Monk")
		{
			chooseXRandomlyFrom(2, { m_Acrobatics, m_Athletics, m_History, m_Insight, m_Religion, m_Stealth });
		}
		if (m_Class == "Paladin")
		{
			chooseXRandomlyFrom(2, { m_Athletics, m_Insight, m_Intimidation, m_Medicine, m_Persuasion, m_Religion });
		}
		if (m_Class == "Ranger")
		{
			chooseXRandomlyFrom(3, { m_AnimalHandling, m_Athletics, m_Insight, m_Investigation, m_Nature, m_Perception,
				m_Stealth, m_Survival });
		}
		if (m_Class == "Rogue")
		{
			chooseXRandomlyFrom(4, { m_Acrobatics, m_Athletics, m_Deception, m_Insight, m_Intimidation,
				m_Investigation, m_Perception, m_Performance, m_Persuasion, m_SleightOfHand, m_Stealth });
		}
		if (m_Class == "Sorceror")
		{
			chooseXRandomlyFrom(2, { m_Arcana, m_Deception, m_Insight, m_Intimidation, m_Persuasion, m_Religion });
		}
		if (m_Class == "Warlock")
		{
			chooseXRandomlyFrom(2, { m_Arcana, m_Deception, m_History, m_Intimidation, m_Investigation, m_Nature, m_Religion });
		}
		if (m_Class == "Wizard")
		{
			chooseXRandomlyFrom(2, { m_Arcana, m_History, m_Insight, m_Investigation, m_Medicine, m_Religion });
		}
	}

	void Character::GenerateSkillModifiers()
	{
		// Skill modifiers are based on the abilities that govern them
		m_Athletics.Parent = m_Strength;
		m_Acrobatics.Parent = m_SleightOfHand.Parent = m_Stealth.Parent = m_Dexterity;
		m_Arcana.Parent = m_History.Parent = m_Investigation.Parent = m_Nature.Parent = m_Religion.Parent = m_Intelligence;
		m_AnimalHandling.Parent = m_Insight.Parent = m_Medicine.Parent = m_Perception.Parent = m_Survival.Parent = m_Wisdom;
		m_Deception.Parent = m_Intimidation.Parent = m_Performance.Parent = m_Persuasion.Parent = m_Charisma;

		std::vector<std::reference_wrapper<Skill> > skills = { m_Acrobatics, m_AnimalHandling, m_Arcana, m_Athletics, m_Deception, m_History, m_Insight,
			m_Intimidation, m_Investigation, m_Medicine, m_Nature, m_Perception, m_Performance, m_Persuasion, m_Religion,
			m_SleightOfHand, m_Stealth, m_Survival };

		for (size_t i = 0; i < skills.size(); ++i)
		{
			// Start at parent ability's modifier
			skills[i].get().Modifier = skills[i].get().Parent.Modifier;

			// If the character is proficient in a skill, add proficiency bonus to the modifier
			if (skills[i].get().Proficient)
			{
				skills[i].get().Modifier += m_ProficiencyBonus;
			}

			// Add other proficiencies
		}
	}

	void Character::GenerateSavingThrowProficiencies()
	{
		if (m_Class == "Barbarian")
		{
			m_StrengthSave.Proficient = true;
			m_ConstitutionSave.Proficient = true;
		}
		if (m_Class == "Bard")
		{
			m_DexteritySave.Proficient = true;
			m_CharismaSave.Proficient = true;
		}
		if (m_Class == "Cleric")
		{
			m_WisdomSave.Proficient = true;
			m_CharismaSave.Proficient = true;
		}
		if (m_Class == "Druid")
		{
			m_IntelligenceSave.Proficient = true;
			m_WisdomSave.Proficient = true;
		}
		if (m_Class == "Fighter")
		{
			m_StrengthSave.Proficient = true;
			m_ConstitutionSave.Proficient = true;
		}
		if (m_Class == "Monk")
		{
			m_StrengthSave.Proficient = true;
			m_DexteritySave.Proficient = true;
		}
		if (m_Class == "Paladin")
		{
			m_WisdomSave.Proficient = true;
			m_CharismaSave.Proficient = true;
		}
		if (m_Class == "Ranger")
		{
			m_StrengthSave.Proficient = true;
			m_DexteritySave.Proficient = true;
		}
		if (m_Class == "Rogue")
		{
			m_DexteritySave.Proficient = true;
			m_IntelligenceSave.Proficient = true;
		}
		if (m_Class == "Sorceror")
		{
			m_ConstitutionSave.Proficient = true;
			m_CharismaSave.Proficient = true;
		}
		if (m_Class == "Warlock")
		{
			m_WisdomSave.Proficient = true;
			m_CharismaSave.Proficient = true;
		}
		if (m_Class == "Wizard")
		{
			m_IntelligenceSave.Proficient = true;
			m_WisdomSave.Proficient = true;
		}
	}

	void Character::GenerateSavingThrowModifiers()
	{
		m_StrengthSave.Parent = m_Strength;
		m_DexteritySave.Parent = m_Dexterity;
		m_ConstitutionSave.Parent = m_Constitution;
		m_IntelligenceSave.Parent = m_Intelligence;
		m_WisdomSave.Parent = m_Wisdom;
		m_CharismaSave.Parent = m_Charisma;

		std::vector<std::reference_wrapper<Skill> > saves = { m_StrengthSave, m_DexteritySave, m_ConstitutionSave, m_IntelligenceSave,
			m_WisdomSave, m_CharismaSave };

		// Start at parent ability's modifier
		for (size_t i = 0; i < saves.size(); ++i)
		{
			saves[i].get().Modifier = saves[i].get().Parent.Modifier;
		}

		// Add profiency bonus if proficient in saving throw
		for (size_t i = 0; i < saves.size(); ++i)
		{
			if (saves[i].get().Proficient)
			{
				saves[i].get().Modifier += m_ProficiencyBonus;
			}
		}
	}

	void Character::GeneratePassiveWisdom()
	{
		// Passive wisdom is wisdom modifier + 10 + proficiency bonus (if proficient in perception)
		m_PassiveWisdom = m_Wisdom.Modifier + 10;

		if (m_Perception.Proficient)
		{
			m_PassiveWisdom += m_ProficiencyBonus;
		}
	}


	// ======================================================================================
	// Feats, Traits, Proficiencies, Languages
	// ======================================================================================


	void Character::GenerateRacialTraits()
	{
	}

	void Character::GenerateFeatsAndTraits()
	{

	}

	void Character::GenerateProficiencies()
	{
	}

	void Character::GenerateLanguages()
	{
		m_Languages.push_back("Common"); // All characters can speak, read, and write in the Common tongue

		// Common is not a possible language because every character already knows it
		std::vector<std::string> possibleLanguages = { "Elvish", "Dwarvish", "Giant", "Gnomish", "Goblin", "Halfling", "Orc", // Common Languages
			"Abyssal", "Celestial", "Draconic", "Deep Speech", "Infernal", "Primordial", "Sylvan", "Undercommon" };	// Exotic Languages

		if (m_Race == "Dwarf" || m_Race == "Hill Dwarf" || m_Race == "Mountain Dwarf")
		{
			m_Languages.push_back("Dwarvish");
		}
		else if (m_Race == "Elf" || m_Race == "High Elf" || m_Race == "Wood Elf" || m_Race == "Dark Elf (Drow)")
		{
			m_Languages.push_back("Elvish");

			// High Elves have the Extra Language Trait
			if (m_Race == "High Elf")
			{
				// 1 is the minimum number to avoid picking Elvish twice
				m_Languages.push_back(possibleLanguages[Random::Int(1, possibleLanguages.size() - 1)]);
			}
		}
		else if (m_Race == "Halfling" || m_Race == "Lightfoot Halfling" || m_Race == "Stout Halfling")
		{
			m_Languages.push_back("Halfling");
		}
		else if (m_Race == "Human")
		{
			// Humans can pick any language
			m_Languages.push_back(possibleLanguages[Random::Int(0, possibleLanguages.size() - 1)]);
		}
	}


	// ======================================================================================
	// Equipment and Combat
	// ======================================================================================

	void Character::GenerateHitDice()
	{
		if (m_Class == "Barbarian")
		{
			m_HitDice.Type = "d12";
		}
		else if (m_Class == "Fighter" || m_Class == "Paladin" || m_Class == "Ranger")
		{
			m_HitDice.Type = "d10";
		}
		else if (m_Class == "Bard" || m_Class == "Cleric" || m_Class == "Druid" || m_Class == "Monk"
			|| m_Class == "Rogue" || m_Class == "Warlock")
		{
			m_HitDice.Type = "d8";
		}
		else if (m_Class == "Sorceror" || m_Class == "Wizard")
		{
			m_HitDice.Type = "d6";
		}

		m_HitDice.Number = m_Level;
	}

	void Character::GenerateHitPoints()
	{
		// At level 1, characters start with the max roll of their hit die plus their constitution modifier
		if (m_Class == "Barbarian")
		{
			m_MaxHitPoints = 12 + m_Constitution.Modifier;
		}
		else if (m_Class == "Fighter" || m_Class == "Paladin" || m_Class == "Ranger")
		{
			m_MaxHitPoints = 10 + m_Constitution.Modifier;
		}
		else if (m_Class == "Bard" || m_Class == "Cleric" || m_Class == "Druid" || m_Class == "Monk"
			|| m_Class == "Rogue" || m_Class == "Warlock")
		{
			m_MaxHitPoints = 8 + m_Constitution.Modifier;
		}
		else if (m_Class == "Sorcerer" || m_Class == "Wizard")
		{
			m_MaxHitPoints = 6 + m_Constitution.Modifier;
		}

		// Health increases with level based on a hit die roll and constitution modifier
		if (m_Level > 1)
		{
			if (m_Class == "Barbarian")
			{
				m_MaxHitPoints += Random::Int(1, 12) + m_Constitution.Modifier;
			}
			else if (m_Class == "Fighter" || m_Class == "Paladin" || m_Class == "Ranger")
			{
				m_MaxHitPoints += Random::Int(1, 10) + m_Constitution.Modifier;
			}
			else if (m_Class == "Bard" || m_Class == "Cleric" || m_Class == "Druid" || m_Class == "Monk"
				|| m_Class == "Rogue" || m_Class == "Warlock")
			{
				m_MaxHitPoints += Random::Int(1, 8) + m_Constitution.Modifier;
			}
			else if (m_Class == "Sorcerer" || m_Class == "Wizard")
			{
				m_MaxHitPoints += Random::Int(1, 6) + m_Constitution.Modifier;
			}
		}

		// Add other modifiers
	}

	void Character::GenerateSpeed()
	{
		if (m_Race == "Dwarf" || m_Race == "Hill Dwarf" || m_Race == "Mountain Dwarf"
			|| m_Race == "Halfling" || m_Race == "Lightfoot Halfling" || m_Race == "Stout Halfling")
		{
			m_Speed = 25;
		}
		else if (m_Race == "Elf" || m_Race == "High Elf" || m_Race == "Wood Elf" || m_Race == "Dark Elf (Drow)"
			|| m_Race == "Human")
		{
			m_Speed = 30;
		}
	}

	void Character::GenerateInitiative()
	{
		m_Initiative = m_Dexterity.Modifier;

		// Add other modifiers
	}

	void Character::GenerateEquipment()
	{
	}

	void Character::GenerateAttacks()
	{
	}

	void Character::GenerateSpellcastingTraits()
	{
	}

	// Temporary
	void Character::DisplayCharacterSheet()
	{
		std::cout << std::boolalpha;

		std::cout << "Name: " << m_FirstName << " " << m_Surname << "\n";
		std::cout << "Sex: " << m_Gender << "\n";
		std::cout << "Race: " << m_Race << "\n";
		if (m_Race == "Human")
		{
			std::cout << "Ethnicity: " << m_Ethnicity << "\n";
		}
		std::cout << "Class: " << m_Class << "\n";
		std::cout << "Level: " << m_Level << "\n";
		std::cout << "Experience Points: " << m_Experience << "\n";
		std::cout << "Proficiency Bonus: " << m_ProficiencyBonus << "\n";
		std::cout << "Hit Points: " << m_MaxHitPoints << "\n";
		std::cout << "Speed: " << m_Speed << "\n";
		std::cout << "Initiative: " << m_Initiative << "\n";
		std::cout << "Background: " << m_Background << "\n";
		std::cout << "Alignment: " << m_Alignment << "\n\n";
		std::cout << "Personality Traits: " << m_PersonalityTraits << "\n\n";
		std::cout << "Ideals: " << m_Ideals << "\n\n";
		std::cout << "Bonds: " << m_Bonds << "\n\n";
		std::cout << "Flaws: " << m_Flaws << "\n\n";

		std::cout << "Languages: ";
		for (size_t i = 0; i < m_Languages.size(); ++i)
		{
			std::cout << m_Languages[i];
			if (i != m_Languages.size() - 1)
			{
				std::cout << ", ";
			}
		}
		std::cout << "\n\n";

		std::cout << "========\n";
		std::cout << "Abilites\n";
		std::cout << "========\n";
		std::cout << "Strength\n";
		std::cout << "Score: " << m_Strength.Score << "\n";
		std::cout << "Modifier: " << m_Strength.Modifier << "\n\n";
		std::cout << "Dexterity\n";
		std::cout << "Score: " << m_Dexterity.Score << "\n";
		std::cout << "Modifier: " << m_Dexterity.Modifier << "\n\n";
		std::cout << "Constitution\n";
		std::cout << "Score: " << m_Constitution.Score << "\n";
		std::cout << "Modifier: " << m_Constitution.Modifier << "\n\n";
		std::cout << "Intelligence\n";
		std::cout << "Score: " << m_Intelligence.Score << "\n";
		std::cout << "Modifier: " << m_Intelligence.Modifier << "\n\n";
		std::cout << "Wisdom\n";
		std::cout << "Score: " << m_Wisdom.Score << "\n";
		std::cout << "Modifier: " << m_Wisdom.Modifier << "\n\n";
		std::cout << "Charisma\n";
		std::cout << "Score: " << m_Charisma.Score << "\n";
		std::cout << "Modifier: " << m_Charisma.Modifier << "\n\n";

		std::cout << "=============\n";
		std::cout << "Saving Throws\n";
		std::cout << "=============\n";
		std::cout << "Proficiencies\n";
		std::cout << "Strength: " << m_StrengthSave.Proficient << "\n";
		std::cout << "Dexterity: " << m_DexteritySave.Proficient << "\n";
		std::cout << "Constitution: " << m_ConstitutionSave.Proficient << "\n";
		std::cout << "Intelligence: " << m_IntelligenceSave.Proficient << "\n";
		std::cout << "Wisdom: " << m_WisdomSave.Proficient << "\n";
		std::cout << "Charisma: " << m_CharismaSave.Proficient << "\n\n";
		std::cout << "Modifiers\n";
		std::cout << "Strength: " << m_StrengthSave.Modifier << "\n";
		std::cout << "Dexterity: " << m_DexteritySave.Modifier << "\n";
		std::cout << "Constitution: " << m_Constitution.Modifier << "\n";
		std::cout << "Intelligence: " << m_IntelligenceSave.Modifier << "\n";
		std::cout << "Wisdom: " << m_WisdomSave.Modifier << "\n";
		std::cout << "Charisma: " << m_CharismaSave.Modifier << "\n\n";

		std::cout << "======\n";
		std::cout << "Skills\n";
		std::cout << "======\n";
		std::cout << "Proficiencies\n";
		std::cout << "Acrobatics:      " << m_Acrobatics.Proficient << "\n";
		std::cout << "Animal Handling: " << m_AnimalHandling.Proficient << "\n";
		std::cout << "Arcana:          " << m_Arcana.Proficient << "\n";
		std::cout << "Athletics:       " << m_Athletics.Proficient << "\n";
		std::cout << "Deception:       " << m_Deception.Proficient << "\n";
		std::cout << "History:         " << m_History.Proficient << "\n";
		std::cout << "Insight:         " << m_Insight.Proficient << "\n";
		std::cout << "Intimidation:    " << m_Intimidation.Proficient << "\n";
		std::cout << "Investigation:   " << m_Investigation.Proficient << "\n";
		std::cout << "Medicine:        " << m_Medicine.Proficient << "\n";
		std::cout << "Nature:          " << m_Nature.Proficient << "\n";
		std::cout << "Perception:      " << m_Perception.Proficient << "\n";
		std::cout << "Performance:     " << m_Performance.Proficient << "\n";
		std::cout << "Persuasion:      " << m_Persuasion.Proficient << "\n";
		std::cout << "Religion:        " << m_Religion.Proficient << "\n";
		std::cout << "Sleight of Hand: " << m_SleightOfHand.Proficient << "\n";
		std::cout << "Stealth:         " << m_Stealth.Proficient << "\n";
		std::cout << "Survival:        " << m_Survival.Proficient << "\n\n";
		std::cout << "Modifiers\n";
		std::cout << "Acrobatics:      " << m_Acrobatics.Modifier << "\n";
		std::cout << "Animal Handling: " << m_AnimalHandling.Modifier << "\n";
		std::cout << "Arcana:          " << m_Arcana.Modifier << "\n";
		std::cout << "Athletics:       " << m_Athletics.Modifier << "\n";
		std::cout << "Deception:       " << m_Deception.Modifier << "\n";
		std::cout << "History:         " << m_History.Modifier << "\n";
		std::cout << "Insight:         " << m_Insight.Modifier << "\n";
		std::cout << "Intimidation:    " << m_Intimidation.Modifier << "\n";
		std::cout << "Investigation:   " << m_Investigation.Modifier << "\n";
		std::cout << "Medicine:        " << m_Medicine.Modifier << "\n";
		std::cout << "Nature:          " << m_Nature.Modifier << "\n";
		std::cout << "Perception:      " << m_Perception.Modifier << "\n";
		std::cout << "Performance:     " << m_Performance.Modifier << "\n";
		std::cout << "Persuasion:      " << m_Persuasion.Modifier << "\n";
		std::cout << "Religion:        " << m_Religion.Modifier << "\n";
		std::cout << "Sleight of Hand: " << m_SleightOfHand.Modifier << "\n";
		std::cout << "Stealth:         " << m_Stealth.Modifier << "\n";
		std::cout << "Survival:        " << m_Survival.Modifier << "\n\n";

		std::cout << "Passive Wisdom (Perception): " << m_PassiveWisdom << "\n";
	}
}