#include "dndCharacter.h"
#include "Random.h"

#include <algorithm>
#include <string>
#include <vector>

#include "Lists.h"

// Temporary
#include <iostream>

namespace dnd {

// ======================================================================================
// Helper Functions
// ======================================================================================

	// Choose a list from a dictionary given a certain attribute of the character, and set one of their traits to a random value from the list
	template<typename S, typename T>
	void SetTraitFromDict(std::string& trait, const std::unordered_map<T, S>& dict, const std::string& criteria)
	{
		auto list = dict.at(criteria);
		trait = list[Random::Int(0, list.size() - 1)];
	}

// Choose a number of skill proficiencies randomly from a given list
	void chooseSkillProficiencies(int skillsToChoose, std::vector<std::reference_wrapper<dnd::Skill>> list)
	{
		// Since this uses std::reference_wrapper, when the values in list change, the values in character change also 

		// Randomize the order of entries and pick the first x of them
		std::shuffle(list.begin(), list.end(), Random::GetEngine());

		for (int i = 0; i < skillsToChoose; ++i)
			list[i].get().Proficient = true;
	}

	Character::Character()
	{
		// Descriptors
		GenerateClass();
		GenerateRace();
		GenerateBackground();
		GenerateAlignment();
		GenerateGender();
		GenerateName();
		GeneratePersonality();

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
		m_Class = Classes[Random::Int(0, NumClasses - 1)];
	}

	void Character::GenerateRace()
	{
		m_Race = Races[Random::Int(0, NumRaces - 1)];

		// Humans also have ethnicity (for name)
		if (m_Race == "Human")
			m_Ethnicity = Ethnicities[Random::Int(0, NumEthnicities - 1)];
		
		// Find the character's major race
		if (m_Race == "Dwarf" || m_Race == "Elf" || m_Race == "Halfling" || m_Race == "Human")
			m_MajorRace = m_Race;
		else if (m_Race == "Mountain Dwarf" || m_Race == "Hill Dwarf")
			m_MajorRace = "Dwarf";
		else if (m_Race == "High Elf" || m_Race == "Wood Elf" || m_Race == "Dark Elf (Drow)")
			m_MajorRace = "Elf";
		else if (m_Race == "Lightfoot Halfling" || m_Race == "Stout Halfling")
			m_MajorRace = "Halfling";
	}

	void Character::GenerateBackground()
	{
		m_Background = Backgrounds[Random::Int(0, NumBackgrounds - 1)];
	}

	void Character::GenerateAlignment()
	{
		m_Alignment = Alignments[Random::Int(0, NumAlignments - 1)];
	}

	void Character::GenerateGender()
	{
		m_Gender = Genders[Random::Int(0, NumGenders - 1)];
	}

	void Character::GenerateName()
	{
		if (m_Race == "Human")
		{
			if (m_Gender == "Male")
				SetTraitFromDict(m_FirstName, HumanMaleNames, m_Ethnicity);
			else if (m_Gender == "Female")
				SetTraitFromDict(m_FirstName, HumanFemaleNames, m_Ethnicity);

			SetTraitFromDict(m_Surname, HumanSurnames, m_Ethnicity);
		}
		else
		{
			if (m_Gender == "Male")
				SetTraitFromDict(m_FirstName, NonHumanMaleNames, m_MajorRace);
			else if (m_Gender == "Female")
				SetTraitFromDict(m_FirstName, NonHumanFemaleNames, m_MajorRace);

			SetTraitFromDict(m_Surname, NonHumanSurnames, m_MajorRace);
		}
	}

