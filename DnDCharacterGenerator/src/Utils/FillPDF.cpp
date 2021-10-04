#include "FillPDF.h"
#include "Character/Character.h"
#include "Character/Lists.h"
#include "Utils/Random.h"

#include <wx/pdfdoc.h>

static bool foundException(const std::string& str, const std::vector<std::string>& exceptionList)
{
	for (size_t i = 0; i < exceptionList.size(); i++)
	{
		if (str.find(exceptionList[i]) != std::string::npos)
			return true;
	}
	return false;
}

// Naive solution for resolving articles for now. Will improve as needed
static bool isVowel(char c)
{
	return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

// Add leading spaces to a string to center the text. The number of spaces is determined by how many spaces fit in the text field
static std::string center(const std::string& input, int width)
{
	return std::string((width - input.length() - 1) / 2, ' ') + input;
}

bool fillCharacterSheetPage1(dnd::Character character)
{
	wxPdfDocument characterSheet(1, "mm", wxPAPER_LETTER);
	characterSheet.SetDisplayMode(wxPDF_ZOOM_REAL);
	characterSheet.SetFont("Helvetica", wxPDF_FONTSTYLE_REGULAR, 8);

	// Initialize character sheet from template
	characterSheet.SetSourceFile("assets/templates/CharacterSheet_1Page.pdf");
	int tpl = characterSheet.ImportPage(1);
	characterSheet.AddPage();
	characterSheet.UseTemplate(tpl);

	// Top
	wxString name;
	if (character.m_Race == "Dragonborn")
		name = character.m_Surname + " " + character.m_FirstName;
	else
		name = character.m_FirstName + " " + character.m_Surname;

	characterSheet.TextField("CharacterName", 16.8, 21.6, 61.0, 7.4, name);
	characterSheet.TextField("ClassLevel", 95.3, 17.0, 37.3, 5.5, character.m_Class + " " + wxString::Format(wxT("%i"), character.m_Level));
	characterSheet.TextField("Background", 135.5, 17.0, 30.4, 5.5, character.m_Background);
	characterSheet.TextField("PlayerName", 169.4, 17.0, 31.8, 5.5, character.m_PlayerName);
	characterSheet.TextField("Race", 95.3, 26.2, 37.3, 5.5, character.m_Race);
	characterSheet.TextField("Alignment", 135.5, 26.2, 30.4, 5.5, character.m_Alignment);
	characterSheet.TextField("XP", 169.4, 26.2, 31.8, 5.5, wxString::Format(wxT("%i"), character.m_Experience));

	// Abilities
	characterSheet.SetFontSize(6);
	characterSheet.TextField("StrengthModifier", 16.4, 65.9, 7.49, 4.5, center(std::to_string(character.m_Strength.Score), 10));
	characterSheet.TextField("DexterityModifier", 16.4, 91.3, 7.49, 4.5, center(std::to_string(character.m_Dexterity.Score), 10));
	characterSheet.TextField("ConstitutionModifier", 16.4, 116.4, 7.49, 4.5, center(std::to_string(character.m_Constitution.Score), 10));
	characterSheet.TextField("IntelligenceModifier", 16.4, 141.8, 7.49, 4.5, center(std::to_string(character.m_Intelligence.Score), 10));
	characterSheet.TextField("WisdomModifier", 16.4, 167.0, 7.5, 4.49, center(std::to_string(character.m_Wisdom.Score), 10));
	characterSheet.TextField("CharismaModifier", 16.4, 192.1, 7.49, 4.5, center(std::to_string(character.m_Charisma.Score), 10));

	// Ability Modifiers
	characterSheet.SetFontSize(8);
	characterSheet.TextField("Strength", 13.0, 54.4, 14.5, 9.0,
		center((character.m_Strength.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Strength.Modifier), 16));
	characterSheet.TextField("Dexterity", 13.0, 79.9, 14.5, 9.0,
		center((character.m_Dexterity.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Dexterity.Modifier), 16));
	characterSheet.TextField("Constitution", 13.0, 104.9, 14.5, 9.0,
		center((character.m_Constitution.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Constitution.Modifier), 16));
	characterSheet.TextField("Intelligence", 13.0, 130.3, 14.5, 9.0,
		center((character.m_Intelligence.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Intelligence.Modifier), 16));
	characterSheet.TextField("Wisdom", 13.0, 155.5, 14.5, 9.0,
		center((character.m_Wisdom.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Wisdom.Modifier), 16));
	characterSheet.TextField("Charisma", 13.0, 180.6, 14.5, 9.0,
		center((character.m_Charisma.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Charisma.Modifier), 16));

	// Saving Throws
	characterSheet.TextField("StrengthSave", 39.8, 72.9, 5.1, 3.0,
		center((character.m_StrengthSave.Modifier >= 0 ? "+" : "") + std::to_string(character.m_StrengthSave.Modifier), 6));
	characterSheet.TextField("DexteritySave", 39.8, 77.6, 5.1, 3.0,
		center((character.m_DexteritySave.Modifier >= 0 ? "+" : "") + std::to_string(character.m_DexteritySave.Modifier), 6));
	characterSheet.TextField("ConstitutionSave", 39.8, 82.4, 5.1, 3.0,
		center((character.m_ConstitutionSave.Modifier >= 0 ? "+" : "") + std::to_string(character.m_ConstitutionSave.Modifier), 6));
	characterSheet.TextField("IntelligenceSave", 39.8, 87.2, 5.1, 3.0,
		center((character.m_DexteritySave.Modifier >= 0 ? "+" : "") + std::to_string(character.m_DexteritySave.Modifier), 6));
	characterSheet.TextField("WisdomSave", 39.8, 91.9, 5.1, 3.0,
		center((character.m_WisdomSave.Modifier >= 0 ? "+" : "") + std::to_string(character.m_WisdomSave.Modifier), 6));
	characterSheet.TextField("CharismaSave", 39.8, 96.7, 5.1, 3.0,
		center((character.m_CharismaSave.Modifier >= 0 ? "+" : "") + std::to_string(character.m_CharismaSave.Modifier), 6));

	// Saving Throw Checkboxes
	characterSheet.CheckBox("StrengthSaveCheck", 35.7, 73.4, 2.2, character.m_StrengthSave.Proficient);
	characterSheet.CheckBox("DexteritySaveCheck", 35.7, 78.1, 2.2, character.m_DexteritySave.Proficient);
	characterSheet.CheckBox("ConstitutionSaveCheck", 35.7, 82.9, 2.2, character.m_ConstitutionSave.Proficient);
	characterSheet.CheckBox("IntelligenceSaveCheck", 35.7, 87.6, 2.2, character.m_IntelligenceSave.Proficient);
	characterSheet.CheckBox("WisdomSaveCheck", 35.7, 92.4, 2.2, character.m_WisdomSave.Proficient);
	characterSheet.CheckBox("CharismaSaveCheck", 35.7, 97.2, 2.2, character.m_CharismaSave.Proficient);

	// Skills
	characterSheet.TextField("Acrobatics", 39.5, 113.5, 5.1, 3.0,
		center((character.m_Acrobatics.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Acrobatics.Modifier), 6));
	characterSheet.TextField("AnimalHandling", 39.5, 118.3, 5.1, 3.0,
		center((character.m_AnimalHandling.Modifier >= 0 ? "+" : "") + std::to_string(character.m_AnimalHandling.Modifier), 6));
	characterSheet.TextField("Arcana", 39.5, 123.0, 5.1, 3.0,
		center((character.m_Arcana.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Arcana.Modifier), 6));
	characterSheet.TextField("Athletics", 39.5, 127.8, 5.1, 3.0,
		center((character.m_Athletics.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Athletics.Modifier), 6));
	characterSheet.TextField("Deception", 39.5, 132.6, 5.1, 3.0,
		center((character.m_Deception.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Deception.Modifier), 6));
	characterSheet.TextField("History", 39.5, 137.3, 5.1, 3.0,
		center((character.m_History.Modifier >= 0 ? "+" : "") + std::to_string(character.m_History.Modifier), 6));
	characterSheet.TextField("Insight", 39.5, 142.1, 5.1, 3.0,
		center((character.m_Insight.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Insight.Modifier), 6));
	characterSheet.TextField("Intimidation", 39.5, 146.8, 5.1, 3.0,
		center((character.m_Intimidation.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Intimidation.Modifier), 6));
	characterSheet.TextField("Investigation", 39.5, 151.6, 5.1, 3.0,
		center((character.m_Investigation.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Investigation.Modifier), 6));
	characterSheet.TextField("Medicine", 39.5, 156.4, 5.1, 3.0,
		center((character.m_Medicine.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Medicine.Modifier), 6));
	characterSheet.TextField("Nature", 39.5, 161.2, 5.1, 3.0,
		center((character.m_Nature.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Nature.Modifier), 6));
	characterSheet.TextField("Percepction", 39.5, 165.9, 5.1, 3.0,
		center((character.m_Perception.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Perception.Modifier), 6));
	characterSheet.TextField("Performance", 39.5, 170.7, 5.1, 3.0,
		center((character.m_Performance.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Performance.Modifier), 6));
	characterSheet.TextField("Persuasion", 39.5, 175.5, 5.1, 3.0,
		center((character.m_Persuasion.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Persuasion.Modifier), 6));
	characterSheet.TextField("Religion", 39.5, 180.2, 5.1, 3.0,
		center((character.m_Religion.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Religion.Modifier), 6));
	characterSheet.TextField("SleightOfHand", 39.5, 184.9, 5.1, 3.0,
		center((character.m_SleightOfHand.Modifier >= 0 ? "+" : "") + std::to_string(character.m_SleightOfHand.Modifier), 6));
	characterSheet.TextField("Stealth", 39.5, 189.7, 5.1, 3.0,
		center((character.m_Stealth.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Stealth.Modifier), 6));
	characterSheet.TextField("Survival", 39.5, 194.5, 5.1, 3.0,
		center((character.m_Survival.Modifier >= 0 ? "+" : "") + std::to_string(character.m_Survival.Modifier), 6));

	// Skill Checkboxes
	characterSheet.CheckBox("AcrobaticsCheck", 35.7, 114.1, 2.2, character.m_Acrobatics.Proficient);
	characterSheet.CheckBox("AnimalHandlingCheck", 35.7, 118.9, 2.2, character.m_AnimalHandling.Proficient);
	characterSheet.CheckBox("ArcanaCheck", 35.7, 123.6, 2.2, character.m_Arcana.Proficient);
	characterSheet.CheckBox("AthleticsCheck", 35.7, 128.4, 2.2, character.m_Athletics.Proficient);
	characterSheet.CheckBox("DeceptionCheck", 35.7, 133.2, 2.2, character.m_Deception.Proficient);
	characterSheet.CheckBox("HistoryCheck", 35.7, 137.9, 2.2, character.m_History.Proficient);
	characterSheet.CheckBox("InsightCheck", 35.7, 142.7, 2.2, character.m_Insight.Proficient);
	characterSheet.CheckBox("IntimidationCheck", 35.7, 147.4, 2.2, character.m_Intimidation.Proficient);
	characterSheet.CheckBox("InvestigationCheck", 35.7, 152.2, 2.2, character.m_Investigation.Proficient);
	characterSheet.CheckBox("MedicineCheck", 35.7, 157.0, 2.2, character.m_Medicine.Proficient);
	characterSheet.CheckBox("NatureCheck", 35.7, 161.8, 2.2, character.m_Nature.Proficient);
	characterSheet.CheckBox("PerceptionCheck", 35.7, 166.5, 2.2, character.m_Perception.Proficient);
	characterSheet.CheckBox("PerformanceCheck", 35.7, 171.1, 2.2, character.m_Performance.Proficient);
	characterSheet.CheckBox("PersuasionCheck", 35.7, 176.1, 2.2, character.m_Persuasion.Proficient);
	characterSheet.CheckBox("ReligionCheck", 35.7, 180.8, 2.2, character.m_Religion.Proficient);
	characterSheet.CheckBox("SleightOfHandCheck", 35.7, 185.4, 2.2, character.m_SleightOfHand.Proficient);
	characterSheet.CheckBox("StealthCheck", 35.7, 190.2, 2.2, character.m_Stealth.Proficient);
	characterSheet.CheckBox("SurvivalCheck", 35.7, 195.1, 2.2, character.m_Survival.Proficient);

	// Combat
	characterSheet.TextField("ArmorClass", 82.6, 49.6, 9.7, 9.1, center(std::to_string(character.m_ArmorClass), 10));
	characterSheet.TextField("Initiative", 100.9, 49.6, 12.7, 11.7, center("+" + std::to_string(character.m_Initiative), 14));
	characterSheet.TextField("Speed", 121.4, 49.6, 12.7, 11.7, center(std::to_string(character.m_Speed) + " feet", 14));
	characterSheet.TextField("HitPointsMax", 102.6, 69.4, 31.5, 3.8, std::to_string(character.m_HitPointsMax));
	characterSheet.TextField("HitPointsCurrent", 81.6, 75.0, 52.6, 10.7, center(std::to_string(character.m_HitPointsCurrent), 64));
	characterSheet.TextField("HitPointsTemp", 81.6, 93.3, 52.6, 10.7, center(std::to_string(character.m_HitPointsTemp), 64));
	characterSheet.TextField("HitDiceTotal", 87.1, 112.3, 17.0, 3.2, std::to_string(character.m_HitDice.Number));
	characterSheet.TextField("HitDice", 81.8, 116.9, 22.4, 7.4, center("d" + std::to_string(character.m_HitDice.Type), 28));

	characterSheet.CheckBox("Successes1", 122.0, 113.6, 3.3, true);
	characterSheet.CheckBox("Successes2", 126.6, 113.6, 3.3, true);
	characterSheet.CheckBox("Successes3", 131.1, 113.6, 3.3, true);
	characterSheet.CheckBox("Failures1", 122.0, 118.9, 3.3, true);
	characterSheet.CheckBox("Failures2", 126.6, 118.9, 3.3, true);
	characterSheet.CheckBox("Failures3", 131.1, 118.9, 3.3, true);

	characterSheet.TextField("Weapon1Name", 79.0, 138.7, 21.7, 5.0,
		character.m_Attacks.size() > 0 ? character.m_Attacks[0].Name : "");
	characterSheet.TextField("Weapon1AtkBonus", 103.0, 138.7, 10.5, 5.0,
		character.m_Attacks.size() > 0 ? "+" + std::to_string(character.m_Attacks[0].AttackBonus) : "");
	characterSheet.TextField("Weapon1Damage", 115.7, 138.7, 21.5, 5.0,
		character.m_Attacks.size() > 0 ? character.m_Attacks[0].Damage : "");

	characterSheet.TextField("Weapon2Name", 79.0, 145.8, 21.7, 5.0,
		character.m_Attacks.size() > 1 ? character.m_Attacks[1].Name : "");
	characterSheet.TextField("Weapon2AtkBonus", 103.0, 145.8, 10.5, 5.0,
		character.m_Attacks.size() > 1 ? "+" + std::to_string(character.m_Attacks[1].AttackBonus) : "");
	characterSheet.TextField("Weapon2Damage", 115.7, 145.8, 21.5, 5.0,
		character.m_Attacks.size() > 1 ? character.m_Attacks[1].Damage : "");

	characterSheet.TextField("Weapon3Name", 79.0, 153.2, 21.7, 5.0,
		character.m_Attacks.size() > 2 ? character.m_Attacks[2].Name : "");
	characterSheet.TextField("Weapon3AtkBonus", 103.0, 153.2, 10.5, 5.0,
		character.m_Attacks.size() > 2 ? "+" + std::to_string(character.m_Attacks[2].AttackBonus) : "");
	characterSheet.TextField("Weapon3Damage", 115.7, 153.2, 21.5, 5.0,
		character.m_Attacks.size() > 2 ? character.m_Attacks[2].Damage : "");

	// Attacks & Spellcasting
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

	characterSheet.TextField("AttacksSpellcasting", 78.8, 160.1, 58.4, 40.1, attacksSpellcasting, true);

	// Personality
	characterSheet.TextField("PersonalityTraits", 147.7, 49.6, 53.9, 17.1, character.m_PersonalityTraits, true);
	characterSheet.TextField("Ideals", 147.7, 74.0, 53.9, 12.2, character.m_Ideals, true);
	characterSheet.TextField("Bonds", 147.7, 93.5, 53.9, 12.2, character.m_Bonds, true);
	characterSheet.TextField("Flaws", 147.7, 112.8, 53.9, 12.2, character.m_Flaws, true);

	// Features and Traits
	std::string featsAndTraits;
	for (const auto& it : character.m_FeatsAndTraits)
	{
		featsAndTraits += it.Name + ". " + it.Description;

		if (it.Name != character.m_FeatsAndTraits.back().Name)
			featsAndTraits += "\n\n";
	}

	characterSheet.TextField("FeaturesTraits", 145.6, 136.4, 58.2, 130.4, featsAndTraits, true);

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
	// Capitalize the first character of the first proficiency (after the word "Proficiencies. ")
	proficiencies[15] = std::toupper(proficiencies[15]);

	std::string languages = "Languages. ";
	for (const auto& it : character.m_Languages)
	{
		languages += it;
		if (it != *character.m_Languages.rbegin())
			languages += ", ";
	}

	characterSheet.TextField("ProficienciesLanguages", 12.1, 221.3, 58.4, 45.5, proficiencies + "\n\n" + languages, true);

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

	characterSheet.TextField("Equipment", 94.9, 209.4, 42.3, 57.4, equipment, true);
	characterSheet.TextField("CP", 81.0, 211.3, 10.3, 6.2, center(std::to_string(character.m_CopperPieces), 12));
	characterSheet.TextField("SP", 81.0, 220.5, 10.3, 6.2, center(std::to_string(character.m_SilverPieces), 12));
	characterSheet.TextField("EP", 81.0, 229.6, 10.3, 6.2, center(std::to_string(character.m_ElectrumPieces), 12));
	characterSheet.TextField("GP", 81.0, 238.8, 10.3, 6.2, center(std::to_string(character.m_GoldPieces), 12));
	characterSheet.TextField("PP", 81.0, 247.9, 10.3, 6.2, center(std::to_string(character.m_PlatinumPieces), 12));

	// Other
	characterSheet.TextField("Inspiration", 34.2, 46.4, 7.5, 5.8, center(std::to_string(character.m_Inspiration), 8));
	characterSheet.TextField("ProficiencyBonus", 34.2, 59.7, 7.5, 5.8, center(std::to_string(character.m_ProficiencyBonus), 8));
	characterSheet.TextField("PassiveWisdom", 11.6, 208.5, 7.5, 5.8, center(std::to_string(character.m_PassiveWisdom), 8));

	return characterSheet.SaveAsFile("CharacterSheet.pdf");
}
