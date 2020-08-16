#pragma once

#include <string>
#include <vector>

namespace dnd
{
	// The six main abilities: Str, Dex, Con, Int, Wis, Cha
	struct Ability
	{
		int score = 0;
		int modifier = 0;
	};


	// Specific aspects of abilities
	struct Skill
	{
		Ability parent; // The ability that governs the skill
		int modifier = 0;
		bool proficient = false; // Fill in the bubble on character sheet and allows proficiency bonus to be applied to modifier
	};


	struct Trait
	{
		std::string name;
		std::string description;
	};

	// A collection of the different types of coins a character owns
	struct Wealth
	{
		int cp = 0; // copper pieces
		int sp = 0; // silver pieces
		int ep = 0; // electrum pieces
		int gp = 0; // gold pieces
		int pp = 0; // platinum pieces
	};


	struct Attack
	{
		std::string name;
		int atkBonus;
		std::string type;
		std::string damage; // string b/c it's based on die roll, ex. "1d8 + 2"
	};

	// The dice a character's hit points are based on
	struct HitDice
	{
		std::string type; // d6, d8, etc.
		int number = 0;       // How many dice
	};


	struct DeathSaves
	{
		int successes = 0;
		int failures = 0;
	};


	struct Character
	{
		// Descriptors
		std::string playerName;
		std::string firstName;
		std::string surname;
		std::string sex;
		std::string characterClass;
		std::string background;
		std::string race;
		std::string ethnicity; // Only for humans
		std::string alignment;
		std::string personalityTraits;
		std::string ideals;
		std::string bonds;
		std::string flaws;


		// Values
		int level = 0;
		int experience = 0;
		int inspiration = 0;
		int proficiencyBonus = 0;
		int passiveWisdom = 0;


		// Abilities
		Ability strength;
		Ability dexterity;
		Ability constitution;
		Ability intelligence;
		Ability wisdom;
		Ability charisma;


		// Skills
		Skill acrobatics;
		Skill animalHandling;
		Skill arcana;
		Skill athletics;
		Skill deception;
		Skill history;
		Skill insight;
		Skill intimidation;
		Skill investigation;
		Skill medicine;
		Skill nature;
		Skill perception;
		Skill performance;
		Skill persuasion;
		Skill religion;
		Skill sleightOfHand;
		Skill stealth;
		Skill survival;


		// Saving Throws
		Skill strengthSave;
		Skill dexteritySave;
		Skill constitutionSave;
		Skill intelligenceSave;
		Skill wisdomSave;
		Skill charismaSave;


		// Feats, Traits, Lanuguages, Proficiencies
		std::vector<Trait> featsAndTraits;
		std::vector<Trait> profiencies;
		std::vector<std::string> languages;


		// Equipment
		Wealth wealth;
		std::string equipmentList;


		// Combat
		int currentHitPoints = 0;
		int maxHitPoints = 0;
		int tempHitPoints = 0;
		int armorClass = 0;
		int initiative = 0;
		int speed = 0;
		HitDice hitDice;
		DeathSaves deathSaves;
		std::vector<Attack> attacks;
		std::vector<Trait> spellcastingTraits;
	};
}