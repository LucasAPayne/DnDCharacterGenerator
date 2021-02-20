#include "DnDCharacter.h"
#include "Lists.h"
#include "Random.h"
#include "Types.h"

#include <algorithm>
#include <set>
#include <string>
#include <unordered_map>
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
		trait = list[Random::Index(0, list.size() - 1)];
	}

	auto foundException = [](const std::string& str, const std::vector<std::string>& exceptionList) -> bool
	{
		for (size_t i = 0; i < exceptionList.size(); i++)
		{
			if (str.find(exceptionList[i]) != std::string::npos)
				return true;
		}
		return false;
	};

	Character::Character()
	{
		// Add a proficiency or language that the character does not already have
		auto addUniqueProficiency = [](std::set<std::string>& characterList, const std::vector<std::string>& proficiencyList)
		{
			std::string proficiency = proficiencyList[Random::Index(0, proficiencyList.size() - 1)];

			while (characterList.insert(proficiency).second == false)
				proficiency = proficiencyList[Random::Index(0, proficiencyList.size() - 1)];
		};

		// Add a list of equipment to the character. If the character already has at least one of a type of equipment, just add the number to that.
		auto addEquipment = [this](const std::unordered_map<std::string, int>& equipment)
		{
			for (const auto& it : equipment)
			{
				if (!m_Equipment.contains(it.first))
					m_Equipment.insert(it);
				else
					m_Equipment.at(it.first) += it.second;
			}
		};

		// Choose a number of skill proficiencies randomly from a given list
		auto chooseSkillProficiencies = [](int skillsToChoose, std::vector<std::reference_wrapper<Skill>> list)
		{
			// Since this uses std::reference_wrapper, when the values in list change, the values in character change also 

			// Randomize the order of entries and pick the first x of them
			std::shuffle(list.begin(), list.end(), Random::GetEngine());

			for (int i = 0; i < skillsToChoose; ++i)
			{
				if (!list[i].get().Proficient)
					list[i].get().Proficient = true;
				else
				{
					// If the character is already proficient in the skill, increase skillsToChoose to skip that one and look at another
					if (skillsToChoose != list.size())
						skillsToChoose++;
				}
			}
		};

		// A character may choose to start with either equipment or money to buy equipment.
		// For now, this will be chosen randomly.
		bool startWithEquipment = Random::Int(0, 1); // true for equipment and false for money

		// Independent of race, background, and class
		{
			m_Alignment = Alignments[Random::Index(0, Alignments.size() - 1)];
			m_Gender = Genders[Random::Index(0, Genders.size() - 1)];

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
		}

		// Race
		{
			m_Race = Races[Random::Index(0, Races.size() - 1)];

			// Humans also have ethnicity (for name)
			if (m_Race == "Human" || m_Race == "Half-Elf" || m_Race == "Half-Orc")
				m_Ethnicity = Ethnicities[Random::Index(0, Ethnicities.size() - 1)];

			// Find the character's major race
			if (m_Race == "Mountain Dwarf" || m_Race == "Hill Dwarf")
				m_MajorRace = "Dwarf";
			else if (m_Race == "High Elf" || m_Race == "Wood Elf" || m_Race == "Dark Elf (Drow)")
				m_MajorRace = "Elf";
			else if (m_Race == "Lightfoot Halfling" || m_Race == "Stout Halfling")
				m_MajorRace = "Halfling";
			else if (m_Race == "Forest Gnome" || m_Race == "Rock Gnome")
				m_MajorRace = "Gnome";
			else
				m_MajorRace = m_Race;

			// Generate name
			if (m_Race == "Human")
			{
				if (m_Gender == "Male")
					SetTraitFromDict(m_FirstName, HumanMaleNames, m_Ethnicity);
				else if (m_Gender == "Female")
					SetTraitFromDict(m_FirstName, HumanFemaleNames, m_Ethnicity);

				SetTraitFromDict(m_Surname, HumanSurnames, m_Ethnicity);
			}
			else if (m_Race == "Half-Elf")
			{
				// Half-elves can use either the elven or human naming conventions
				bool elfName = Random::Int(0, 1);
				if (elfName)
				{
					if (m_Gender == "Male")
						SetTraitFromDict(m_FirstName, NonHumanMaleNames, "Elf");
					else if (m_Gender == "Female")
						SetTraitFromDict(m_FirstName, NonHumanFemaleNames, "Elf");

					SetTraitFromDict(m_Surname, NonHumanSurnames, "Elf");
				}
				else
				{
					if (m_Gender == "Male")
						SetTraitFromDict(m_FirstName, HumanMaleNames, m_Ethnicity);
					else if (m_Gender == "Female")
						SetTraitFromDict(m_FirstName, HumanFemaleNames, m_Ethnicity);

					SetTraitFromDict(m_Surname, HumanSurnames, m_Ethnicity);
				}
			}
			else if (m_Race == "Half-Orc")
			{
				// Half-orcs can choose orc names with no surname, or they can choose a human name
				bool orcName = Random::Int(0, 1);
				if (orcName)
				{
					if (m_Gender == "Male")
						SetTraitFromDict(m_FirstName, NonHumanMaleNames, "Half-Orc");
					else if (m_Gender == "Female")
						SetTraitFromDict(m_FirstName, NonHumanFemaleNames, "Half-Orc");
				}
				else
				{
					if (m_Gender == "Male")
						SetTraitFromDict(m_FirstName, HumanMaleNames, m_Ethnicity);
					else if (m_Gender == "Female")
						SetTraitFromDict(m_FirstName, HumanFemaleNames, m_Ethnicity);

					SetTraitFromDict(m_Surname, HumanSurnames, m_Ethnicity);
				}
			}
			else if (m_Race == "Tiefling")
			{
				// Tieflings can choose to use a name that signifies a virtue, one derived from the Infernal language, or one from whatever culture they were raised in, human or nonhuman
				int nameType = Random::Int(0, 3);
				if (nameType == 0) // Virtue Name
				{
					m_FirstName = VirtueNames[Random::Index(0, VirtueNames.size() - 1)];
				}
				else if (nameType == 1) // Infernal name
				{
					if (m_Gender == "Male")
						SetTraitFromDict(m_FirstName, NonHumanMaleNames, "Tiefling");
					else if (m_Gender == "Female")
						SetTraitFromDict(m_FirstName, NonHumanFemaleNames, "Tiefling");
				}
				else if (nameType == 2) // Human name
				{
					m_Ethnicity = Ethnicities[Random::Index(0, Ethnicities.size() - 1)];

					if (m_Gender == "Male")
						SetTraitFromDict(m_FirstName, HumanMaleNames, m_Ethnicity);
					else if (m_Gender == "Female")
						SetTraitFromDict(m_FirstName, HumanFemaleNames, m_Ethnicity);

					SetTraitFromDict(m_Surname, HumanSurnames, m_Ethnicity);
				}
				else if (nameType == 3) // Non-human name
				{
					std::vector<std::string> cultures = {"Dwarf", "Elf", "Halfling", "Dragonborn", "Gnome", "Half-Orc"};
					std::string culture = cultures[Random::Index(0, cultures.size() - 1)];

					if (m_Gender == "Male")
						SetTraitFromDict(m_FirstName, NonHumanMaleNames, culture);
					else if (m_Gender == "Female")
						SetTraitFromDict(m_FirstName, NonHumanFemaleNames, culture);

					// Some races do not have surnames
					if (NonHumanSurnames.contains(culture))
						SetTraitFromDict(m_Surname, NonHumanSurnames, culture);
				}
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
			m_Languages.insert("Common");

			// Most races get racial features, and most subraces get additional features
			if (RacialFeats.count(m_MajorRace) > 0)
				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), RacialFeats.at(m_MajorRace).begin(), RacialFeats.at(m_MajorRace).end());
			if (m_MajorRace != m_Race && RacialFeats.count(m_Race) > 0)
				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), RacialFeats.at(m_Race).begin(), RacialFeats.at(m_Race).end());

			// Ability score increases, feats, proficiencies, languages
			// Subraces also get parent race benefits
			if (m_MajorRace == "Dwarf")
			{
				m_Speed = 25;
				m_Constitution.Score += 2;
				m_Languages.insert("Dwarvish");

				// All dwarves get set weapon proficiencies and can choose one set of tools to be proficient with
				std::vector<std::string> choices = { "smith's tools", "brewer's supplies", "mason's tools" };
				m_ToolProficiencies.insert(choices[Random::Index(0, choices.size() - 1)]);
				m_WeaponProficiencies.insert({ "battleaxe", "handaxe", "throwing hammer", "warhammer" });

				if (m_Race == "Hill Dwarf")
				{
					m_Wisdom.Score++;
					m_MaxHitPoints += m_Level; // From the Dwarven Toughness feat
				}

				else if (m_Race == "Mountain Dwarf")
				{
					m_Strength.Score += 2;
					m_ArmorProficiencies.insert({ "light armor", "medium armor" });
				}
			}
			else if (m_MajorRace == "Elf")
			{
				m_Speed = 30;
				m_Dexterity.Score += 2;
				m_Perception.Proficient = true;
				m_Languages.insert("Elvish");

				if (m_Race == "High Elf")
				{
					m_Intelligence.Score++;
					m_WeaponProficiencies.insert({ "longsword", "shortsword", "shortbow", "longbow" });

					// Choose one additional language
					m_Languages.insert(Languages[Random::Index(1, Languages.size() - 1)]); // 1 is the minimum number to avoid picking Elvish twice

					// High elves get a cantrip from the wizard spell list
					m_Cantrips.insert(CantripLists.at("Wizard")[Random::Index(0, CantripLists.at("Wizard").size() - 1)]);
				}
				else if (m_Race == "Wood Elf")
				{
					m_Speed = 35;
					m_Wisdom.Score++;

					m_WeaponProficiencies.insert({ "longsword", "shortsword", "shortbow", "longbow" });
				}
				else if (m_Race == "Dark Elf (Drow)")
				{
					m_Charisma.Score++;
					m_WeaponProficiencies.insert({ "rapier", "shortsword", "hand crossbow" });
				}
			}
			else if (m_MajorRace == "Halfling")
			{
				m_Speed = 25;
				m_Dexterity.Score += 2;
				m_Languages.insert("Halfling");

				if (m_Race == "Lightfoot Halfling")
				{
					m_Charisma.Score++;
				}
				else if (m_Race == "Stout Halfling")
				{
					m_Constitution.Score++;
				}
			}
			else if (m_MajorRace == "Human")
			{
				m_Speed = 30;
				m_Strength.Score++;
				m_Dexterity.Score++;
				m_Constitution.Score++;
				m_Intelligence.Score++;
				m_Wisdom.Score++;
				m_Charisma.Score++;

				m_Languages.insert(Languages[Random::Index(0, Languages.size() - 1)]);
				// TODO: Add optional variant human trait
			}
			else if (m_MajorRace == "Dragonborn")
			{
				m_Speed = 30;
				m_Strength.Score += 2;
				m_Charisma.Score++;
				m_Languages.insert("Draconic");
			}
			else if (m_MajorRace == "Gnome")
			{
				m_Speed = 25;
				m_Intelligence.Score += 2;
				m_Languages.insert("Gnomish");

				if (m_Race == "Forest Gnome")
				{
					m_Dexterity.Score++;
					m_Cantrips.insert("minor illusion");
				}
				else if (m_Race == "Rock Gnome")
				{
					m_Constitution.Score++;
					m_ToolProficiencies.insert({ "set of tinker's tools" });
				}
			}
			else if (m_MajorRace == "Half-Elf")
			{
				m_Speed = 30;
				m_Charisma.Score += 2;

				// Half-elves can choose any other two ability score besides charisma to increase by 1
				// The same ability cannot receive both +1's
				std::vector<std::reference_wrapper<Ability>> abilities = { m_Strength, m_Dexterity, m_Constitution, m_Intelligence, m_Wisdom };
				size_t index = Random::Index(0, abilities.size() - 1);
				abilities[index].get().Score++;
				// Remove the ability whose score was just increased and choose anohter
				abilities.erase(abilities.begin() + index);
				abilities[Random::Index(0, abilities.size() - 1)].get().Score++;

				m_Languages.insert("Elvish");
				// Choose one additional language
				m_Languages.insert(Languages[Random::Index(1, Languages.size() - 1)]); // 1 is the minimum number to avoid picking Elvish twice

				// Half-elves can choose any two skills to be proficient in, from their Skill Versatility trait
				chooseSkillProficiencies(2, { m_Acrobatics, m_AnimalHandling, m_Arcana, m_Athletics, m_Deception, m_History, m_Insight, m_Intimidation,
					m_Investigation, m_Medicine, m_Nature, m_Perception, m_Performance, m_Persuasion, m_Religion, m_SleightOfHand, m_Stealth, m_Survival });
			}
			else if (m_MajorRace == "Half-Orc")
			{
				m_Speed = 30;
				m_Strength.Score += 2;
				m_Constitution.Score++;
				m_Intimidation.Proficient = true;
				m_Languages.insert("Orc");
			}
			else if (m_MajorRace == "Tiefling")
			{
				m_Speed = 30;
				m_Intelligence.Score++;
				m_Charisma.Score += 2;
				m_Languages.insert("Infernal");
				m_Cantrips.insert("thaumaturgy");
			}
		}

		// Class
		{
			m_Class = Classes[Random::Index(0, Classes.size() - 1)];

			m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), ClassFeats.at(m_Class).begin(), ClassFeats.at(m_Class).end());

			// Hit dice/points, proficiencies, saving throw proficiencies, skill proficiencies
			if (m_Class == "Barbarian")
			{
				m_HitDice.Type = 12;
				m_ArmorProficiencies.insert({ "light armor", "medium armor", "shields" });
				m_WeaponProficiencies.insert(AllSimpleWeapons.begin(), AllSimpleWeapons.end());
				m_WeaponProficiencies.insert(AllMartialWeapons.begin(), AllMartialWeapons.end());
				m_StrengthSave.Proficient = true;
				m_ConstitutionSave.Proficient = true;
				chooseSkillProficiencies(2, { m_AnimalHandling, m_Athletics, m_Intimidation, m_Nature, m_Perception, m_Survival });
				
				if (startWithEquipment)
				{
					// Most classes give certain set starting equipment, and allow the character to choose between a couple options for the rest of the equipment
					Random::Int(0, 1) ? addEquipment({ {"greataxe", 1} }) : addEquipment({ {MartialMeleeWeapons[Random::Index(0, MartialMeleeWeapons.size() - 1)], 1} });
					Random::Int(0, 1) ? addEquipment({ {"handaxe", 2} }) : addEquipment({ {AllSimpleWeapons[Random::Index(0, AllSimpleWeapons.size() - 1)], 1} });
					addEquipment({ {"explorer's pack", 1}, {"javelin", 4} });
				}
				else m_GoldPieces = 10 * Random::IntSum(1, 4, 2);
			}
			else if (m_Class == "Bard")
			{
				m_HitDice.Type = 8;

				// Pick three musical instruments to be proficient with
				for (int i = 0; i < 3; i++)
					addUniqueProficiency(m_ToolProficiencies, MusicalInstruments);

				m_ArmorProficiencies.insert("light armor");
				m_WeaponProficiencies.insert(AllSimpleWeapons.begin(), AllSimpleWeapons.end());
				m_WeaponProficiencies.insert({ "hand crossbow", "longsword", "rapier", "shortsword" });

				m_DexteritySave.Proficient = true;
				m_CharismaSave.Proficient = true;

				// Pick any three skills to be proficient in
				chooseSkillProficiencies(3, { m_Acrobatics, m_AnimalHandling, m_Arcana, m_Athletics, m_Deception, m_History, m_Insight,
					m_Intimidation, m_Investigation, m_Medicine, m_Nature, m_Perception, m_Performance, m_Persuasion, m_Religion,
					m_SleightOfHand, m_Stealth, m_Survival });

				// TODO: These numbers will be based on level in the future
				m_CantripsKnown = 2;
				m_SpellsKnown = 4;
				m_SpellSlots = 2;

				if (startWithEquipment)
				{
					int choice = Random::Int(0, 2);
					if (choice == 0) addEquipment({ {"rapier", 1} });
					else if (choice == 1) addEquipment({ {"longsword", 1} });
					else if (choice == 2) addEquipment({ {AllSimpleWeapons[Random::Index(0, AllSimpleWeapons.size() - 1)], 1} });

					Random::Int(0, 1) ? addEquipment({ {"diplomat's pack", 1} }) : addEquipment({ {"entertainer's pack", 1} });
					Random::Int(0, 1) ? addEquipment({ {"lute", 1} }) : addEquipment({ {MusicalInstruments[Random::Index(0, MusicalInstruments.size() - 1)], 1} });
					addEquipment({ {"leather armor", 1}, {"dagger", 1} });
				}
				else m_GoldPieces = 10 * Random::IntSum(1, 4, 5);
			}
			else if (m_Class == "Cleric")
			{
				m_HitDice.Type = 8;
				m_ArmorProficiencies.insert({ "light armor", "medium armor", "shields" });
				m_WeaponProficiencies.insert(AllSimpleWeapons.begin(), AllSimpleWeapons.end());
				m_WisdomSave.Proficient = true;
				m_CharismaSave.Proficient = true;
				chooseSkillProficiencies(2, { m_History, m_Insight, m_Medicine, m_Persuasion, m_Religion });
				m_CantripsKnown = 3;
				m_SpellSlots = 2;
				m_SpellsPrepared = std::max(1, m_Level + m_Wisdom.Modifier);

				// Pick a cleric domain
				std::vector<std::string> domains = { "Knowledge Domain", "Life Domain", "Light Domain", "Nature Domain", "Tempest Domain", "Trickery Domain", "War Domain" };
				std::string domain = domains[Random::Index(0, domains.size() - 1)];
				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), ClericDomainFeats.at(domain).begin(), ClericDomainFeats.at(domain).end());
				m_Spells.insert(DomainSpells.at(domain).begin(), DomainSpells.at(domain).end());
				std::cout << domain << "\n\n";

				// Note: The Trickery Domain doesn't get anything extra at 1st level that goes on the character sheet
				if (domain == "Knowledge Domain")
				{
					// From the Blessings of Knowledge Feat
					for (int i = 0; i < 2; i++)
						addUniqueProficiency(m_Languages, Languages);

					chooseSkillProficiencies(2, { m_Arcana, m_History, m_Nature, m_Religion });
				}
				else if (domain == "Life Domain")
				{
					m_ArmorProficiencies.insert("heavy armor");
				}
				else if (domain == "Light Domain")
				{
					m_Cantrips.insert("light");
				}
				else if (domain == "Nature Domain")
				{
					// From the Acolyte of Nature Feat, pick a cantrip from the Druid list
					m_Cantrips.insert(CantripLists.at("Druid")[Random::Index(0, CantripLists.at("Druid").size() - 1)]);
					chooseSkillProficiencies(1, { m_AnimalHandling, m_Nature, m_Survival });
					m_ArmorProficiencies.insert("heavy armor");
				}
				else if (domain == "Tempest Domain" || domain == "War Domain")
				{
					// Note: These cases will probably need to be separate when higher levels are considered
					m_ArmorProficiencies.insert("heavy armor");
					m_WeaponProficiencies.insert(AllMartialWeapons.begin(), AllMartialWeapons.end());
				}

				if (startWithEquipment)
				{
					// A cleric must be proficient with warhammers to choose between a warhammer and a mace. Otherwise, a mace is their only choice
					if (m_WeaponProficiencies.contains("warhammer") || m_WeaponProficiencies.contains("all martial weapons"))
						Random::Int(0, 1) ? addEquipment({ {"mace", 1} }) : addEquipment({ {"warhammer", 1} });
					else
						addEquipment({ {"mace", 1} });

					int choice = 0;
					// A cleric must be proficient with heavy armor to have chain mail as a choice of starting equipment
					if (m_ArmorProficiencies.contains("heavy armor") || m_ArmorProficiencies.contains("all armor")) choice = Random::Int(0, 2);
					else choice = Random::Int(0, 1);

					if (choice == 0) addEquipment({ {"scale mail", 1} });
					else if (choice == 1) addEquipment({ {"leather armor", 1} });
					else if (choice == 2) addEquipment({ {"chain mail", 1} });
					
					Random::Int(0, 1) ? addEquipment({ {"light crossbow", 1}, {"bolt", 20} }) : addEquipment({ {AllSimpleWeapons[Random::Index(0, SimpleMeleeWeapons.size() - 1)], 1} });
					Random::Int(0, 1) ? addEquipment({ {"priest's pack", 1} }) : addEquipment({ {"explorer's pack", 1} });
					addEquipment({ {"shield", 1}, {"holy symbol", 1} });
				}
				else m_GoldPieces = 10 * Random::IntSum(1, 4, 5);
			}
			else if (m_Class == "Druid")
			{
				m_HitDice.Type = 8;
				m_Languages.insert("Druidic"); // From Druidic class feat
				m_ArmorProficiencies.insert({ "light armor", "medium armor", "shields" });
				m_WeaponProficiencies.insert({ "club", "dagger", "dart", "javelin", "mace", "quarterstaff", "scimitar", "sickle", "sling", "spear" });
				m_ToolProficiencies.insert("herbalism kit");
				m_IntelligenceSave.Proficient = true;
				m_WisdomSave.Proficient = true;
				chooseSkillProficiencies(2, { m_Arcana, m_AnimalHandling, m_Insight, m_Medicine, m_Nature, m_Perception, m_Religion, m_Survival });
				m_CantripsKnown = 2;
				m_SpellSlots = 2;
				m_SpellsPrepared = std::max(1, m_Level + m_Wisdom.Modifier);

				if (startWithEquipment)
				{
					Random::Int(0, 1) ? addEquipment({ {"wooden shield", 1} }) : addEquipment({ {AllSimpleWeapons[Random::Index(0, AllSimpleWeapons.size() - 1)], 1} });
					Random::Int(0, 1) ? addEquipment({ {"scimitar", 1} }) : addEquipment({ {SimpleMeleeWeapons[Random::Index(0, SimpleMeleeWeapons.size() - 1)], 1} });
					addEquipment({ {"leather armor", 1}, {"explorer's pack", 1}, {"druidic focus", 1} });
				}
				else m_GoldPieces = 10 * Random::IntSum(1, 4, 2);
			}
			else if (m_Class == "Fighter")
			{
				m_HitDice.Type = 10;
				m_ArmorProficiencies.insert({ "light armor", "medium armor", "heavy armor", "shields" });
				m_WeaponProficiencies.insert(AllSimpleWeapons.begin(), AllSimpleWeapons.end());
				m_WeaponProficiencies.insert(AllMartialWeapons.begin(), AllMartialWeapons.end());
				m_StrengthSave.Proficient = true;
				m_ConstitutionSave.Proficient = true;
				chooseSkillProficiencies(2, { m_Acrobatics, m_AnimalHandling, m_Athletics, m_History, m_Insight, m_Intimidation, m_Perception, m_Survival });

				// Pick a fighting style
				m_FeatsAndTraits.push_back(FightingStyles[Random::Index(0, FightingStyles.size() - 1)]);

				if (startWithEquipment)
				{
					Random::Int(0, 1) ? addEquipment({ {"chain mail", 1} }) : addEquipment({ {"leather armor", 1}, {"longbow", 1}, {"arrow", 20} });
					Random::Int(0, 1) ? addEquipment({ {AllMartialWeapons[Random::Index(0, AllMartialWeapons.size() - 1)], 1}, {"shield", 1} })
						: addEquipment({ {AllMartialWeapons[Random::Index(0, AllMartialWeapons.size() - 1)], 1}, {AllMartialWeapons[Random::Index(0, AllMartialWeapons.size() - 1)], 1} });
					Random::Int(0, 1) ? addEquipment({ {"light crossbow", 1}, {"bolt", 20} }) : addEquipment({ {"handaxe", 2} });
					Random::Int(0, 1) ? addEquipment({ {"dungeoneer's pack", 1} }) : addEquipment({ {"explorer's pack", 1} });
				}
				else m_GoldPieces = 10 * Random::IntSum(1, 4, 5);
			}
			else if (m_Class == "Monk")
			{
				m_HitDice.Type = 8;

				m_WeaponProficiencies.insert(AllSimpleWeapons.begin(), AllSimpleWeapons.end());
				m_WeaponProficiencies.insert("shortsword");
				// Choose one type of artisan's tools or musical instrument
				Random::Int(0, 1) ? m_ToolProficiencies.insert(ArtisanTools[Random::Index(0, ArtisanTools.size() - 1)]) 
					: m_ToolProficiencies.insert(MusicalInstruments[Random::Index(0, MusicalInstruments.size() - 1)]);

				m_StrengthSave.Proficient = true;
				m_DexteritySave.Proficient = true;
				chooseSkillProficiencies(2, { m_Acrobatics, m_Athletics, m_History, m_Insight, m_Religion, m_Stealth });

				if (startWithEquipment)
				{
					Random::Int(0, 1) ? addEquipment({ {"shortsword", 1} }) : addEquipment({ {AllSimpleWeapons[Random::Index(0, AllSimpleWeapons.size() - 1)], 1} });
					Random::Int(0, 1) ? addEquipment({ {"dungeoneer's pack", 1} }) : addEquipment({ {"explorer's pack", 1} });
					addEquipment({ {"dart", 10} });
				}
				else m_GoldPieces = Random::IntSum(1, 4, 5);
			}
			else if (m_Class == "Paladin")
			{
				m_HitDice.Type = 10;
				m_ArmorProficiencies.insert({ "light armor", "medium armor", "heavy armor", "shields" });
				m_WeaponProficiencies.insert(AllSimpleWeapons.begin(), AllSimpleWeapons.end());
				m_WeaponProficiencies.insert(AllMartialWeapons.begin(), AllMartialWeapons.end());
				m_WisdomSave.Proficient = true;
				m_CharismaSave.Proficient = true;
				chooseSkillProficiencies(2, { m_Athletics, m_Insight, m_Intimidation, m_Medicine, m_Persuasion, m_Religion });

				if (startWithEquipment)
				{
					Random::Int(0, 1) ? addEquipment({ {AllMartialWeapons[Random::Index(0, AllMartialWeapons.size() - 1)], 1}, {"shield", 1} }) 
						: addEquipment({ {AllMartialWeapons[Random::Index(0, AllMartialWeapons.size() - 1)], 1}, { AllMartialWeapons[Random::Index(0, AllMartialWeapons.size() - 1)], 1 } });
					Random::Int(0, 1) ? addEquipment({ {"javeline", 5} }) : addEquipment({ {SimpleMeleeWeapons[Random::Index(0, SimpleMeleeWeapons.size() - 1)], 1} });
					Random::Int(0, 1) ? addEquipment({ {"priest's pack", 1} }) : addEquipment({ {"explorer's pack", 1} });
					addEquipment({ {"chain mail", 1}, {"holy symbol", 1} });
				}
				else m_GoldPieces = 10 * Random::IntSum(1, 4, 5);
			}
			else if (m_Class == "Ranger")
			{
				m_HitDice.Type = 10;
				m_ArmorProficiencies.insert({ "light armor", "medium armor", "shields" });
				m_WeaponProficiencies.insert(AllSimpleWeapons.begin(), AllSimpleWeapons.end());
				m_WeaponProficiencies.insert(AllMartialWeapons.begin(), AllMartialWeapons.end());
				m_StrengthSave.Proficient = true;
				m_DexteritySave.Proficient = true;
				chooseSkillProficiencies(3, { m_AnimalHandling, m_Athletics, m_Insight, m_Investigation, m_Nature, m_Perception, m_Stealth, m_Survival });

				if (startWithEquipment)
				{
					Random::Int(0, 1) ? addEquipment({ {"scale mail", 1} }) : addEquipment({ {"leather armor", 1} });
					Random::Int(0, 1) ? addEquipment({ {"shortsword", 2} }) 
						: addEquipment({ {SimpleMeleeWeapons[Random::Index(0, SimpleMeleeWeapons.size() - 1)], 1}, {SimpleMeleeWeapons[Random::Index(0, SimpleMeleeWeapons.size() - 1)], 1} });
					Random::Int(0, 1) ? addEquipment({ {"dungeoneer's pack", 1} }) : addEquipment({ {"explorer's pack", 1} });
					addEquipment({ {"longbow", 1}, {"arrow", 20} });
				}
				else m_GoldPieces = 10 * Random::IntSum(1, 4, 5);
			}
			else if (m_Class == "Rogue")
			{
				m_HitDice.Type = 8;
				m_Languages.insert("Thieves' Cant"); // From Thieves' Cant class feat
				m_ArmorProficiencies.insert("light armor");
				m_WeaponProficiencies.insert(AllSimpleWeapons.begin(), AllSimpleWeapons.end());
				m_WeaponProficiencies.insert({ "hand crossbow", "longsword", "rapier", "shortsword" });
				m_ToolProficiencies.insert("thieves' tools");
				m_DexteritySave.Proficient = true;
				m_IntelligenceSave.Proficient = true;
				chooseSkillProficiencies(4, { m_Acrobatics, m_Athletics, m_Deception, m_Insight, m_Intimidation, m_Investigation, m_Perception, m_Performance, m_Persuasion, m_SleightOfHand, m_Stealth });

				if (startWithEquipment)
				{
					Random::Int(0, 1) ? addEquipment({ {"rapier", 1} }) : addEquipment({ {"shortsword", 1} });
					Random::Int(0, 1) ? addEquipment({ {"shortbow", 1}, {"arrow", 20} }) : addEquipment({ {"shortsword", 1} });
					
					int choice = Random::Int(0, 2);
					if (choice == 0) addEquipment({ {"burglar's pack", 1} });
					else if (choice == 1) addEquipment({ {"dungeoneer's pack", 1} });
					else addEquipment({ {"explorer's pack", 1} });

					addEquipment({ {"leather armor", 1}, {"dagger", 2}, {"set of thieves' tools", 1} });
				}
				else m_GoldPieces = 10 * Random::IntSum(1, 4, 4);
			}
			else if (m_Class == "Sorcerer")
			{
				m_HitDice.Type = 6;
				m_WeaponProficiencies.insert({ "dagger", "dart", "quarterstaff", "light crossbow" });
				m_ConstitutionSave.Proficient = true;
				m_CharismaSave.Proficient = true;
				chooseSkillProficiencies(2, { m_Arcana, m_Deception, m_Insight, m_Intimidation, m_Persuasion, m_Religion });
				m_CantripsKnown = 4;
				m_SpellsKnown = 2;
				m_SpellSlots = 2;

				std::vector<std::string> origins = { "Draconic Bloodline", "Wild Magic" };
				std::string sorcerousOrigin = origins[Random::Index(0, origins.size() - 1)];
				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), SorcerousOriginFeats.at(sorcerousOrigin).begin(), SorcerousOriginFeats.at(sorcerousOrigin).end());

				if (sorcerousOrigin == "Draconic Bloodline")
				{
					std::vector<std::string> dragonTypes = { "black", "blue", "brass", "bronze", "copper", "gold", "green", "red", "silver", "white" };
					std::string draconicAncestry = dragonTypes[Random::Index(0, dragonTypes.size() - 1)];

					m_FeatsAndTraits.insert(m_FeatsAndTraits.end(),
						Trait("Dragon Ancestor", "You have a " + draconicAncestry +
							"dragon as your ancestor. You can speak, read, and write Draconic. "
							"Additionally, whenever you make a Charisma check when interacting with dragons, "
							"your proficiency bonus is doubled if it applies to the check."));

					// The Dragon Ancestor feat lets the character understand Draconic
					if (!m_Languages.contains("Draconic"))
						m_Languages.insert("Draconic");
					else
						addUniqueProficiency(m_Languages, Languages);
				}


				if (startWithEquipment)
				{
					Random::Int(0, 1) ? addEquipment({ {"light crossbow", 1}, {"bolt", 20} }) : addEquipment({ {AllSimpleWeapons[Random::Index(0, AllSimpleWeapons.size() - 1)], 1} });
					Random::Int(0, 1) ? addEquipment({ {"component pouch", 1} }) : addEquipment({ {"arcane focus", 1} });
					Random::Int(0, 1) ? addEquipment({ {"dungeoneer's pack", 1} }) : addEquipment({ {"explorer's pack", 1} });
					addEquipment({ {"dagger", 2} });
				}
				else m_GoldPieces = 10 * Random::IntSum(1, 4, 3);
			}
			else if (m_Class == "Warlock")
			{
				m_HitDice.Type = 8;
				m_ArmorProficiencies.insert("light armor");
				m_WeaponProficiencies.insert(AllSimpleWeapons.begin(), AllSimpleWeapons.end());
				m_WisdomSave.Proficient = true;
				m_CharismaSave.Proficient = true;
				chooseSkillProficiencies(2, { m_Arcana, m_Deception, m_History, m_Intimidation, m_Investigation, m_Nature, m_Religion });
				m_CantripsKnown = 2;
				m_SpellsKnown = 2;
				m_SpellSlots = 1;

				std::vector<std::string> otherworldlyPatrons = { "The Archfey", "The Fiend", "The Great Old One" };
				std::string patron = otherworldlyPatrons[Random::Index(0, otherworldlyPatrons.size() - 1)];

				m_FeatsAndTraits.insert(m_FeatsAndTraits.end(), OtherworldlyPatronFeats.at(patron).begin(), OtherworldlyPatronFeats.at(patron).end());
				SpellLists.at("Warlock").insert(SpellLists.at("Warlock").end(), PatronSpells.at(patron).begin(), PatronSpells.at(patron).end());

				if (startWithEquipment)
				{
					Random::Int(0, 1) ? addEquipment({ {"light crossbow", 1}, {"bolt", 20} }) : addEquipment({ {AllSimpleWeapons[Random::Index(0, AllSimpleWeapons.size() - 1)], 1} });
					Random::Int(0, 1) ? addEquipment({ {"component pouch", 1} }) : addEquipment({ {"arcane focus", 1} });
					Random::Int(0, 1) ? addEquipment({ {"scholar's pack", 1} }) : addEquipment({ {"dungeoneer's pack", 1} });
					addEquipment({ {"leather armor", 1}, {"dagger", 2}, {AllSimpleWeapons[Random::Index(0, AllSimpleWeapons.size() - 1)], 1} });
				}
				else m_GoldPieces = 10 * Random::IntSum(1, 4, 4);
			}
			else if (m_Class == "Wizard")
			{
				m_HitDice.Type = 6;
				m_WeaponProficiencies.insert({ "dagger", "dart", "sling", "quarterstaff", "light crossbow" });
				m_IntelligenceSave.Proficient = true;
				m_WisdomSave.Proficient = true;
				chooseSkillProficiencies(2, { m_Arcana, m_History, m_Insight, m_Investigation, m_Medicine, m_Religion });
				m_CantripsKnown = 3;
				m_SpellSlots = 2;
				m_SpellsPrepared = std::max(1, m_Level + m_Intelligence.Modifier);


				if (startWithEquipment)
				{
					Random::Int(0, 1) ? addEquipment({ {"quarterstaff", 1} }) : addEquipment({ {"dagger", 1} });
					Random::Int(0, 1) ? addEquipment({ {"component pouch", 1} }) : addEquipment({ {"arcane focus", 1} });
					Random::Int(0, 1) ? addEquipment({ {"scholar's pack", 1} }) : addEquipment({ {"explorer's pack", 1} });
					addEquipment({ {"spellbook", 1} });
				}
				else m_GoldPieces = 10 * Random::IntSum(1, 4, 4);
			}

			// Determine spells and cantrips by picking random cantrips and spells from the class's spell list
			if (m_CantripsKnown > 0)
			{
				for (int i = 0; i < m_CantripsKnown; i++)
				{
					std::string cantrip = CantripLists.at(m_Class)[Random::Index(0, CantripLists.at(m_Class).size() - 1)];
					while (m_Cantrips.contains(cantrip))
						cantrip = CantripLists.at(m_Class)[Random::Index(0, CantripLists.at(m_Class).size() - 1)];

					m_Cantrips.insert(cantrip);
				}
			}
			if (m_SpellsKnown > 0)
			{
				for (int i = 0; i < m_SpellsKnown; i++)
				{
					std::string spell = SpellLists.at(m_Class)[Random::Index(0, SpellLists.at(m_Class).size() - 1)];
					while (m_Spells.contains(spell))
						spell = SpellLists.at(m_Class)[Random::Index(0, SpellLists.at(m_Class).size() - 1)];

					m_Spells.insert(spell);
				}
			}
		}

		// Background
		{
			m_Background = Backgrounds[Random::Index(0, Backgrounds.size() - 1)];

			// Personality Traits
			// Generate two unique random numbers to ensure personality traits are different
			std::vector<std::string> personalityList = PersonalityTraits.at(m_Background);
			size_t first = Random::Index(0, personalityList.size() - 1);
			size_t second = Random::Index(0, personalityList.size() - 1);

			// Ensure two unique traits are chosen
			while (second == first)
				second = Random::Index(0, personalityList.size() - 1);

			m_PersonalityTraits = personalityList[first] + " " + personalityList[second];

			// Ideals
			std::string axis1 = m_Alignment.substr(0, m_Alignment.find(' ')); // Lawful, Neutral, or Chaotic
			std::string axis2 = m_Alignment.substr(m_Alignment.find(' ') + 1); // Good, Neutral, or Evil;
			auto& idealsList = Ideals.at(m_Background);

			while (m_Ideals == "")
			{
				size_t index = Random::Index(0, idealsList.size() - 1);

				if (idealsList[index].first == axis1 || idealsList[index].first == axis2 || idealsList[index].first == "Any")
					m_Ideals = idealsList[index].second;
			}

			// Bonds
			SetTraitFromDict(m_Bonds, Bonds, m_Background);

			// Flaws
			SetTraitFromDict(m_Flaws, Flaws, m_Background);

			// Background feats
			// Some backgrounds offer variant feats, but a character may only choose one feat from a background.
			size_t index = Random::Index(0, BackgroundFeats.at(m_Background).size() - 1);
			m_FeatsAndTraits.push_back(BackgroundFeats.at(m_Background)[index]);

			std::vector<std::reference_wrapper<Skill>> skills = { m_Acrobatics, m_AnimalHandling, m_Arcana, m_Athletics, m_Deception, m_History, m_Insight,
					m_Intimidation, m_Investigation, m_Medicine, m_Nature, m_Perception, m_Performance, m_Persuasion, m_Religion, m_SleightOfHand, m_Stealth, m_Survival };

			// Attempt to make the character proficient in a skill. If the character is already proficient in that skill, choose another 
			auto addSkillProficiency = [skills](std::reference_wrapper<Skill> skill)
			{
				while (skill.get().Proficient)
					skill = skills[Random::Index(0, skills.size() - 1)];

				skill.get().Proficient = true;
			};

			// Proficiencies
			// If backgrounds give a character duplicate proficiencies, the character can choose another proficiency of the same type (skill or tool)
			if (m_Background == "Acolyte")
			{
				addSkillProficiency(m_Insight);
				addSkillProficiency(m_Religion);

				// Choose two additional languages
				for (int i = 0; i < 2; i++)
					addUniqueProficiency(m_Languages, Languages);

				if (startWithEquipment)
				{
					std::vector<std::pair<std::string, int>> flavorItems = { { "prayer book", 1}, {"prayer wheel", 1 } };
					addEquipment({ {"holy symbol", 1}, {"stick of incense", 5 }, {"vestments", 1}, {"set of common clothes", 1}, {"pouch", 1} });
					addEquipment({ flavorItems[Random::Index(0, flavorItems.size() - 1)] }); // Add a random flavor item
					m_GoldPieces += 15; // From the pouch
				}
			}
			else if (m_Background == "Charlatan")
			{
				addSkillProficiency(m_Deception);
				addSkillProficiency(m_SleightOfHand);

				// if second == false, then the element could not be inserted (was a duplicate)
				if (m_ToolProficiencies.insert("disguise kit").second == false) addUniqueProficiency(m_ToolProficiencies, OtherTools);
				if (m_ToolProficiencies.insert("forgery kit").second == false)  addUniqueProficiency(m_ToolProficiencies, OtherTools);

				if (startWithEquipment)
				{
					std::vector<std::pair<std::string, int>> flavorItems = { {"toppered bottles filled with colored liquid", 10}, {"set of weighted dice", 1 },
						{"deck of marked cards", 1 }, {"signet ring of an imaginary duke", 1} };
					addEquipment({ {"set of fine clothes", 1}, {"disguise kit", 1}, {"pouch", 1} });
					addEquipment({ flavorItems[Random::Index(0, flavorItems.size() - 1)] });
					m_GoldPieces += 15;
				}
			}
			else if (m_Background == "Criminal" || m_Background == "Spy")
			{
				addSkillProficiency(m_Deception);
				addSkillProficiency(m_Stealth);

				addUniqueProficiency(m_ToolProficiencies, GamingSets);
				if (m_ToolProficiencies.insert("thieves' tools").second == false) addUniqueProficiency(m_ToolProficiencies, OtherTools);

				if (startWithEquipment)
				{
					addEquipment({ {"crowbar", 1}, {"set of dark common clothes including a hood", 1}, {"pouch", 1} });
					m_GoldPieces += 15;
				}
			}
			else if (m_Background == "Entertainer" || m_Background == "Gladiator")
			{
				addSkillProficiency(m_Acrobatics);
				addSkillProficiency(m_Performance);

				addUniqueProficiency(m_ToolProficiencies, MusicalInstruments);
				if (m_ToolProficiencies.insert("disguise kit").second == false) addUniqueProficiency(m_ToolProficiencies, OtherTools);

				if (startWithEquipment)
				{
					std::vector<std::pair<std::string, int>> flavorItems = { {"love letter from an admirer", 1}, {"lock of hair from an admirer", 1}, {"trinket from an admirer", 1} };
					addEquipment({ {MusicalInstruments[Random::Index(0, MusicalInstruments.size() - 1)], 1}, {"costume", 1}, {"pouch", 1} });
					addEquipment({ flavorItems[Random::Index(0, flavorItems.size() - 1)] });
					m_GoldPieces += 15;
				}

			}
			else if (m_Background == "Folk Hero")
			{
				addSkillProficiency(m_AnimalHandling);
				addSkillProficiency(m_Survival);

				addUniqueProficiency(m_ToolProficiencies, ArtisanTools);
				if (m_ToolProficiencies.insert("vehicles (land)").second == false) addUniqueProficiency(m_ToolProficiencies, OtherTools);

				if (startWithEquipment)
				{
					addEquipment({ {"set of " + ArtisanTools[Random::Index(0, ArtisanTools.size() - 1)], 1}, {"shovel", 1}, {"iron pot", 1}, {"set of common clothes", 1}, {"pouch", 1} });
					m_GoldPieces += 10;
				}
			}
			else if (m_Background == "Guild Artisan" || m_Background == "Guild Merchant")
			{
				addSkillProficiency(m_Insight);
				addSkillProficiency(m_Persuasion);

				addUniqueProficiency(m_Languages, Languages);
				addUniqueProficiency(m_ToolProficiencies, ArtisanTools);

				if (startWithEquipment)
				{
					addEquipment({ {"set of " + ArtisanTools[Random::Index(0, ArtisanTools.size() - 1)], 1}, {"set of traveler's clothes", 1}, {"pouch", 1},
						{"letter of introduction from your guild", 1} });
					m_GoldPieces += 15;
				}
			}
			else if (m_Background == "Hermit")
			{
				addSkillProficiency(m_Medicine);
				addSkillProficiency(m_Religion);

				addUniqueProficiency(m_Languages, Languages);
				if (m_ToolProficiencies.insert("herbalism kit").second == false) addUniqueProficiency(m_ToolProficiencies, OtherTools);

				if (startWithEquipment)
				{
					std::vector<std::pair<std::string, int>> flavorItems = { {"scroll case stuffed full of notes from your studies", 1},
						{"scroll case stuffed full of notes from your prayers", 1} };
					addEquipment({ {"winter blanket", 1}, {"set of common clothes", 1}, {"herbalism kit", 1} });
					addEquipment({ flavorItems[Random::Index(0, flavorItems.size() - 1)] });
					m_GoldPieces += 5;
				}
			}
			else if (m_Background == "Noble" || m_Background == "Knight")
			{
				addSkillProficiency(m_History);
				addSkillProficiency(m_Persuasion);

				addUniqueProficiency(m_Languages, Languages);
				addUniqueProficiency(m_ToolProficiencies, GamingSets);

				if (startWithEquipment)
				{
					addEquipment({ {"set of fine clothes", 1}, {"signet ring", 1}, {"scroll of pedigree", 1}, {"purse", 1} });
					m_GoldPieces += 25;
				}

			}
			else if (m_Background == "Outlander")
			{
				addSkillProficiency(m_Athletics);
				addSkillProficiency(m_Survival);

				addUniqueProficiency(m_Languages, Languages);
				addUniqueProficiency(m_ToolProficiencies, MusicalInstruments);

				if (startWithEquipment)
				{
					addEquipment({ {"staff", 1}, {"hunting trap", 1}, {"animal trophy", 1}, {"set of traveler's clothes", 1}, {"pouch", 1} });
					m_GoldPieces += 10;
				}
			}
			else if (m_Background == "Sage")
			{
				addSkillProficiency(m_Arcana);
				addSkillProficiency(m_History);

				// Choose two additional languages
				for (int i = 0; i < 2; i++)
					addUniqueProficiency(m_Languages, Languages);

				if (startWithEquipment)
				{
					addEquipment({ {"bottle of black ink", 1}, {"quill", 1}, {"small knife", 1}, {"set of common clothes", 1}, {"pouch", 1},
						{"letter from a dead colleague posing a question you have not yet been able to answer", 1} });
					m_GoldPieces += 10;
				}

			}
			else if (m_Background == "Sailor" || m_Background == "Pirate")
			{
				addSkillProficiency(m_Athletics);
				addSkillProficiency(m_Perception);

				if (m_ToolProficiencies.insert("navigator's tools").second == false) addUniqueProficiency(m_ToolProficiencies, OtherTools);
				if (m_ToolProficiencies.insert("vehicles (water)").second == false)  addUniqueProficiency(m_ToolProficiencies, OtherTools);

				if (startWithEquipment)
				{
					std::vector<std::pair<std::string, int>> flavorItems = { {"rabbit's foot", 1}, {"small stone with a hole in the center", 1} };
					addEquipment({ {"belaying pin (club)", 1}, {"50 feet of silk rope", 1}, {"set of common clothes", 1}, {"pouch", 1} });
					Random::Int(0, 1) ? addEquipment({flavorItems[Random::Index(0, flavorItems.size() - 1)]}) : addEquipment({ {Trinkets[Random::Index(0, Trinkets.size() - 1)], 1} });
					m_GoldPieces += 10;
				}
			}
			else if (m_Background == "Soldier")
			{
				addSkillProficiency(m_Athletics);
				addSkillProficiency(m_Intimidation);

				addUniqueProficiency(m_ToolProficiencies, GamingSets);
				if (m_ToolProficiencies.insert("vehicles (land)").second == false) addUniqueProficiency(m_ToolProficiencies, OtherTools);

				if (startWithEquipment)
				{
					std::vector<std::string> choices = { "dagger", "broken blade", "piece of banner" };
					std::string flavorText = choices[Random::Index(0, choices.size() - 1)] + " taken as a trophy from a fallen enemy";
					addEquipment({ {"insignia of rank", 1}, {"pouch", 1}, {flavorText, 1} });
					Random::Int(0, 1) ? addEquipment({ {"set of bone dice", 1} }) : addEquipment({ {"deck of cards", 1} });
					m_GoldPieces += 10;
				}
			}
			else if (m_Background == "Urchin")
			{
				addSkillProficiency(m_SleightOfHand);
				addSkillProficiency(m_Stealth);

				if (m_ToolProficiencies.insert("disguise kit").second == false)   addUniqueProficiency(m_ToolProficiencies, OtherTools);
				if (m_ToolProficiencies.insert("thieves' tools").second == false) addUniqueProficiency(m_ToolProficiencies, OtherTools);

				if (startWithEquipment)
				{
					addEquipment({ {"small knife", 1}, {"map of the city you grew up in", 1}, {"pet mouse", 1}, {"token to remember your parents by", 1}, {"pouch", 1} });
					m_GoldPieces += 10;
				}
			}
		}

		// Independent of race, class, and background, but need to be processed after
		{
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

			// TODO: Add other modifiers
			m_Initiative = m_Dexterity.Modifier;
			// Hit dice/points
			m_HitDice.Number = m_Level;
			m_MaxHitPoints = m_HitDice.Type + m_Constitution.Modifier;

			// Skill modifiers are based on the abilities that govern them
			m_Athletics.Parent = m_Strength;
			m_Acrobatics.Parent = m_SleightOfHand.Parent = m_Stealth.Parent = m_Dexterity;
			m_Arcana.Parent = m_History.Parent = m_Investigation.Parent = m_Nature.Parent = m_Religion.Parent = m_Intelligence;
			m_AnimalHandling.Parent = m_Insight.Parent = m_Medicine.Parent = m_Perception.Parent = m_Survival.Parent = m_Wisdom;
			m_Deception.Parent = m_Intimidation.Parent = m_Performance.Parent = m_Persuasion.Parent = m_Charisma;

			std::vector<std::reference_wrapper<Skill>> skills = { m_Acrobatics, m_AnimalHandling, m_Arcana, m_Athletics, m_Deception, m_History, m_Insight,
				m_Intimidation, m_Investigation, m_Medicine, m_Nature, m_Perception, m_Performance, m_Persuasion, m_Religion, m_SleightOfHand, m_Stealth, m_Survival };

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

			// Passive wisdom is wisdom modifier + 10 + proficiency bonus (if proficient in perception)
			m_PassiveWisdom = m_Wisdom.Modifier + 10;
			if (m_Perception.Proficient)
				m_PassiveWisdom += m_ProficiencyBonus;

			{
				// Every character can pick one trinket. Make sure it is unique
				std::string trinket = Trinkets[Random::Index(0, Trinkets.size() - 1)];
				if (!m_Equipment.contains(trinket))
					addEquipment({ {trinket, 1} });

				// Some trinkets allow the player to pick certian aspects of them
				for (const auto& it : TrinketChoices)
				{
					if (m_Equipment.contains(it.first))
					{
						std::string trinketCopy = it.first;
						// Choose a random item from the vector of choices to customize the trinket
						std::string choice = " " + TrinketChoices.at(trinketCopy)[Random::Index(0, TrinketChoices.at(trinketCopy).size() - 1)];

						// The choice comes after "mechanical in this trinket
						if (trinketCopy == "tiny mechanical that moves about when it's no longer being observed")
							trinketCopy.insert(15, choice);
						// Choices in other trinkets are at the end
						else
							trinketCopy = trinketCopy + choice;

						// Replace the trinket that was in the character's inventory with the modified version
						m_Equipment.erase(it.first);
						m_Equipment.insert({ trinketCopy, 1 });
					}
				}
			}

			// Attacks
			for (const auto& it : WeaponAttacks)
			{
				if (m_Equipment.contains(it.first))
				{
					int attackBonus = 0;
					std::string damage = it.second;
					int abilityModifier = 0;

					if (std::find(SimpleMeleeWeapons.begin(), SimpleMeleeWeapons.end(), it.first) != SimpleMeleeWeapons.end()
						|| std::find(MartialMeleeWeapons.begin(), MartialMeleeWeapons.end(), it.first) != MartialMeleeWeapons.end())
					{
						// If a melee weapon has the finesse property, the character can add their dexterity modifier to the attack bonus instead of strength
						if (it.first == "dagger" || it.first == "rapier" || it.first == "scimitar" || it.first == "shortsword" || it.first == "whip")
						{
							attackBonus += abilityModifier = std::max(m_Dexterity.Modifier, m_Strength.Modifier);
							
						}
						else
							attackBonus += abilityModifier = m_Strength.Modifier;
					}
					else if (std::find(SimpleRangedWeapons.begin(), SimpleRangedWeapons.end(), it.first) != SimpleRangedWeapons.end()
						|| std::find(MartialRangedWeapons.begin(), MartialRangedWeapons.end(), it.first) != MartialRangedWeapons.end())
					{
						// If a ranged weapon has the thrown property, the character can add their strength modifier to the attack bonus instead of dexterity
						if (it.first == "dart" || it.first == "net")
							attackBonus += abilityModifier = std::max(m_Dexterity.Modifier, m_Strength.Modifier);
						else
							attackBonus += abilityModifier = m_Dexterity.Modifier;
					}

					// If the character is proficient with a weapon, they add their proficiency bonus to their attack bonus
					if (m_WeaponProficiencies.contains(it.first))
						attackBonus += m_ProficiencyBonus;

					// Add to the damage whichever ability modifier applied to the attack bonus
					if (damage.length() > 0)
					{
						size_t pos = damage.find_first_of(' ');
						std::string str;
						if (abilityModifier > 0)
							str = " + " + std::to_string(abilityModifier);
						else if (abilityModifier < 0)
							str = " - " + std::to_string(std::abs(abilityModifier));

						damage.insert(pos, str);

						m_Attacks.push_back(Attack(it.first, attackBonus, damage));
					}
				}
			}
			if (m_Race == "Dragonborn")
			{
				std::vector<std::string> dragonTypes = { "black", "blue", "brass", "bronze", "copper", "gold", "green", "red", "silver", "white" };
				std::string type = dragonTypes[Random::Index(0, dragonTypes.size() - 1)];
				std::string attackName = "breath weapon (" + type + ")";
				// TODO: Breath weapon damage increases at certain levels
				std::string damage = "2d6 " + BreathWeaponTypes.at(type);
				m_Attacks.push_back(Attack(attackName, 0, damage));
			}
		}

		// Determine armor class by finding the armor in the character's equipment that has the highest armor class
		{
			// If result.second remains 10 after all the for loops, then the character is unarmored
			std::pair<std::string, int> result = { "", 10 };

			for (const auto& it : LightArmorClasses)
			{
				if (m_Equipment.contains(it.first) && it.second >= result.second)
					result = it;
			}

			for (const auto& it : MediumArmorClasses)
			{
				if (m_Equipment.contains(it.first) && it.second >= result.second)
					result = it;
			}

			for (const auto& it : HeavyArmorClasses)
			{
				if (m_Equipment.contains(it.first) && it.second >= result.second)
					result = it;
			}

			m_ArmorClass += result.second;
			if (LightArmorClasses.contains(result.first))
				m_ArmorClass += m_Dexterity.Modifier;
			else if (MediumArmorClasses.contains(result.first))
				m_ArmorClass += std::min(2, m_Dexterity.Modifier);
			else if (result.second == 10)
			{
				// Every unarmored character adds their dex modifier, but some classes gain additional benefits
				m_ArmorClass += m_Dexterity.Modifier;

				if (m_Class == "Barbarian")
					m_ArmorClass += m_Constitution.Modifier;
				if (m_Class == "Monk")
				{
					m_ArmorClass += m_Wisdom.Modifier;

					// Monks cannot benefit use a shield and still benefit from their Unarmored Defense trait
					if (m_Equipment.contains("shield")) m_ArmorClass -= 2;
				}
				if (m_Class == "Sorcerer")
				{
					for (const auto& it : m_FeatsAndTraits)
					{

						if (it.Name == "Draconic Resilience")
						{
							m_ArmorClass = 13 + m_Dexterity.Modifier;
							break;
						}
					}
				}
			}

			if (m_Equipment.contains("shield"))
				m_ArmorClass += 2;
		}

		// Sort out proficiency lists
		{
			// If the character is proficient in all items in a category, replace the individual proficiencies with one that encompasses the category
			if (m_ArmorProficiencies.contains("light armor") && m_ArmorProficiencies.contains("medium armor") && m_ArmorProficiencies.contains("heavy armor"))
			{
				m_ArmorProficiencies.erase("light armor");
				m_ArmorProficiencies.erase("medium armor");
				m_ArmorProficiencies.erase("heavy armor");
				m_ArmorProficiencies.insert("all armor");
			}

			auto setContainsVec = [](const std::set<std::string>& s, const std::vector<std::string>& v) -> bool
			{
				int count = 0;
				for (const auto& it : v)
				{
					if (s.contains(it))
						count++;
				}
				return count == v.size();
			};

			if (setContainsVec(m_WeaponProficiencies, AllSimpleWeapons))
			{
				for (const auto& it : AllSimpleWeapons)
					m_WeaponProficiencies.erase(it);

				m_WeaponProficiencies.insert("all simple weapons");
			}

			if (setContainsVec(m_WeaponProficiencies, AllMartialWeapons))
			{
				for (const auto& it : AllMartialWeapons)
					m_WeaponProficiencies.erase(it);

				m_WeaponProficiencies.insert("all martial weapons");
			}

			// All proficiencies should be plural
			// Some words like armor, tools, supplies, and vehicles are already plural
			{
				auto it = m_WeaponProficiencies.begin();
				while (it != m_WeaponProficiencies.end())
				{
					std::string item = *it;
					if (item.find("weapons") == std::string::npos)
					{
						it = m_WeaponProficiencies.erase(it);
						m_WeaponProficiencies.insert(item + "s");
					}
					else it++;
				}
			}

			auto it = m_ToolProficiencies.begin();
			std::vector<std::string> exceptions = { "bagpipes", "supplies", "tools", "vehicles" };
			while (it != m_ToolProficiencies.end())
			{
				std::string item = *it;
				if (foundException(item, exceptions))
				{
					it = m_ToolProficiencies.erase(it);
					m_ToolProficiencies.insert(item + "s");
				}
				else it++;
			}
		}
	}	

	// Temporary
	void Character::DisplayCharacterSheet()
	{
		std::cout << std::boolalpha;

		if (m_Race == "Dragonborn")
			std::cout << "Name: " << m_Surname << " " << m_FirstName << "\n";
		else
			std::cout << "Name: "   << m_FirstName << " " << m_Surname << "\n";

		std::cout << "Gender: " << m_Gender    << "\n";
		std::cout << "Race: "   << m_Race      << "\n";

		if (m_Race == "Human")
			std::cout << "Ethnicity: " << m_Ethnicity << "\n";

		std::cout << "Class: "              << m_Class             << "\n";
		std::cout << "Level: "              << m_Level             << "\n";
		std::cout << "Experience Points: "  << m_Experience        << "\n";
		std::cout << "Proficiency Bonus: "  << m_ProficiencyBonus  << "\n";
		std::cout << "Hit Points: "         << m_MaxHitPoints      << "\n";
		std::cout << "Armor Class: "        << m_ArmorClass        << "\n";
		std::cout << "Speed: "              << m_Speed             << " feet\n";
		std::cout << "Initiative: "         << m_Initiative        << "\n";
		std::cout << "Background: "         << m_Background        << "\n";
		std::cout << "Alignment: "          << m_Alignment         << "\n\n";
		std::cout << "Personality Traits: " << m_PersonalityTraits << "\n\n";
		std::cout << "Ideals: "             << m_Ideals            << "\n\n";
		std::cout << "Bonds: "              << m_Bonds             << "\n\n";
		std::cout << "Flaws: "              << m_Flaws             << "\n\n";

		std::cout << "========\n";
		std::cout << "Abilites\n";
		std::cout << "========\n";
		std::cout << "Strength\n";
		std::cout << "Score:    " << m_Strength.Score    << "\n";
		std::cout << "Modifier: " << m_Strength.Modifier << "\n\n";
		std::cout << "Dexterity\n";
		std::cout << "Score:    " << m_Dexterity.Score    << "\n";
		std::cout << "Modifier: " << m_Dexterity.Modifier << "\n\n";
		std::cout << "Constitution\n";
		std::cout << "Score:    " << m_Constitution.Score    << "\n";
		std::cout << "Modifier: " << m_Constitution.Modifier << "\n\n";
		std::cout << "Intelligence\n";
		std::cout << "Score:    " << m_Intelligence.Score    << "\n";
		std::cout << "Modifier: " << m_Intelligence.Modifier << "\n\n";
		std::cout << "Wisdom\n";
		std::cout << "Score:    " << m_Wisdom.Score    << "\n";
		std::cout << "Modifier: " << m_Wisdom.Modifier << "\n\n";
		std::cout << "Charisma\n";
		std::cout << "Score:    " << m_Charisma.Score    << "\n";
		std::cout << "Modifier: " << m_Charisma.Modifier << "\n\n";

		std::cout << "=============\n";
		std::cout << "Saving Throws\n";
		std::cout << "=============\n";
		std::cout << "Proficiencies\n";
		std::cout << "Strength:     " << m_StrengthSave.Proficient     << "\n";
		std::cout << "Dexterity:    " << m_DexteritySave.Proficient    << "\n";
		std::cout << "Constitution: " << m_ConstitutionSave.Proficient << "\n";
		std::cout << "Intelligence: " << m_IntelligenceSave.Proficient << "\n";
		std::cout << "Wisdom:       " << m_WisdomSave.Proficient       << "\n";
		std::cout << "Charisma:     " << m_CharismaSave.Proficient     << "\n\n";
		std::cout << "Modifiers\n";
		std::cout << "Strength:     " << m_StrengthSave.Modifier     << "\n";
		std::cout << "Dexterity:    " << m_DexteritySave.Modifier    << "\n";
		std::cout << "Constitution: " << m_Constitution.Modifier     << "\n";
		std::cout << "Intelligence: " << m_IntelligenceSave.Modifier << "\n";
		std::cout << "Wisdom:       " << m_WisdomSave.Modifier       << "\n";
		std::cout << "Charisma:     " << m_CharismaSave.Modifier     << "\n\n";

		std::cout << "======\n";
		std::cout << "Skills\n";
		std::cout << "======\n";
		std::cout << "Proficiencies\n";
		std::cout << "Acrobatics:      " << m_Acrobatics.Proficient     << "\n";
		std::cout << "Animal Handling: " << m_AnimalHandling.Proficient << "\n";
		std::cout << "Arcana:          " << m_Arcana.Proficient         << "\n";
		std::cout << "Athletics:       " << m_Athletics.Proficient      << "\n";
		std::cout << "Deception:       " << m_Deception.Proficient      << "\n";
		std::cout << "History:         " << m_History.Proficient        << "\n";
		std::cout << "Insight:         " << m_Insight.Proficient        << "\n";
		std::cout << "Intimidation:    " << m_Intimidation.Proficient   << "\n";
		std::cout << "Investigation:   " << m_Investigation.Proficient  << "\n";
		std::cout << "Medicine:        " << m_Medicine.Proficient       << "\n";
		std::cout << "Nature:          " << m_Nature.Proficient         << "\n";
		std::cout << "Perception:      " << m_Perception.Proficient     << "\n";
		std::cout << "Performance:     " << m_Performance.Proficient    << "\n";
		std::cout << "Persuasion:      " << m_Persuasion.Proficient     << "\n";
		std::cout << "Religion:        " << m_Religion.Proficient       << "\n";
		std::cout << "Sleight of Hand: " << m_SleightOfHand.Proficient  << "\n";
		std::cout << "Stealth:         " << m_Stealth.Proficient        << "\n";
		std::cout << "Survival:        " << m_Survival.Proficient       << "\n\n";

		std::cout << "Modifiers\n";
		std::cout << "Acrobatics:      " << m_Acrobatics.Modifier     << "\n";
		std::cout << "Animal Handling: " << m_AnimalHandling.Modifier << "\n";
		std::cout << "Arcana:          " << m_Arcana.Modifier         << "\n";
		std::cout << "Athletics:       " << m_Athletics.Modifier      << "\n";
		std::cout << "Deception:       " << m_Deception.Modifier      << "\n";
		std::cout << "History:         " << m_History.Modifier        << "\n";
		std::cout << "Insight:         " << m_Insight.Modifier        << "\n";
		std::cout << "Intimidation:    " << m_Intimidation.Modifier   << "\n";
		std::cout << "Investigation:   " << m_Investigation.Modifier  << "\n";
		std::cout << "Medicine:        " << m_Medicine.Modifier       << "\n";
		std::cout << "Nature:          " << m_Nature.Modifier         << "\n";
		std::cout << "Perception:      " << m_Perception.Modifier     << "\n";
		std::cout << "Performance:     " << m_Performance.Modifier    << "\n";
		std::cout << "Persuasion:      " << m_Persuasion.Modifier     << "\n";
		std::cout << "Religion:        " << m_Religion.Modifier       << "\n";
		std::cout << "Sleight of Hand: " << m_SleightOfHand.Modifier  << "\n";
		std::cout << "Stealth:         " << m_Stealth.Modifier        << "\n";
		std::cout << "Survival:        " << m_Survival.Modifier       << "\n\n";

		std::cout << "Passive Wisdom (Perception): " << m_PassiveWisdom << "\n\n";

		std::cout << "===========================\n";
		std::cout << "Proficiencies and Languages\n";
		std::cout << "===========================\n";
		std::cout << "Proficiencies: ";
		for (const auto& it : m_ArmorProficiencies)
			std::cout << it << ", ";

		for (const auto& it : m_WeaponProficiencies)
			std::cout << it << ", ";

		for (const auto& it : m_ToolProficiencies)
		{ 
			std::cout << it;
			if (it != *m_ToolProficiencies.rbegin())
				std::cout << ", ";
		}
		std::cout << "\n\n";

		std::cout << "Languages: ";
		for (const auto& it : m_Languages)
		{
			std::cout << it;
			if (it != *m_Languages.rbegin())
				std::cout << ", ";
		}
		std::cout << "\n\n";

		std::cout << "======================\n";
		std::cout << "Attacks & Spellcasting\n";
		std::cout << "======================\n";
		if (!m_Attacks.empty())
		{
			for (size_t i = 0; i < m_Attacks.size(); i++)
			{
				if (m_Attacks[i].AttackBonus >= 0)
					std::cout << m_Attacks[i].Name << "  +" << m_Attacks[i].AttackBonus << "  " << m_Attacks[i].Damage << "\n";
				else
					std::cout << m_Attacks[i].Name << "  " << m_Attacks[i].AttackBonus << "  " << m_Attacks[i].Damage << "\n";
			}
			std::cout << "\n";
		}

		if (!m_Cantrips.empty())
		{
			std::cout << "Cantrips: ";
			for (const auto& it : m_Cantrips)
			{
				std::cout << it;
				if (it != *m_Cantrips.rbegin())
					std::cout << ", ";
			}
			std::cout << "\n\n";
		}

		if (m_SpellSlots > 0)
			std::cout << "Spell Slots. You have " << m_SpellSlots << " 1st-level spell slots you can use to cast your spells.\n\n";

		if (m_Class == "Bard" || m_Class == "Sorcerer" || m_Class == "Warlock")
		{
			std::cout << "Spells Known: ";
			for (const auto& it : m_Spells)
			{
				std::cout << it;
				if (it != *m_Spells.rbegin())
					std::cout << ", ";
			}
			std::cout << "\n\n";
		}

		if (m_Class == "Cleric")
		{
			std::cout << "Prepared Spells. You prepare " << m_SpellsPrepared << " 1st-level spells to make them available to you to cast, choosing from the "
				      << m_Class << " spell list in the rulebook. In addition, you always have " << m_Spells.size() << " domain spells prepared: ";
			for (const auto& it : m_Spells)
			{
				std::cout << it;
				if (it != *m_Spells.rbegin())
					std::cout << ", ";
				else 
					std::cout << ".";
			}
			std::cout << "\n\n";
		}
		else if (m_Class == "Druid")
		{
			std::cout << "Prepared Spells. You prepare " << m_SpellsPrepared << " 1st-level spells to make them available to you to cast, choosing from the "
				      << m_Class << " spell list in the rulebook.\n\n";
		}
		else if (m_Class == "Wizard")
		{
			std::cout << "Prepared Spells. You prepare " << m_SpellsPrepared
				<< " 1st-level spells to make them available to you to cast, choosing from the spells in your spellbook.\n\n";
			std::set<std::string> spellbook;
			for (int i = 0; i < 6; i++)
			{
				std::string spell = SpellLists.at("Wizard")[Random::Index(0, SpellLists.at("Wizard").size() - 1)];
				while (spellbook.contains(spell))
					spell = SpellLists.at("Wizard")[Random::Index(0, SpellLists.at("Wizard").size() - 1)];

				spellbook.insert(spell);
			}

			std::cout << "Spellbook. You have a spellbook containing these 1st-level spells: ";
			for (const auto& it : spellbook)
			{
				if (it != *spellbook.rbegin())
					std::cout << it << ", ";
				else
					std::cout << " and " << it << ".";
			}
			std::cout << "\n\n";
		}

		std::cout << "=================\n";
		std::cout << "Features & Traits\n";
		std::cout << "=================\n";
		for (size_t i = 0; i < m_FeatsAndTraits.size(); i++)
			std::cout << m_FeatsAndTraits[i].Name + ". " + m_FeatsAndTraits[i].Description + "\n\n";

		std::cout << "=========\n";
		std::cout << "Equipment\n";
		std::cout << "=========\n";
		// Format equipment list
		{
			// Incredibly naive solution for resolving articles for now. Will improve as needed
			auto isVowel = [](std::string c) -> bool
			{
				return (c == "a" || c == "e" || c == "i" || c == "o" || c == "u");
			};

			// Some items, especially trinkets, are singular but should not have "a" or "an" added before them
			std::vector<std::string> singularExceptions = { "armor", "half", "mail", "two", "vestments" };
			for (const auto& it : m_Equipment)
			{
				// If the character has only one of a particular item
				if (it.second == 1)
				{
					// "the is also an exception, but only if it starts the string
					if (foundException(it.first, singularExceptions) || it.first.substr(0, 3) == "the")
						std::cout << it.first;
					else if (isVowel(it.first.substr(0, 1)) || it.first == "herbalism kit")
						std::cout << "an " << it.first;
					else
						std::cout << "a " << it.first;
				}
				else if (it.second > 1)
				{
					if (it.first.substr(0, 3) == "set")
						std::cout << it.second << " " << it.first.substr(0, 3) << "s " << it.first.substr(4);
					else if (it.first.substr(0, 5) == "stick")
						std::cout << it.second << " " << it.first.substr(0, 5) << "s " << it.first.substr(6);
					else if (it.first.ends_with("supplies"))
						std::cout << it.second << " " << it.first;
					else
						std::cout << it.second << " " << it.first << "s";
				}

				if (it != *m_Equipment.rbegin())
					std::cout << ", ";
			}
			std::cout << "\n\n";
		}

		std::cout << "CP: " << m_CopperPieces   << "\n";
		std::cout << "SP: " << m_SilverPieces   << "\n";
		std::cout << "EP: " << m_ElectrumPieces << "\n";
		std::cout << "GP: " << m_GoldPieces     << "\n";
		std::cout << "PP: " << m_PlatinumPieces << "\n\n";
	}
}
