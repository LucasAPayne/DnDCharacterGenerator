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
		m_Class = classes[Random::Int(0, NumClasses - 1)];
	}

	void Character::GenerateRace()
	{
		m_Race = races[Random::Int(0, NumRaces - 1)];

		// Humans also have ethnicity (for name)
		if (m_Race == "Human")
			m_Ethnicity = ethnicities[Random::Int(0, NumEthnicities - 1)];
	}

	void Character::GenerateBackground()
	{
		m_Background = backgrounds[Random::Int(0, NumBackgrounds - 1)];
	}

	void Character::GenerateAlignment()
	{
		m_Alignment = alignments[Random::Int(0, NumAlignments - 1)];
	}

	void Character::GenerateGender()
	{
		// Gender needed to generate random name
		if (m_Gender == "")
		{
			m_Gender = genders[Random::Int(0, NumGenders - 1)];
		}
	}

	void Character::GenerateFirstName()
	{
		if (m_Race.find("Dwarf") != std::string::npos)
		{
			if (m_Gender == "Male")
				m_FirstName = DwarfMaleNames[Random::Int(0, NumDwarfMaleNames - 1)];
			else if (m_Gender == "Female")
				m_FirstName = DwarfFemaleNames[Random::Int(0, NumDwarfFemaleNames - 1)];
		}
		else if (m_Race.find("Elf") != std::string::npos)
		{
			if (m_Gender == "Male")
				m_FirstName = ElfMaleNames[Random::Int(0, NumElfMaleNames - 1)];
			else if (m_Gender == "Female")
				m_FirstName = ElfFemaleNames[Random::Int(0, NumElfFemaleNames - 1)];
		}
		else if (m_Race.find("Halfling") != std::string::npos)
		{
			if (m_Gender == "Male")
				m_FirstName = HalflingMaleNames[Random::Int(0, NumHalflingMaleNames - 1)];
			else if (m_Gender == "Female")
				m_FirstName = HalflingFemaleNames[Random::Int(0, NumHalflingFemaleNames - 1)];
		}
		else if (m_Race == "Human")
		{
			if (m_Gender == "Male")
			{
				if (m_Ethnicity == "Calishite")
					m_FirstName = CalishiteMaleNames[Random::Int(0, NumCalishiteMaleNames - 1)];
				else if (m_Ethnicity == "Chondathan" || m_Ethnicity == "Tethyrian")
					m_FirstName = ChondathanTethyrianMaleNames[Random::Int(0, NumChondathanTethyrianMaleNames - 1)];
				else if (m_Ethnicity == "Damaran")
					m_FirstName = DamaranMaleNames[Random::Int(0, NumDamaranMaleNames - 1)];
				else if (m_Ethnicity == "Illuskan")
					m_FirstName = IlluskanMaleNames[Random::Int(0, NumIlluskanMaleNames - 1)];
				else if (m_Ethnicity == "Mulan")
					m_FirstName = MulanMaleNames[Random::Int(0, NumMulanMaleNames - 1)];
				else if (m_Ethnicity == "Rashemi")
					m_FirstName = RashemiMaleNames[Random::Int(0, NumRashemiMaleNames - 1)];
				else if (m_Ethnicity == "Shou")
					m_FirstName = ShouMaleNames[Random::Int(0, NumShouMaleNames - 1)];
				else if (m_Ethnicity == "Turami")
					m_FirstName = TuramiMaleNames[Random::Int(0, NumTuramiMaleNames - 1)];
			}
			else if (m_Gender == "Female")
			{
				if (m_Ethnicity == "Calishite")
					m_FirstName = CalishiteFemaleNames[Random::Int(0, NumCalishiteFemaleNames - 1)];
				else if (m_Ethnicity == "Chondathan" || m_Ethnicity == "Tethyrian")
					m_FirstName = ChondathanTethyrianFemaleNames[Random::Int(0, NumChondathanTethyrianFemaleNames - 1)];
				else if (m_Ethnicity == "Damaran")
					m_FirstName = DamaranFemaleNames[Random::Int(0, NumDamaranFemaleNames - 1)];
				else if (m_Ethnicity == "Illuskan")
					m_FirstName = IlluskanFemaleNames[Random::Int(0, NumIlluskanFemaleNames - 1)];
				else if (m_Ethnicity == "Mulan")
					m_FirstName = MulanFemaleNames[Random::Int(0, NumMulanFemaleNames - 1)];
				else if (m_Ethnicity == "Rashemi")
					m_FirstName = RashemiFemaleNames[Random::Int(0, NumRashemiFemaleNames - 1)];
				else if (m_Ethnicity == "Shou")
					m_FirstName = ShouFemaleNames[Random::Int(0, NumShouFemaleNames - 1)];
				else if (m_Ethnicity == "Turami")
					m_FirstName = TuramiFemaleNames[Random::Int(0, NumTuramiFemaleNames - 1)];
			}
		}
	}

	void Character::GenerateSurname()
	{
		// There are different types of non-humans but the major race is all that matters for picking a name
		if (m_Race.find("Dwarf") != std::string::npos)
			m_Surname = DwarfClanNames[Random::Int(0, NumDwarfClanNames - 1)];
		else if (m_Race.find("Elf") != std::string::npos)
			m_Surname = ElfFamilyNames[Random::Int(0, NumElfFamilyNames - 1)];
		else if (m_Race.find("Halfling") != std::string::npos)
			m_Surname = HalflingFamilyNames[Random::Int(0, NumHalflingFamilyNames - 1)];
		else if (m_Race == "Human")
		{
			if (m_Ethnicity == "Calishite")
				m_Surname = CalishiteSurnames[Random::Int(0, NumCalishiteSurnames - 1)];
			else if (m_Ethnicity == "Chondathan" || m_Ethnicity == "Tethyrian")
				m_Surname = ChondathanTethyrianSurnames[Random::Int(0, NumChondathanTethyrianSurnames - 1)];
			else if (m_Ethnicity == "Damaran")
				m_Surname = DamaranSurnames[Random::Int(0, NumDamaranSurnames - 1)];
			else if (m_Ethnicity == "Illuskan")
				m_Surname = IlluskanSurnames[Random::Int(0, NumIlluskanSurnames - 1)];
			else if (m_Ethnicity == "Mulan")
				m_Surname = MulanSurnames[Random::Int(0, NumMulanSurnames - 1)];
			else if (m_Ethnicity == "Rashemi")
				m_Surname = RashemiSurnames[Random::Int(0, NumRashemiSurnames - 1)];
			else if (m_Ethnicity == "Shou")
				m_Surname = ShouSurnames[Random::Int(0, NumShouSurnames - 1)];
			else if (m_Ethnicity == "Turami")
				m_Surname = TuramiSurnames[Random::Int(0, NumTuramiSurnames - 1)];
		}
	}

	void Character::GeneratePersonalityTraits()
	{
		// Generate two unique random numbers to ensure personality traits are different
		int first = Random::Int(0, NumPersonalityTraits - 1);
		int second = Random::Int(0, NumPersonalityTraits - 1);
		while (second == first)
			second = Random::Int(0, NumPersonalityTraits - 1);

		if (m_Background == "Acolyte")
			m_PersonalityTraits = AcolytePersonalityTraits[first] + " " + AcolytePersonalityTraits[second];
		else if (m_Background == "Charlatan")
			m_PersonalityTraits = CharlatanPersonalityTraits[first] + " " + CharlatanPersonalityTraits[second];
		else if (m_Background == "Criminal" || m_Background == "Spy")
			m_PersonalityTraits = CriminalSpyPersonalityTraits[first] + " " + CriminalSpyPersonalityTraits[second];
		else if (m_Background == "Entertainer" || m_Background == "Gladiator")
			m_PersonalityTraits = EntertainerGladiatorPersonalityTraits[first] + " " + EntertainerGladiatorPersonalityTraits[second];
		else if (m_Background == "Folk Hero")
			m_PersonalityTraits = FolkHeroPersonalityTraits[first] + " " + FolkHeroPersonalityTraits[second];
		else if (m_Background == "Guild Artisan" || m_Background == "Guild Merchant")
			m_PersonalityTraits = GuildArtisanMerchantPersonalityTraits[first] + " " + GuildArtisanMerchantPersonalityTraits[second];
		else if (m_Background == "Hermit")
			m_PersonalityTraits = HermitPersonalityTraits[first] + " " + HermitPersonalityTraits[second];
		else if (m_Background == "Noble" || m_Background == "Knight")
			m_PersonalityTraits = NobleKnightPersonalityTraits[first] + " " + NobleKnightPersonalityTraits[second];
		else if (m_Background == "Outlander")
			m_PersonalityTraits = OutlanderPersonalityTraits[first] + " " + OutlanderPersonalityTraits[second];
		else if (m_Background == "Sage")
			m_PersonalityTraits = SagePersonalityTraits[first] + " " + SagePersonalityTraits[second];
		else if (m_Background == "Sailor" || m_Background == "Pirate")
			m_PersonalityTraits = SailorPiratePersonalityTraits[first] + " " + SailorPiratePersonalityTraits[second];
		else if (m_Background == "Soldier")
			m_PersonalityTraits = SoldierPersonalityTraits[first] + " " + SoldierPersonalityTraits[second];
		else if (m_Background == "Urchin")
			m_PersonalityTraits = UrchinPersonalityTraits[first] + " " + UrchinPersonalityTraits[second];
	}

	void Character::GenerateIdeals()
	{
		std::string axis1 = m_Alignment.substr(0, m_Alignment.find(' ')); // Lawful, Neutral, or Chaotic
		std::string axis2 = m_Alignment.substr(m_Alignment.find(' ') + 1); // Good, Neutral, or Evil;

		std::array<std::pair<std::string, std::string>, NumIdeals> list;
		int index = Random::Int(0, NumIdeals - 1);

		bool success = false;
		while (!success)
		{
			if (m_Ideals != "")
				success = true;

			if (m_Background == "Acolyte")
				list = AcolyteIdeals;
			else if (m_Background == "Charlatan")
				list = CharlatanIdeals;
			else if (m_Background == "Criminal" || m_Background == "Spy")
				list = CriminalSpyIdeals;
			else if (m_Background == "Entertainer" || m_Background == "Gladiator")
				list = EntertainerGladiatorIdeals;
			else if (m_Background == "Folk Hero")
				list = FolkHeroIdeals;
			else if (m_Background == "Guild Artisan" || m_Background == "Guild Merchant")
				list = GuildArtisanMerchantIdeals;
			else if (m_Background == "Hermit")
				list = HermitIdeals;
			else if (m_Background == "Noble" || m_Background == "Knight")
				list = NobleKnightIdeals;
			else if (m_Background == "Outlander")
				list = OutlanderIdeals;
			else if (m_Background == "Sage")
				list = SageIdeals;
			else if (m_Background == "Sailor" || m_Background == "Pirate")
				list = SailorPirateIdeals;
			else if (m_Background == "Soldier")
				list = SoldierIdeals;
			else if (m_Background == "Urchin")
				list = UrchinIdeals;

			if (list[index].first == axis1 || list[index].first == axis2 || list[index].first == "Any")
				m_Ideals = list[index].second;
			else
				index = Random::Int(0, NumIdeals - 1);
		}
	}

	void Character::GenerateBonds()
	{
		int index = Random::Int(0, NumBonds - 1);

		if (m_Background == "Acolyte")
			m_Bonds = AcolyteBonds[index];
		else if (m_Background == "Charlatan")
			m_Bonds = CharlatanBonds[index];
		else if (m_Background == "Criminal" || m_Background == "Spy")
			m_Bonds = CriminalSpyBonds[index];
		else if (m_Background == "Entertainer" || m_Background == "Gladiator")
			m_Bonds = EntertainerGladiatorBonds[index];
		else if (m_Background == "Folk Hero")
			m_Bonds = FolkHeroBonds[index];
		else if (m_Background == "Guild Artisan" || m_Background == "Guild Merchant")
			m_Bonds = GuildArtisanMerchantBonds[index];
		else if (m_Background == "Hermit")
			m_Bonds = HermitBonds[index];
		else if (m_Background == "Noble" || m_Background == "Knight")
			m_Bonds = NobleKnightBonds[index];
		else if (m_Background == "Outlander")
			m_Bonds = OutlanderBonds[index];
		else if (m_Background == "Sage")
			m_Bonds = SageBonds[index];
		else if (m_Background == "Sailor" || m_Background == "Pirate")
			m_Bonds = SailorPirateBonds[index];
		else if (m_Background == "Soldier")
			m_Bonds = SoldierBonds[index];
		else if (m_Background == "Urchin")
			m_Bonds = UrchinBonds[index];
	}

	void Character::GenerateFlaws()
	{
		int index = Random::Int(0, NumFlaws - 1);

		if (m_Background == "Acolyte")
			m_Flaws = AcolyteFlaws[index];
		else if (m_Background == "Charlatan")
			m_Flaws = CharlatanFlaws[index];
		else if (m_Background == "Criminal" || m_Background == "Spy")
			m_Flaws = CriminalSpyFlaws[index];
		else if (m_Background == "Entertainer" || m_Background == "Gladiator")
			m_Flaws = EntertainerGladiatorFlaws[index];
		else if (m_Background == "Folk Hero")
			m_Flaws = FolkHeroFlaws[index];
		else if (m_Background == "Guild Artisan" || m_Background == "Guild Merchant")
			m_Flaws = GuildArtisanMerchantFlaws[index];
		else if (m_Background == "Hermit")
			m_Flaws = HermitFlaws[index];
		else if (m_Background == "Noble" || m_Background == "Knight")
			m_Flaws = NobleKnightFlaws[index];
		else if (m_Background == "Outlander")
			m_Flaws = OutlanderFlaws[index];
		else if (m_Background == "Sage")
			m_Flaws = SageFlaws[index];
		else if (m_Background == "Sailor" || m_Background == "Pirate")
			m_Flaws = SailorPirateFlaws[index];
		else if (m_Background == "Soldier")
			m_Flaws = SoldierFlaws[index];
		else if (m_Background == "Urchin")
			m_Flaws = UrchinFlaws[index];
	}

	// ======================================================================================
	// Skills, Abilities, and Level
	// ======================================================================================

	void Character::GenerateLevel()
	{
		m_Level = Random::Int(1, NumLevels - 1);
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
		m_Constitution.Score = totals[2];
		m_Intelligence.Score = totals[3];
		m_Wisdom.Score = totals[4];
		m_Charisma.Score = totals[5];
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
				m_Languages.push_back(languages[Random::Int(1, NumLanguages - 1)]);
			}
		}
		else if (m_Race == "Halfling" || m_Race == "Lightfoot Halfling" || m_Race == "Stout Halfling")
		{
			m_Languages.push_back("Halfling");
		}
		else if (m_Race == "Human")
		{
			// Humans can pick any language
			m_Languages.push_back(languages[Random::Int(0, NumLanguages - 1)]);
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