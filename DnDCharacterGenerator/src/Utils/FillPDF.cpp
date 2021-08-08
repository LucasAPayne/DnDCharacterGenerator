#include "FillPDF.h"
#include "Character/Lists.h"
#include "Utils/FDF.h"
#include "Utils/Random.h"

bool foundException(const std::string& str, const std::vector<std::string>& exceptionList)
{
	for (size_t i = 0; i < exceptionList.size(); i++)
	{
		if (str.find(exceptionList[i]) != std::string::npos)
			return true;
	}
	return false;
}

// Naive solution for resolving articles for now. Will improve as needed
bool isVowel(char c)
{
	return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

void fillCharacterSheet_1Page(dnd::Character character)
{
	FDF fdf("assets/scripts/CharacterSheet_1Page.fdf", "../templates/CharacterSheet_1Page.pdf");

	// Top
	if (character.m_Race == "Dragonborn")
		fdf.WriteTextField("CharacterName", character.m_Surname + " " + character.m_FirstName);
	else
		fdf.WriteTextField("CharacterName", character.m_FirstName + " " + character.m_Surname);

	fdf.WriteTextField("ClassLevel", character.m_Class + " " + std::to_string(character.m_Level));
	fdf.WriteTextField("Background", character.m_Background);
	fdf.WriteTextField("PlayerName", character.m_PlayerName);
	fdf.WriteTextField("Race", character.m_Race);
	fdf.WriteTextField("Alignment", character.m_Alignment);
	fdf.WriteTextField("XP", std::to_string(character.m_Experience));

	// Abilities
	fdf.WriteTextField("Strength", std::to_string(character.m_Strength.Score));
	fdf.WriteTextField("Dexterity", std::to_string(character.m_Dexterity.Score));
	fdf.WriteTextField("Constitution", std::to_string(character.m_Constitution.Score));
	fdf.WriteTextField("Intelligence", std::to_string(character.m_Intelligence.Score));
	fdf.WriteTextField("Wisdom", std::to_string(character.m_Wisdom.Score));
	fdf.WriteTextField("Charisma", std::to_string(character.m_Charisma.Score));

	// Ability Modifiers
	fdf.WriteTextField("StrengthModifier", std::to_string(character.m_Strength.Modifier));
	fdf.WriteTextField("DexterityModifier", std::to_string(character.m_Dexterity.Modifier));
	fdf.WriteTextField("ConstitutionModifier", std::to_string(character.m_Constitution.Modifier));
	fdf.WriteTextField("IntelligenceModifier", std::to_string(character.m_Intelligence.Modifier));
	fdf.WriteTextField("WisdomModifier", std::to_string(character.m_Wisdom.Modifier));
	fdf.WriteTextField("CharismaModifier", std::to_string(character.m_Charisma.Modifier));

	// Saving Throws
	fdf.WriteTextField("StrengthSave", std::to_string(character.m_StrengthSave.Modifier));
	fdf.WriteTextField("DexteritySave", std::to_string(character.m_DexteritySave.Modifier));
	fdf.WriteTextField("ConstitutionSave", std::to_string(character.m_ConstitutionSave.Modifier));
	fdf.WriteTextField("IntelligenceSave", std::to_string(character.m_IntelligenceSave.Modifier));
	fdf.WriteTextField("WisdomSave", std::to_string(character.m_WisdomSave.Modifier));
	fdf.WriteTextField("CharismaSave", std::to_string(character.m_CharismaSave.Modifier));

	// Saving Throw Checkboxes
	fdf.WriteCheckbox("StrengthSaveCheck", character.m_StrengthSave.Proficient);
	fdf.WriteCheckbox("DexteritySaveCheck", character.m_DexteritySave.Proficient);
	fdf.WriteCheckbox("ConstitutionSaveCheck", character.m_ConstitutionSave.Proficient);
	fdf.WriteCheckbox("IntelligenceSaveCheck", character.m_IntelligenceSave.Proficient);
	fdf.WriteCheckbox("WisdomSaveCheck", character.m_WisdomSave.Proficient);
	fdf.WriteCheckbox("CharismaSaveCheck", character.m_CharismaSave.Proficient);

	// Skills
	fdf.WriteTextField("Acrobatics", std::to_string(character.m_Acrobatics.Modifier));
	fdf.WriteTextField("AnimalHandling", std::to_string(character.m_AnimalHandling.Modifier));
	fdf.WriteTextField("Arcana", std::to_string(character.m_Arcana.Modifier));
	fdf.WriteTextField("Athletics", std::to_string(character.m_Athletics.Modifier));
	fdf.WriteTextField("Deception", std::to_string(character.m_Deception.Modifier));
	fdf.WriteTextField("History", std::to_string(character.m_History.Modifier));
	fdf.WriteTextField("Insight", std::to_string(character.m_Insight.Modifier));
	fdf.WriteTextField("Intimidation", std::to_string(character.m_Intimidation.Modifier));
	fdf.WriteTextField("Investigation", std::to_string(character.m_Investigation.Modifier));
	fdf.WriteTextField("Medicine", std::to_string(character.m_Medicine.Modifier));
	fdf.WriteTextField("Nature", std::to_string(character.m_Nature.Modifier));
	fdf.WriteTextField("Perception", std::to_string(character.m_Perception.Modifier));
	fdf.WriteTextField("Performance", std::to_string(character.m_Performance.Modifier));
	fdf.WriteTextField("Persuasion", std::to_string(character.m_Persuasion.Modifier));
	fdf.WriteTextField("Religion", std::to_string(character.m_Religion.Modifier));
	fdf.WriteTextField("SleightOfHand", std::to_string(character.m_SleightOfHand.Modifier));
	fdf.WriteTextField("Stealth", std::to_string(character.m_Stealth.Modifier));
	fdf.WriteTextField("Survival", std::to_string(character.m_Survival.Modifier));

	// Skill Checkboxes
	fdf.WriteCheckbox("AcrobaticsCheck", character.m_Acrobatics.Proficient);
	fdf.WriteCheckbox("AnimalHandlingCheck", character.m_AnimalHandling.Proficient);
	fdf.WriteCheckbox("ArcanaCheck", character.m_Arcana.Proficient);
	fdf.WriteCheckbox("AthleticsCheck", character.m_Athletics.Proficient);
	fdf.WriteCheckbox("DeceptionCheck", character.m_Deception.Proficient);
	fdf.WriteCheckbox("HistoryCheck", character.m_History.Proficient);
	fdf.WriteCheckbox("InsightCheck", character.m_Insight.Proficient);
	fdf.WriteCheckbox("IntimidationCheck", character.m_Intimidation.Proficient);
	fdf.WriteCheckbox("InvestigationCheck", character.m_Investigation.Proficient);
	fdf.WriteCheckbox("MedicineCheck", character.m_Medicine.Proficient);
	fdf.WriteCheckbox("NatureCheck", character.m_Nature.Proficient);
	fdf.WriteCheckbox("PerceptionCheck", character.m_Perception.Proficient);
	fdf.WriteCheckbox("PerformanceCheck", character.m_Performance.Proficient);
	fdf.WriteCheckbox("PersuasionCheck", character.m_Persuasion.Proficient);
	fdf.WriteCheckbox("ReligionCheck", character.m_Religion.Proficient);
	fdf.WriteCheckbox("SleightOfHandCheck", character.m_SleightOfHand.Proficient);
	fdf.WriteCheckbox("StealthCheck", character.m_Stealth.Proficient);
	fdf.WriteCheckbox("SurvivalCheck", character.m_Survival.Proficient);

	// Combat
	fdf.WriteTextField("ArmorClass", std::to_string(character.m_ArmorClass));
	fdf.WriteTextField("Initiative", std::to_string(character.m_Initiative));
	fdf.WriteTextField("Speed", std::to_string(character.m_Speed));
	fdf.WriteTextField("HitPointsMax", std::to_string(character.m_HitPointsMax));
	fdf.WriteTextField("HitPointsCurrent", std::to_string(character.m_HitPointsCurrent));
	fdf.WriteTextField("HitPointsTemp", std::to_string(character.m_HitPointsTemp));
	fdf.WriteTextField("HitDiceTotal", std::to_string(character.m_HitDice.Number));
	fdf.WriteTextField("HitDice", "d" + std::to_string(character.m_HitDice.Type));

	fdf.WriteCheckbox("Successes1", false);
	fdf.WriteCheckbox("Successes2", false);
	fdf.WriteCheckbox("Successes3", false);
	fdf.WriteCheckbox("Failures1", false);
	fdf.WriteCheckbox("Failures2", false);
	fdf.WriteCheckbox("Failures3", false);

	if (character.m_Attacks.size() > 0)
	{
		fdf.WriteTextField("Weapon1Name", character.m_Attacks[0].Name);
		fdf.WriteTextField("Weapon1AtkBonus", "+" + std::to_string(character.m_Attacks[0].AttackBonus));
		fdf.WriteTextField("Weapon1Damage", character.m_Attacks[0].Damage);
	}
	if (character.m_Attacks.size() > 1)
	{
		fdf.WriteTextField("Weapon2Name", character.m_Attacks[1].Name);
		fdf.WriteTextField("Weapon2AtkBonus", "+" + std::to_string(character.m_Attacks[1].AttackBonus));
		fdf.WriteTextField("Weapon2Damage", character.m_Attacks[1].Damage);
	}
	if (character.m_Attacks.size() > 2)
	{
		fdf.WriteTextField("Weapon3Name", character.m_Attacks[2].Name);
		fdf.WriteTextField("Weapon3AtkBonus", "+" + std::to_string(character.m_Attacks[2].AttackBonus));
		fdf.WriteTextField("Weapon3Damage", character.m_Attacks[2].Damage);
	}

	std::string attacksSpellcasting;

	if (!character.m_Cantrips.empty())
	{
		attacksSpellcasting += "Cantrips. You know ";

		for (const auto& it : character.m_Cantrips)
		{
			attacksSpellcasting += it;
			if (it != *character.m_Cantrips.rbegin() && character.m_Cantrips.size() > 2)
				attacksSpellcasting += ", ";
			else if (it != *character.m_Cantrips.rbegin() && character.m_Cantrips.size() == 2)
				attacksSpellcasting += " and ";
		}

		if (character.m_Cantrips.size() == 2)
			attacksSpellcasting += " and can cast them at will.";
		else if (character.m_Cantrips.size() > 2)
		{
			attacksSpellcasting.insert(attacksSpellcasting.find_last_of(",") + 1, " and");
			attacksSpellcasting += " and can cast them at will.";
		}
		else
			attacksSpellcasting += " and can cast it at will.";

		attacksSpellcasting += "\n\n";
	}

	if (dnd::lists::SpellLists.contains(character.m_Class))
	{
		if (character.m_SpellSlots > 1)
			attacksSpellcasting += "Spells Slots. You have " + std::to_string(character.m_SpellSlots) + " 1st-level spell slots you can use to cast your spells.";
		else
			attacksSpellcasting += "Spells Slots. You have " + std::to_string(character.m_SpellSlots) + " 1st-level spell slot you can use to cast your spells.";
	}

	if (character.m_Class == "Bard" || character.m_Class == "Sorcerer" || character.m_Class == "Warlock")
	{
		attacksSpellcasting += "Spells Known: ";
		for (const auto& it : character.m_Spells)
		{
			attacksSpellcasting += it;
			if (it != *character.m_Spells.rbegin())
				attacksSpellcasting += ", ";
		}
		attacksSpellcasting += "\n\n";
	}
	else if (character.m_Class == "Cleric" || character.m_Class == "Druid")
	{
		attacksSpellcasting += "Prepared Spells. You prepare " + std::to_string(character.m_SpellsPrepared) + " 1st-level ";

		if (character.m_SpellsPrepared > 1)
			attacksSpellcasting += "spells to make them ";
		else
			attacksSpellcasting += "spell to make it ";

		attacksSpellcasting += "available to you to cast, choosing from the " + character.m_Class + " spell list in the rulebook.";

		if (character.m_Class == "Cleric")
		{
			attacksSpellcasting += " In addition, you always have " + std::to_string(character.m_Spells.size()) + " domain ";
			if (character.m_Spells.size() > 1)
				attacksSpellcasting += "spells ";
			else
				attacksSpellcasting += "spell ";

			attacksSpellcasting += "prepared: ";

			for (const auto& it : character.m_Spells)
			{
				attacksSpellcasting += it;
				if (it != *character.m_Spells.rbegin() && character.m_Spells.size() > 2)
					attacksSpellcasting += ", ";
				else if (it != *character.m_Spells.rbegin() && character.m_Spells.size() == 2)
					attacksSpellcasting += " and ";
				if (it == *character.m_Spells.rbegin())
					attacksSpellcasting += ".";
			}

			if (character.m_Spells.size() > 2)
				attacksSpellcasting.insert(attacksSpellcasting.find_last_of(",") + 1, " and");
		}
		attacksSpellcasting += "\n\n";
	}
	else if (character.m_Class == "Wizard")
	{
		attacksSpellcasting += "Prepared Spells.You prepare " + std::to_string(character.m_SpellsPrepared) + " 1st-level ";

		if (character.m_SpellsPrepared > 1)
			attacksSpellcasting += "spells to make them ";
		else
			attacksSpellcasting += "spell to make it ";

		attacksSpellcasting += "availale to you to cast, choosing from the spells in your spellbook.\n\n";

		// At 1st level, wizards have a spellbook containing 6 spells from the wizard spell list
		std::set<std::string> spellbook;
		for (int i = 0; i < 6; i++)
		{
			std::string spell = dnd::lists::SpellLists.at("Wizard")[Random::Index(0, dnd::lists::SpellLists.at("Wizard").size() - 1)];

			// Make sure the spell is unique
			while (spellbook.contains(spell))
				spell = dnd::lists::SpellLists.at("Wizard")[Random::Index(0, dnd::lists::SpellLists.at("Wizard").size() - 1)];

			spellbook.insert(spell);
		}

		attacksSpellcasting += "Spellbook. You have a spellbook containing these 1st-level spells: ";
		for (const auto& it : spellbook)
		{
			if (it != *spellbook.rbegin())
				attacksSpellcasting += it + ", ";
			else
				attacksSpellcasting += "and " + it + ".";
		}
	}

	fdf.WriteTextField("AttacksSpellcasting", attacksSpellcasting);

	// Personality
	fdf.WriteTextField("PersonalityTraits", character.m_PersonalityTraits);
	fdf.WriteTextField("Ideals", character.m_Ideals);
	fdf.WriteTextField("Bonds", character.m_Bonds);
	fdf.WriteTextField("Flaws", character.m_Flaws);

	// Features and Traits
	std::string featsAndTraits;
	for (const auto& it : character.m_FeatsAndTraits)
	{
		featsAndTraits += it.Name + ". " + it.Description;

		if (it.Name != character.m_FeatsAndTraits.back().Name)
			featsAndTraits += "\n\n";
	}

	fdf.WriteTextField("FeaturesTraits", featsAndTraits);

	// Proficiencies
	std::string proficiencies = "Proficiencies. ";
	std::vector<std::string> pluralExceptions = { "bagpipes", "supplies", "tools", "vehicles" };

	for (const auto& it : character.m_ArmorProficiencies)
		proficiencies += it + ", ";

	for (const auto& it : character.m_WeaponProficiencies)
	{
		if (it.find("weapons") == std::string::npos)
			proficiencies += it + "s, ";
		else
			proficiencies += it + ", ";
	}

	for (const auto& it : character.m_ToolProficiencies)
	{
		if (!foundException(it, pluralExceptions))
			proficiencies += it + "s";
		else
			proficiencies += it;

		if (it != *character.m_ToolProficiencies.rbegin())
			proficiencies += ", ";
	}
	proficiencies[15] = std::toupper(proficiencies[15]);

	std::string languages = "Languages. ";
	for (const auto& it : character.m_Languages)
	{
		languages += it;
		if (it != *character.m_Languages.rbegin())
			languages += ", ";
	}

	fdf.WriteTextField("ProficienciesLanguages", proficiencies + "\n\n" + languages);

	// Equipment
	// Some items, especially trinkets, are singular but should not have "a" or "an" added before them
	std::vector<std::string> singularExceptions = { "armor", "half", "mail", "two", "vestments" };
	std::string equipment;
	for (const auto& it : character.m_Equipment)
	{
		// If the character has only one of a particular item
		if (it.second == 1)
		{
			// "the" is also an exception, but only if it starts the string
			if (foundException(it.first, singularExceptions) || it.first.substr(0, 3) == "the")
				equipment += it.first;
			else if (isVowel(it.first[0]) || it.first == "herbalism kit")
				equipment += "an " + it.first;
			else
				equipment += "a " + it.first;
		}
		else if (it.second > 1)
		{
			if (it.first.substr(0, 3) == "set")
				equipment += std::to_string(it.second) + " sets " + it.first.substr(4);
			else if (it.first.substr(0, 5) == "stick")
				equipment += std::to_string(it.second) + " sticks " + it.first.substr(6);
			else if (it.first.ends_with("supplies"))
				equipment += std::to_string(it.second) + " " + it.first;
			else
				equipment += std::to_string(it.second) + " " + it.first + "s";
		}

		if (it != *character.m_Equipment.rbegin())
			equipment += ", ";
	}
	equipment[0] = std::toupper(equipment[0]);

	fdf.WriteTextField("Equipment", equipment);
	fdf.WriteTextField("CP", std::to_string(character.m_CopperPieces));
	fdf.WriteTextField("SP", std::to_string(character.m_SilverPieces));
	fdf.WriteTextField("EP", std::to_string(character.m_ElectrumPieces));
	fdf.WriteTextField("GP", std::to_string(character.m_GoldPieces));
	fdf.WriteTextField("PP", std::to_string(character.m_PlatinumPieces));

	// Other
	fdf.WriteTextField("Inspiration", std::to_string(character.m_Inspiration));
	fdf.WriteTextField("ProficiencyBonus", std::to_string(character.m_ProficiencyBonus));
	fdf.WriteTextField("PassiveWisdom", std::to_string(character.m_PassiveWisdom));
}
