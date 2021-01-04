#include "DnDCharacter.h"
#include "Lists.h"
#include "Random.h"
#include "Types.h"

#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

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

	Character::Character()
	{
		// Add a proficiency or language that the character does not already have
		auto addUniqueProficiency = [this](std::vector<std::string>& characterList, const std::vector<std::string>& proficiencyList)
		{
			std::string proficiency = proficiencyList[Random::Int(0, proficiencyList.size() - 1)];

			// Make sure the character does not already have the proficiency
			while (std::find(characterList.begin(), characterList.end(), proficiency) != characterList.end())
				proficiency = proficiencyList[Random::Int(0, proficiencyList.size() - 1)];

			characterList.push_back(proficiency);
		};

		// Independent of race, background, and class
		{
			m_Alignment = Alignments[Random::Int(0, Alignments.size() - 1)];
			m_Gender = Genders[Random::Int(0, Genders.size() - 1)];

			m_Level = 1; // For now, characters should be locked to level 1 since any effects of leveling up are currently not considered
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
			m_Strength.Score = totals[0];
			m_Dexterity.Score = totals[1];
			m_Constitution.Score = totals[2];
			m_Intelligence.Score = totals[3];
			m_Wisdom.Score = totals[4];
			m_Charisma.Score = totals[5];

			// Ability score modifiers
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
			m_Strength.Modifier = abilities[0].Modifier;
			m_Dexterity.Modifier = abilities[1].Modifier;
			m_Constitution.Modifier = abilities[2].Modifier;
			m_Intelligence.Modifier = abilities[3].Modifier;
			m_Wisdom.Modifier = abilities[4].Modifier;
			m_Charisma.Modifier = abilities[5].Modifier;

			// Passive wisdom is wisdom modifier + 10 + proficiency bonus (if proficient in perception)
			m_PassiveWisdom = m_Wisdom.Modifier + 10;
			if (m_Perception.Proficient)
				m_PassiveWisdom += m_ProficiencyBonus;

			m_Initiative = m_Dexterity.Modifier;
			// TODO: Add other modifiers
		}

		// Race
		{
			m_Race = Races[Random::Int(0, Races.size() - 1)];

			// Humans also have ethnicity (for name)
			if (m_Race == "Human")
				m_Ethnicity = Ethnicities[Random::Int(0, Ethnicities.size() - 1)];

			// Find the character's major race
			if (m_Race == "Dwarf" || m_Race == "Elf" || m_Race == "Halfling" || m_Race == "Human")
				m_MajorRace = m_Race;
			else if (m_Race == "Mountain Dwarf" || m_Race == "Hill Dwarf")
				m_MajorRace = "Dwarf";
			else if (m_Race == "High Elf" || m_Race == "Wood Elf" || m_Race == "Dark Elf (Drow)")
				m_MajorRace = "Elf";
			else if (m_Race == "Lightfoot Halfling" || m_Race == "Stout Halfling")
				m_MajorRace = "Halfling";

			// Generate name
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

			// All characters can speak, read, and write in the Common tongue
			m_Languages.push_back("Common"); 

			// Ability score increases, feats, proficiencies, languages
			// Subraces also get parent race benefits
			if (m_MajorRace == "Dwarf")
			{
				m_Speed = 25;
				m_Constitution.Score += 2;
				m_Languages.push_back("Dwarvish");
				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), RacialFeats.at("Dwarf").begin(), RacialFeats.at("Dwarf").end());

				// All dwarves get set weapon proficiencies and can choose one set of tools to be proficient with
				std::vector<std::string> choices = { "smith's tools", "brewer's supplies", "mason's tools" };
				m_ToolProficiencies.push_back(choices[Random::Int(0, choices.size() - 1)]);
				m_WeaponProficiencies.insert(m_WeaponProficiencies.end(), { "battleaxe", "handaxe", "throwing hammer", "warhammer" });

				if (m_Race == "Hill Dwarf")
				{
					m_Wisdom.Score++;
					m_MaxHitPoints += m_Level; // From the Dwarven Toughness feat
					m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), RacialFeats.at("Hill Dwarf").begin(), RacialFeats.at("Hill Dwarf").end());
				}

				else if (m_Race == "Mountain Dwarf")
				{
					m_Strength.Score += 2;
					m_ArmorProficiencies.insert(m_ArmorProficiencies.end(), { "light armor", "medium armor" });
				}
			}
			else if (m_MajorRace == "Elf")
			{
				m_Speed = 30;
				m_Dexterity.Score += 2;
				m_Perception.Proficient = true;
				m_Languages.push_back("Elvish");
				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), RacialFeats.at("Elf").begin(), RacialFeats.at("Elf").end());

				if (m_Race == "High Elf")
				{
					// TODO: High elves get a cantrip from the wizard spell list

					m_Intelligence.Score++;
					m_WeaponProficiencies.insert(m_WeaponProficiencies.end(), { "longsword", "shortsword", "shortbow", "longbow" });

					// Choose one additional language
					m_Languages.push_back(Languages[Random::Int(1, Languages.size() - 1)]); // 1 is the minimum number to avoid picking Elvish twice
				}
				else if (m_Race == "Wood Elf")
				{
					m_Speed = 35;
					m_Wisdom.Score++;

					m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), RacialFeats.at("Wood Elf").begin(), RacialFeats.at("Wood Elf").end());
					m_WeaponProficiencies.insert(m_WeaponProficiencies.end(), { "longsword", "shortsword", "shortbow", "longbow" });
				}
				else if (m_Race == "Dark Elf (Drow)")
				{ 
					m_Charisma.Score++;
					m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), RacialFeats.at("Dark Elf (Drow)").begin(), RacialFeats.at("Dark Elf (Drow)").end());
					m_WeaponProficiencies.insert(m_WeaponProficiencies.end(), { "rapiers", "shortswords", "hand crossbows" });
				}
			}
			else if (m_MajorRace == "Halfling")
			{
				m_Speed = 25;
				m_Dexterity.Score += 2;
				m_Languages.push_back("Halfling");
				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), RacialFeats.at("Halfling").begin(), RacialFeats.at("Halfling").end());

				if (m_Race == "Lightfoot Halfling")
				{
					m_Charisma.Score++;
					m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), RacialFeats.at("Lightfoot Halfling").begin(), RacialFeats.at("Lightfoot Halfling").end());
				}
				else if (m_Race == "Stout Halfling")
				{
					m_Constitution.Score++;
					m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), RacialFeats.at("Stout Halfling").begin(), RacialFeats.at("Stout Halfling").end());
				}
			}
			else if (m_Race == "Human")
			{
				m_Speed = 30;
				m_Strength.Score++;
				m_Dexterity.Score++;
				m_Constitution.Score++;
				m_Intelligence.Score++;
				m_Wisdom.Score++;
				m_Charisma.Score++;

				m_Languages.push_back(Languages[Random::Int(0, Languages.size() - 1)]);
				// TODO: Add optional variant human trait
			}
		}

		// Background
		{
			m_Background = Backgrounds[Random::Int(0, Backgrounds.size() - 1)];

			// Personality Traits
			// Generate two unique random numbers to ensure personality traits are different
			std::vector<std::string> personalityList = PersonalityTraits.at(m_Background);
			int first = Random::Int(0, personalityList.size() - 1);
			int second = Random::Int(0, personalityList.size() - 1);

			// Ensure two unique traits are chosen
			while (second == first)
				second = Random::Int(0, personalityList.size() - 1);

			m_PersonalityTraits = personalityList[first] + " " + personalityList[second];

			// Ideals
			std::string axis1 = m_Alignment.substr(0, m_Alignment.find(' ')); // Lawful, Neutral, or Chaotic
			std::string axis2 = m_Alignment.substr(m_Alignment.find(' ') + 1); // Good, Neutral, or Evil;
			auto& idealsList = Ideals.at(m_Background);

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

			// Background feats
			// Some backgrounds offer variant feats, but a character may only choose one feat from a background.
			int index = Random::Int(0, BackgroundFeats.at(m_Background).size() - 1);
			m_FeatsAndTraits.push_back(BackgroundFeats.at(m_Background)[index]);

			// Proficiencies
			if (m_Background == "Acolyte")
			{
				m_Insight.Proficient = true;
				m_Religion.Proficient = true;

				// Choose two additional languages
				for (int i = 0; i < 2; i++)
					addUniqueProficiency(m_Languages, Languages);
			}
			else if (m_Background == "Charlatan")
			{
				m_Deception.Proficient = true;
				m_SleightOfHand.Proficient = true;

				m_ToolProficiencies.insert(m_ToolProficiencies.end(), { "disguise kit", "forgery kit" });
			}
			else if (m_Background == "Criminal" || m_Background == "Spy")
			{
				m_Deception.Proficient = true;
				m_Stealth.Proficient = true;

				// Choose one gaming set to be proficient with
				m_ToolProficiencies.push_back(GamingSets[Random::Int(0, GamingSets.size() - 1)]);
				m_ToolProficiencies.push_back("thieves' tools");
			}
			else if (m_Background == "Entertainer" || m_Background == "Gladiator")
			{
				m_Acrobatics.Proficient = true;
				m_Performance.Proficient = true;

				// Choose one musical instrument to be proficient with
				m_ToolProficiencies.push_back(MusicalInstruments[Random::Int(0, MusicalInstruments.size() - 1)]);
				m_ToolProficiencies.push_back("disguise kit");
			}
			else if (m_Background == "Folk Hero")
			{
				m_AnimalHandling.Proficient = true;
				m_Survival.Proficient = true;

				// Choose one type of artisan's tools to be proficient with
				m_ToolProficiencies.push_back(ArtisanTools[Random::Int(0, ArtisanTools.size() - 1)]);
				m_ToolProficiencies.push_back("vehicles (land)");
			}
			else if (m_Background == "Guild Artisan" || m_Background == "Guild Merchant")
			{
				m_Insight.Proficient = true;
				m_Persuasion.Proficient = true;
				
				// Choose one type of artisan's tools to be proficient with
				m_ToolProficiencies.push_back(ArtisanTools[Random::Int(0, ArtisanTools.size() - 1)]);
				
				// Choose one additional language
				addUniqueProficiency(m_Languages, Languages);
			}
			else if (m_Background == "Hermit")
			{
				m_Medicine.Proficient = true;
				m_Religion.Proficient = true;

				m_ToolProficiencies.push_back("herbalism kit");

				// Choose one additional language
				addUniqueProficiency(m_Languages, Languages);
			}
			else if (m_Background == "Noble" || m_Background == "Knight")
			{
				m_History.Proficient = true;
				m_Persuasion.Proficient = true;

				// Choose one gaming set to be proficient with
				m_ToolProficiencies.push_back(GamingSets[Random::Int(0, GamingSets.size() - 1)]);

				// Choose one additional language
				addUniqueProficiency(m_Languages, Languages);
			}
			else if (m_Background == "Outlander")
			{
				m_Athletics.Proficient = true;
				m_Survival.Proficient = true;

				// Choose one musical instrument to be proficient with
				m_ToolProficiencies.push_back(MusicalInstruments[Random::Int(0, MusicalInstruments.size() - 1)]);

				// Choose one additional language
				addUniqueProficiency(m_Languages, Languages);
			}
			else if (m_Background == "Sage")
			{
				m_Arcana.Proficient = true;
				m_History.Proficient = true;

				// Choose two additional languages
				for (int i = 0; i < 2; i++)
					addUniqueProficiency(m_Languages, Languages);
			}
			else if (m_Background == "Sailor" || m_Background == "Pirate")
			{
				m_Athletics.Proficient = true;
				m_Perception.Proficient = true;

				m_ToolProficiencies.insert(m_ToolProficiencies.end(), { "navigator's tools", "vehicles (water)" });
			}
			else if (m_Background == "Soldier")
			{
				m_Athletics.Proficient = true;
				m_Intimidation.Proficient = true;

				// Choose one gaming set to be proficient with
				m_ToolProficiencies.push_back(GamingSets[Random::Int(0, GamingSets.size() - 1)]);
				m_ToolProficiencies.push_back("vehicles (land)");
			}
			else if (m_Background == "Urchin")
			{
				m_SleightOfHand.Proficient = true;
				m_Stealth.Proficient = true;

				m_ToolProficiencies.insert(m_ToolProficiencies.end(), { "disguise kit", "thieves' tools" });
			}
		}

		// Class
		{
			m_Class = Classes[Random::Int(0, Classes.size() - 1)];

			// Choose a number of skill proficiencies randomly from a given list
			auto chooseSkillProficiencies = [](int skillsToChoose, std::vector<std::reference_wrapper<Skill>> list)
			{
				// Since this uses std::reference_wrapper, when the values in list change, the values in character change also 

				// Randomize the order of entries and pick the first x of them
				std::shuffle(list.begin(), list.end(), Random::GetEngine());

				for (int i = 0; i < skillsToChoose; ++i)
					list[i].get().Proficient = true;
			};

			// Hit dice/points, proficiencies, saving throw proficiencies, skill proficiencies
			if (m_Class == "Barbarian")
			{
				m_HitDice.Type = 12;
				m_ArmorProficiencies.insert(m_ArmorProficiencies.end(), { "light armor", "medium armor", "shields" });
				m_WeaponProficiencies.insert(m_WeaponProficiencies.end(), { "simple weapons", "martial weapons" });
				m_StrengthSave.Proficient = true;
				m_ConstitutionSave.Proficient = true;
				chooseSkillProficiencies(2, { m_AnimalHandling, m_Athletics, m_Intimidation, m_Nature, m_Perception, m_Survival });
				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), ClassFeats.at("Barbarian").begin(), ClassFeats.at("Barbarian").end());
			}
			else if (m_Class == "Bard")
			{
				m_HitDice.Type = 8;

				// Pick three musical instruments to be proficient with
				for (int i = 0; i < 3; i++)
				{
					std::string instrument = MusicalInstruments[Random::Int(0, MusicalInstruments.size() - 1)];

					// Make sure the character is not already proficient with the instrument
					while (std::find(m_ToolProficiencies.begin(), m_ToolProficiencies.end(), instrument) != m_ToolProficiencies.end())
						instrument = MusicalInstruments[Random::Int(0, MusicalInstruments.size() - 1)];

					m_Languages.push_back(instrument);
				}

				m_ArmorProficiencies.push_back("light armor");
				m_WeaponProficiencies.insert(m_WeaponProficiencies.end(), { "simple weapons", "hand crossbows", "longswords", "rapiers", "shortswords" });

				m_DexteritySave.Proficient = true;
				m_CharismaSave.Proficient = true;

				// Pick any three skills to be proficient in
				chooseSkillProficiencies(3, { m_Acrobatics, m_AnimalHandling, m_Arcana, m_Athletics, m_Deception, m_History, m_Insight,
					m_Intimidation, m_Investigation, m_Medicine, m_Nature, m_Perception, m_Performance, m_Persuasion, m_Religion,
					m_SleightOfHand, m_Stealth, m_Survival });

				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), ClassFeats.at("Bard").begin(), ClassFeats.at("Bard").end());
			}
			else if (m_Class == "Cleric")
			{
				m_HitDice.Type = 8;
				m_ArmorProficiencies.insert(m_ArmorProficiencies.end(), { "light armor", "medium armor", "shields" });
				m_WeaponProficiencies.push_back("simple weapons");
				m_WisdomSave.Proficient = true;
				m_CharismaSave.Proficient = true;
				chooseSkillProficiencies(2, { m_History, m_Insight, m_Medicine, m_Persuasion, m_Religion });

				// Clerics have a set trait at index 0
				m_FeatsAndTraits.push_back(ClassFeats.at(m_Class)[0]);

				// Pick a cleric domain, one of the 1st level traits after index 0
				int index = Random::Int(1, ClassFeats.at(m_Class).size() - 1);
				m_FeatsAndTraits.push_back(ClassFeats.at(m_Class)[index]);
			}
			else if (m_Class == "Druid")
			{
				m_HitDice.Type = 8;
				m_Languages.push_back("Druidic"); // From Druidic class feat
				m_ArmorProficiencies.insert(m_ArmorProficiencies.end(), { "light armor", "medium armor", "shields (druids will not wear armor or use shields made of metal)" });
				m_WeaponProficiencies.insert(m_WeaponProficiencies.end(), {"clubs", "daggers", "darts", "javelins", "maces", "quarterstaffs", "scimitars", "sickles", "slings", "spears" });
				m_ToolProficiencies.push_back("herbalism kit");
				m_IntelligenceSave.Proficient = true;
				m_WisdomSave.Proficient = true;
				chooseSkillProficiencies(2, { m_Arcana, m_AnimalHandling, m_Insight, m_Medicine, m_Nature, m_Perception, m_Religion, m_Survival });
				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), ClassFeats.at("Druid").begin(), ClassFeats.at("Druid").end());
			}
			else if (m_Class == "Fighter")
			{
				m_HitDice.Type = 10;
				m_ArmorProficiencies.insert(m_ArmorProficiencies.end(), { "light armor", "medium armor", "heavy armor", "shields" });
				m_WeaponProficiencies.insert(m_WeaponProficiencies.end(), { "simple weapons", "martial weapons" });
				m_StrengthSave.Proficient = true;
				m_ConstitutionSave.Proficient = true;
				chooseSkillProficiencies(2, { m_Acrobatics, m_AnimalHandling, m_Athletics, m_History, m_Insight, m_Intimidation, m_Perception, m_Survival });

				// Fighters have a set trait at index 0
				m_FeatsAndTraits.push_back(ClassFeats.at(m_Class)[0]);

				// Pick a fighting style, one of the 1st level traits after index 0
				int index = Random::Int(1, ClassFeats.at(m_Class).size() - 1);
				m_FeatsAndTraits.push_back(ClassFeats.at(m_Class)[index]);
			}
			else if (m_Class == "Monk")
			{
				m_HitDice.Type = 8;

				m_WeaponProficiencies.insert(m_WeaponProficiencies.end(), { "simple weapons", "shortswords" });
				// Choose one type of artisan's tools or musical instrument
				if (Random::Int(0, 1) == 0)
					m_ToolProficiencies.push_back(ArtisanTools[Random::Int(0, ArtisanTools.size() - 1)]);
				else
					m_ToolProficiencies.push_back(MusicalInstruments[Random::Int(0, MusicalInstruments.size() - 1)]);

				m_StrengthSave.Proficient = true;
				m_DexteritySave.Proficient = true;
				chooseSkillProficiencies(2, { m_Acrobatics, m_Athletics, m_History, m_Insight, m_Religion, m_Stealth }); \
					m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), ClassFeats.at("Monk").begin(), ClassFeats.at("Monk").end());
			}
			else if (m_Class == "Paladin")
			{
				m_HitDice.Type = 10;
				m_ArmorProficiencies.insert(m_ArmorProficiencies.end(), { "light armor", "medium armor", "heavy armor", "shields" });
				m_WeaponProficiencies.insert(m_WeaponProficiencies.end(), { "simple weapons", "martial weapons" });
				m_WisdomSave.Proficient = true;
				m_CharismaSave.Proficient = true;
				chooseSkillProficiencies(2, { m_Athletics, m_Insight, m_Intimidation, m_Medicine, m_Persuasion, m_Religion });
				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), ClassFeats.at("Paladin").begin(), ClassFeats.at("Paladin").end());
			}
			else if (m_Class == "Ranger")
			{
				m_HitDice.Type = 10;
				m_ArmorProficiencies.insert(m_ArmorProficiencies.end(), { "light armor", "medium armor", "shields" });
				m_WeaponProficiencies.insert(m_WeaponProficiencies.end(), { "simple weapons", "martial weapons" });
				m_StrengthSave.Proficient = true;
				m_DexteritySave.Proficient = true;
				chooseSkillProficiencies(3, { m_AnimalHandling, m_Athletics, m_Insight, m_Investigation, m_Nature, m_Perception, m_Stealth, m_Survival });
				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), ClassFeats.at("Ranger").begin(), ClassFeats.at("Ranger").end());
				// TODO: Some classes have choices within the set traits, such as Favored Enemy for Rangers
			}
			else if (m_Class == "Rogue")
			{
				m_HitDice.Type = 8;
				m_Languages.push_back("Thieves' Cant"); // From Thieves' Cant class feat
				m_ArmorProficiencies.push_back("light armor");
				m_WeaponProficiencies.insert(m_WeaponProficiencies.end(), { "simple weapons", "hand crossbows", "longswords", "rapiers", "shortswords" });
				m_ToolProficiencies.push_back("thieves' tools");
				m_DexteritySave.Proficient = true;
				m_IntelligenceSave.Proficient = true;
				chooseSkillProficiencies(4, { m_Acrobatics, m_Athletics, m_Deception, m_Insight, m_Intimidation, m_Investigation, m_Perception, m_Performance, m_Persuasion, m_SleightOfHand, m_Stealth });
				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), ClassFeats.at("Rogue").begin(), ClassFeats.at("Rogue").end());
			}
			else if (m_Class == "Sorcerer")
			{
				m_HitDice.Type = 6;
				m_WeaponProficiencies.insert(m_WeaponProficiencies.end(), { "daggers", "darts", "quarterstaffs", "light crossbows" });
				m_ConstitutionSave.Proficient = true;
				m_CharismaSave.Proficient = true;
				chooseSkillProficiencies(2, { m_Arcana, m_Deception, m_Insight, m_Intimidation, m_Persuasion, m_Religion });
				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), ClassFeats.at("Sorcerer").begin(), ClassFeats.at("Sorcerer").end());
			}
			else if (m_Class == "Warlock")
			{
				m_HitDice.Type = 8;
				m_ArmorProficiencies.push_back("light armor");
				m_WeaponProficiencies.push_back("simple weapons");
				m_WisdomSave.Proficient = true;
				m_CharismaSave.Proficient = true;
				chooseSkillProficiencies(2, { m_Arcana, m_Deception, m_History, m_Intimidation, m_Investigation, m_Nature, m_Religion });
				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), ClassFeats.at("Warlock").begin(), ClassFeats.at("Warlock").end());
			}
			else if (m_Class == "Wizard")
			{
				m_HitDice.Type = 6;
				m_WeaponProficiencies.insert(m_WeaponProficiencies.end(), { "daggers", "darts", "slings", "quarterstaffs", "light crossbows" });
				m_IntelligenceSave.Proficient = true;
				m_WisdomSave.Proficient = true;
				chooseSkillProficiencies(2, { m_Arcana, m_History, m_Insight, m_Investigation, m_Medicine, m_Religion });
				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), ClassFeats.at("Wizard").begin(), ClassFeats.at("Wizard").end());
			}
		}

		// Independent of race, class, and background, but need to be processed after
		{
			// Find duplicate values in a vector of strings and output the element and frequency to a map
			auto findDuplicates = [](const std::vector<std::string>& vec, std::map<std::string, int>& map)
			{
				for (const auto& it : vec)
				{
					auto result = map.insert(std::pair<std::string, int>(it, 1));
					// If the string already exists in the map, increment its count by 1
					if (result.second == false)
						result.first->second++;
				}
			};

			// Keep track of how many times the character is proficient in each of its proficiencies
			std::map<std::string, int> proficiencyCount;

			findDuplicates(m_ArmorProficiencies, proficiencyCount);
			for (const auto& it : proficiencyCount)
			{
				if (it.second > 1)
				{
					m_ArmorProficiencies.erase(find(m_ArmorProficiencies.begin(), m_ArmorProficiencies.end(), it.first));
					addUniqueProficiency(m_ArmorProficiencies, ArmorTypes);
				}
			}
			proficiencyCount.clear();

			findDuplicates(m_WeaponProficiencies, proficiencyCount);
			for (const auto& it : proficiencyCount)
			{
				if (it.second > 1)
				{
					m_WeaponProficiencies.erase(find(m_WeaponProficiencies.begin(), m_WeaponProficiencies.end(), it.first));
					addUniqueProficiency(m_WeaponProficiencies, WeaponTypes);
				}
			}
			proficiencyCount.clear();

			findDuplicates(m_ToolProficiencies, proficiencyCount);
			for (const auto& it : proficiencyCount)
			{
				if (it.second > 1)
				{
					std::vector<std::string> toolTypes;
					int choice = Random::Int(0, 3);
					if (choice == 0)
						toolTypes = ArtisanTools;
					else if (choice == 1)
						toolTypes = GamingSets;
					else if (choice == 2)
						toolTypes = MusicalInstruments;
					else if (choice == 3)
						toolTypes = OtherTools;

					m_ToolProficiencies.erase(find(m_ToolProficiencies.begin(), m_ToolProficiencies.end(), it.first));
					addUniqueProficiency(m_ArmorProficiencies, toolTypes);
				}
			}

			// Hit dice/points
			m_HitDice.Number = m_Level;
			m_MaxHitPoints = m_HitDice.Type + m_Constitution.Modifier;

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

				// TODO: Add other proficiencies
			}

			// Saving throw modifiers
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

		std::cout << "Passive Wisdom (Perception): " << m_PassiveWisdom << "\n\n";

		std::cout << "===========================\n";
		std::cout << "Proficiencies and Languages\n";
		std::cout << "===========================\n";
		std::cout << "Proficiencies: ";
		for (size_t i = 0; i < m_ArmorProficiencies.size(); i++)
			std::cout << m_ArmorProficiencies[i] << ", ";

		for (size_t i = 0; i < m_WeaponProficiencies.size(); i++)
			std::cout << m_WeaponProficiencies[i] << ", ";

		for (size_t i = 0; i < m_ToolProficiencies.size(); i++)
		{ 
			std::cout << m_ToolProficiencies[i];
			if (i != m_ToolProficiencies.size() - 1)
				std::cout << ", ";
		}
		std::cout << "\n\n";

		std::cout << "Languages: ";
		for (size_t i = 0; i < m_Languages.size(); ++i)
		{
			std::cout << m_Languages[i];
			if (i != m_Languages.size() - 1)
				std::cout << ", ";

		}
		std::cout << "\n\n";

		std::cout << "===================\n";
		std::cout << "Features and Traits\n";
		std::cout << "===================\n";
		for (size_t i = 0; i < m_FeatsAndTraits.size(); i++)
			std::cout << m_FeatsAndTraits[i].Name + " " + m_FeatsAndTraits[i].Description + "\n\n";
	}
}