	void Character::GeneratePersonality()
	{
		// Personality Traits
		// Generate two unique random numbers to ensure personality traits are different
		auto personalityList = PersonalityTraits.at(m_Background);
		int first = Random::Int(0, personalityList.size() - 1);
		int second = Random::Int(0, personalityList.size() - 1);

		// Ensure two unique traits are chosen
		while (second == first)
			second = Random::Int(0, personalityList.size() - 1);

		m_PersonalityTraits = personalityList[first] + " " + personalityList[second];

		// Ideals
		std::string axis1 = m_Alignment.substr(0, m_Alignment.find(' ')); // Lawful, Neutral, or Chaotic
		std::string axis2 = m_Alignment.substr(m_Alignment.find(' ') + 1); // Good, Neutral, or Evil;
		auto idealsList = Ideals.at(m_Background);

		while (m_Ideals == "")
		{
			int index = Random::Int(0, idealsList.size() - 1);

			if (idealsList[index].first == axis1 || idealsList[index].first == axis2 || idealsList[index].first == "Any")
				m_Ideals = idealsList[index].second;
		}

		// Bonds
		SetTraitFromDict(m_Bonds, Bonds, m_Background);

		// Flaws
		SetTraitFromDict(m_Flaws, Flaws, m_Background);
	}

	// ======================================================================================
	// Skills, Abilities, and Level
	// ======================================================================================

	void Character::GenerateLevel()
	{
		m_Level = Random::Int(1, NumLevels - 1);
		m_Experience = ExpForLevel[m_Level]; // Character starts with 0 progress toward next level
	}

	void Character::GenerateProficiencyBonus()
	{
		if (m_Level >= 1 && m_Level <= 4)
			m_ProficiencyBonus = 2;
		else if (m_Level >= 5 && m_Level <= 8)
			m_ProficiencyBonus = 3;
		else if (m_Level >= 9 && m_Level <= 12)
			m_ProficiencyBonus = 4;
		else if (m_Level >= 13 && m_Level <= 16)
			m_ProficiencyBonus = 5;
		else if (m_Level >= 17 && m_Level <= 20)
			m_ProficiencyBonus = 6;
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
				results.push_back(Random::Int(1, 6));

			std::sort(results.begin(), results.end(), std::greater<int>()); // Put the results in order of greatest to least
			totals.push_back(results[0] + results[1] + results[2]); // Add the greatest three results of this run and put the sum in totals
		}

		// Assign ability scores to the values in totals
		m_Strength.Score     = totals[0];
		m_Dexterity.Score    = totals[1];
		m_Constitution.Score = totals[2];
		m_Intelligence.Score = totals[3];
		m_Wisdom.Score       = totals[4];
		m_Charisma.Score     = totals[5];
	}

	void Character::GenerateRacialAbilityBonuses()
	{
		// Subraces also get parent race benefits
		if (m_MajorRace == "Dwarf")
		{
			m_Constitution.Score += 2;

			if (m_Race == "Hill Dwarf")
				m_Wisdom.Score++;
			else if (m_Race == "Mountain Dwarf")
				m_Strength.Score += 2;
		}
		else if (m_MajorRace == "Elf")
		{
			m_Dexterity.Score += 2;
			
			if (m_Race == "High Elf")
				m_Intelligence.Score++;
			else if (m_Race == "Wood Elf")
				m_Wisdom.Score++;
			else if (m_Race == "Dark Elf (Drow)")
				m_Charisma.Score++;
		}
		else if (m_MajorRace == "Halfling")
		{
			m_Dexterity.Score += 2;

			if (m_Race == "Lightfoot Halfling")
				m_Charisma.Score++;
			else if (m_Race == "Stout Halfling")
				m_Constitution.Score++;
		}
		else if (m_Race == "Human")
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
			int temp = abilities[i].Score - 10;

			if (temp >= 0)
				abilities[i].Modifier = temp / 2;
			else
				abilities[i].Modifier = (temp - 1) / 2;
		}

		m_Strength.Modifier     = abilities[0].Modifier;
		m_Dexterity.Modifier    = abilities[1].Modifier;
		m_Constitution.Modifier = abilities[2].Modifier;
		m_Intelligence.Modifier = abilities[3].Modifier;
		m_Wisdom.Modifier       = abilities[4].Modifier;
		m_Charisma.Modifier     = abilities[5].Modifier;
	}

	void Character::GenerateSkillProficiencies()
	{
		if (m_Class == "Barbarian")
			chooseSkillProficiencies(2, { m_AnimalHandling, m_Athletics, m_Intimidation, m_Nature, m_Perception, m_Survival });

		else if (m_Class == "Bard")
		{
			// Pick any three skills
			chooseSkillProficiencies(3, { m_Acrobatics, m_AnimalHandling, m_Arcana, m_Athletics, m_Deception, m_History, m_Insight,
				m_Intimidation, m_Investigation, m_Medicine, m_Nature, m_Perception, m_Performance, m_Persuasion, m_Religion,
				m_SleightOfHand, m_Stealth, m_Survival });
		}

		else if (m_Class == "Cleric")
			chooseSkillProficiencies(2, { m_History, m_Insight, m_Medicine, m_Persuasion, m_Religion });

		else if (m_Class == "Druid")
			chooseSkillProficiencies(2, { m_Arcana, m_AnimalHandling, m_Insight, m_Medicine, m_Nature, m_Perception, m_Religion, m_Survival });

		else if (m_Class == "Fighter")
			chooseSkillProficiencies(2, { m_Acrobatics, m_AnimalHandling, m_Athletics, m_History, m_Insight, m_Intimidation, m_Perception, m_Survival });

		else if (m_Class == "Monk")
			chooseSkillProficiencies(2, { m_Acrobatics, m_Athletics, m_History, m_Insight, m_Religion, m_Stealth });

		else if (m_Class == "Paladin")
			chooseSkillProficiencies(2, { m_Athletics, m_Insight, m_Intimidation, m_Medicine, m_Persuasion, m_Religion });

		else if (m_Class == "Ranger")
			chooseSkillProficiencies(3, { m_AnimalHandling, m_Athletics, m_Insight, m_Investigation, m_Nature, m_Perception, m_Stealth, m_Survival });

		else if (m_Class == "Rogue")
			chooseSkillProficiencies(4, { m_Acrobatics, m_Athletics, m_Deception, m_Insight, m_Intimidation, m_Investigation, m_Perception, m_Performance, m_Persuasion, m_SleightOfHand, m_Stealth });

		else if (m_Class == "Sorceror")
			chooseSkillProficiencies(2, { m_Arcana, m_Deception, m_Insight, m_Intimidation, m_Persuasion, m_Religion });

		else if (m_Class == "Warlock")
			chooseSkillProficiencies(2, { m_Arcana, m_Deception, m_History, m_Intimidation, m_Investigation, m_Nature, m_Religion });

		else if (m_Class == "Wizard")
			chooseSkillProficiencies(2, { m_Arcana, m_History, m_Insight, m_Investigation, m_Medicine, m_Religion });
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
				skills[i].get().Modifier += m_ProficiencyBonus;

			// Add other proficiencies
		}
	}

	void Character::GenerateSavingThrowProficiencies()
	{
		if (m_Class == "Barbarian" || m_Class == "Fighter" || m_Class == "Monk" || m_Class == "Ranger")
			m_StrengthSave.Proficient = true;

		if (m_Class == "Bard" || m_Class == "Monk" || m_Class == "Ranger" || m_Class == "Rogue")
			m_DexteritySave.Proficient = true;

		if (m_Class == "Barbarian" || m_Class == "Fighter" || m_Class == "Sorceror")
			m_ConstitutionSave.Proficient = true;

		if (m_Class == "Druid" || m_Class == "Rogue" || m_Class == "Wizard")
			m_IntelligenceSave.Proficient = true;

		if (m_Class == "Cleric" || m_Class == "Druid" || m_Class == "Paladin" || m_Class == "Warlock" || m_Class == "Wizard")
			m_WisdomSave.Proficient = true;

		if (m_Class == "Bard" || m_Class == "Cleric" || m_Class == "Paladin" || m_Class == "Sorceror" || m_Class == "Warlock")
			m_CharismaSave.Proficient = true;
	}

	void Character::GenerateSavingThrowModifiers()
	{
		m_StrengthSave.Parent = m_Strength;
		m_DexteritySave.Parent = m_Dexterity;
		m_ConstitutionSave.Parent = m_Constitution;
		m_IntelligenceSave.Parent = m_Intelligence;
		m_WisdomSave.Parent = m_Wisdom;
		m_CharismaSave.Parent = m_Charisma;

		std::vector<std::reference_wrapper<Skill>> saves = { m_StrengthSave, m_DexteritySave, m_ConstitutionSave, m_IntelligenceSave,m_WisdomSave, m_CharismaSave };

		// Start at parent ability's modifier
		for (size_t i = 0; i < saves.size(); ++i)
			saves[i].get().Modifier = saves[i].get().Parent.Modifier;

		// Add profiency bonus if proficient in saving throw
		for (size_t i = 0; i < saves.size(); ++i)
		{
			if (saves[i].get().Proficient)
				saves[i].get().Modifier += m_ProficiencyBonus;
		}
	}

	void Character::GeneratePassiveWisdom()
	{
		// Passive wisdom is wisdom modifier + 10 + proficiency bonus (if proficient in perception)
		m_PassiveWisdom = m_Wisdom.Modifier + 10;

		if (m_Perception.Proficient)
			m_PassiveWisdom += m_ProficiencyBonus;
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

		if (m_MajorRace == "Dwarf")
			m_Languages.push_back("Dwarvish");

		else if (m_MajorRace == "Elf")
		{
			m_Languages.push_back("Elvish");

			// High Elves have the Extra Language Trait
			if (m_Race == "High Elf")
				m_Languages.push_back(Languages[Random::Int(1, NumLanguages - 1)]); // 1 is the minimum number to avoid picking Elvish twice
		}

		else if (m_MajorRace == "Halfling")
			m_Languages.push_back("Halfling");

		// Humans can pick any language
		else if (m_Race == "Human")
			m_Languages.push_back(Languages[Random::Int(0, NumLanguages - 1)]);
	}


	// ======================================================================================
	// Equipment and Combat
	// ======================================================================================

	void Character::GenerateHitDice()
	{
		if (m_Class == "Barbarian")
			m_HitDice.Type = "d12";

		else if (m_Class == "Fighter" || m_Class == "Paladin" || m_Class == "Ranger")
			m_HitDice.Type = "d10";

		else if (m_Class == "Bard" || m_Class == "Cleric" || m_Class == "Druid" || m_Class == "Monk" || m_Class == "Rogue" || m_Class == "Warlock")
			m_HitDice.Type = "d8";

		else if (m_Class == "Sorceror" || m_Class == "Wizard")
			m_HitDice.Type = "d6";

		m_HitDice.Number = m_Level;
	}

	void Character::GenerateHitPoints()
	{
		// At level 1, characters start with the max roll of their hit die plus their constitution modifier
		if (m_Class == "Barbarian")
			m_MaxHitPoints = 12 + m_Constitution.Modifier;

		else if (m_Class == "Fighter" || m_Class == "Paladin" || m_Class == "Ranger")
			m_MaxHitPoints = 10 + m_Constitution.Modifier;

		else if (m_Class == "Bard" || m_Class == "Cleric" || m_Class == "Druid" || m_Class == "Monk" || m_Class == "Rogue" || m_Class == "Warlock")
			m_MaxHitPoints = 8 + m_Constitution.Modifier;

		else if (m_Class == "Sorcerer" || m_Class == "Wizard")
			m_MaxHitPoints = 6 + m_Constitution.Modifier;

		// Health increases with level based on a hit die roll and constitution modifier
		if (m_Level > 1)
		{
			if (m_Class == "Barbarian")
				m_MaxHitPoints += Random::Int(1, 12) + m_Constitution.Modifier;

			else if (m_Class == "Fighter" || m_Class == "Paladin" || m_Class == "Ranger")
				m_MaxHitPoints += Random::Int(1, 10) + m_Constitution.Modifier;

			else if (m_Class == "Bard" || m_Class == "Cleric" || m_Class == "Druid" || m_Class == "Monk" || m_Class == "Rogue" || m_Class == "Warlock")
				m_MaxHitPoints += Random::Int(1, 8) + m_Constitution.Modifier;

			else if (m_Class == "Sorcerer" || m_Class == "Wizard")
				m_MaxHitPoints += Random::Int(1, 6) + m_Constitution.Modifier;
		}

		// Add other modifiers
	}

	void Character::GenerateSpeed()
	{
		if (m_MajorRace == "Dwarf" || m_MajorRace == "Halfling")
			m_Speed = 25;
		else if (m_MajorRace == "Elf" || m_Race == "Human")
			m_Speed = 30;
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

		std::cout << "Name: "   << m_FirstName << " " << m_Surname << "\n";
		std::cout << "Gender: " << m_Gender    << "\n";
		std::cout << "Race: "   << m_Race      << "\n";

		if (m_Race == "Human")
			std::cout << "Ethnicity: " << m_Ethnicity << "\n";

		std::cout << "Class: "              << m_Class << "\n";
		std::cout << "Level: "              << m_Level << "\n";
		std::cout << "Experience Points: "  << m_Experience << "\n";
		std::cout << "Proficiency Bonus: "  << m_ProficiencyBonus << "\n";
		std::cout << "Hit Points: "         << m_MaxHitPoints << "\n";
		std::cout << "Speed: "              << m_Speed << "\n";
		std::cout << "Initiative: "         << m_Initiative << "\n";
		std::cout << "Background: "         << m_Background << "\n";
		std::cout << "Alignment: "          << m_Alignment << "\n\n";
		std::cout << "Personality Traits: " << m_PersonalityTraits << "\n\n";
		std::cout << "Ideals: "             << m_Ideals << "\n\n";
		std::cout << "Bonds: "              << m_Bonds << "\n\n";
		std::cout << "Flaws: "              << m_Flaws << "\n\n";

		std::cout << "Languages: ";
		for (size_t i = 0; i < m_Languages.size(); ++i)
		{
			std::cout << m_Languages[i];
			if (i != m_Languages.size() - 1)
				std::cout << ", ";

		}
		std::cout << "\n\n";

		std::cout << "========\n";
		std::cout << "Abilites\n";
		std::cout << "========\n";
		std::cout << "Strength\n";
		std::cout << "Score:    " << m_Strength.Score << "\n";
		std::cout << "Modifier: " << m_Strength.Modifier << "\n\n";
		std::cout << "Dexterity\n";
		std::cout << "Score:    " << m_Dexterity.Score << "\n";
		std::cout << "Modifier: " << m_Dexterity.Modifier << "\n\n";
		std::cout << "Constitution\n";
		std::cout << "Score:    " << m_Constitution.Score << "\n";
		std::cout << "Modifier: " << m_Constitution.Modifier << "\n\n";
		std::cout << "Intelligence\n";
		std::cout << "Score:    " << m_Intelligence.Score << "\n";
		std::cout << "Modifier: " << m_Intelligence.Modifier << "\n\n";
		std::cout << "Wisdom\n";
		std::cout << "Score:    " << m_Wisdom.Score << "\n";
		std::cout << "Modifier: " << m_Wisdom.Modifier << "\n\n";
		std::cout << "Charisma\n";
		std::cout << "Score:    " << m_Charisma.Score << "\n";
		std::cout << "Modifier: " << m_Charisma.Modifier << "\n\n";

		std::cout << "=============\n";
		std::cout << "Saving Throws\n";
		std::cout << "=============\n";
		std::cout << "Proficiencies\n";
		std::cout << "Strength:     " << m_StrengthSave.Proficient << "\n";
		std::cout << "Dexterity:    " << m_DexteritySave.Proficient << "\n";
		std::cout << "Constitution: " << m_ConstitutionSave.Proficient << "\n";
		std::cout << "Intelligence: " << m_IntelligenceSave.Proficient << "\n";
		std::cout << "Wisdom:       " << m_WisdomSave.Proficient << "\n";
		std::cout << "Charisma:     " << m_CharismaSave.Proficient << "\n\n";
		std::cout << "Modifiers\n";
		std::cout << "Strength:     " << m_StrengthSave.Modifier << "\n";
		std::cout << "Dexterity:    " << m_DexteritySave.Modifier << "\n";
		std::cout << "Constitution: " << m_Constitution.Modifier << "\n";
		std::cout << "Intelligence: " << m_IntelligenceSave.Modifier << "\n";
		std::cout << "Wisdom:       " << m_WisdomSave.Modifier << "\n";
		std::cout << "Charisma:     " << m_CharismaSave.Modifier << "\n\n";

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