#pragma once

#include <string>
#include <vector>

struct Ability
{
	int score;
	int multiplier;
};

struct Skill
{
	int value;
	bool proficient; // Fill in the bubble on character sheet
};

struct Trait
{
	std::string name;
	std::string description;
};

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

struct hitDice
{
	std::string type; // d6, d8, etc.
	int number;       // How many dice
};

struct deathSaves
{
	int successes;
	int failures;
};

class dndCharacter
{
public:
	dndCharacter()
	{
	}
	
public:
	// Descriptors

	std::string characterName;
	std::string playerName;
	std::string gender = "";
	std::string characterClass;
	std::string background;
	std::string race;
	std::string alignment;
	std::string personalityTraits;
	std::string ideals;
	std::string bonds;
	std::string flaws;

	// Values

	int level;
	int experience;
	int inspiration;
	int proficiencyBonus;
	int passiveWisdom;

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

	Skill strenghSave;
	Skill dexteritySave;
	Skill constituionSave;
	Skill intelligenceSave;
	Skill wisdomSave;
	Skill charismaSave;

	// Feats, Traits, Lanuguages, Proficiencies
	std::vector<Trait> featsAndTraits;
	std::vector<Trait> profiencies;
	std::vector<Trait> languages;

	// Equipment
	Wealth wealth;
	std::string equipmentList;

	// Combat

	int currentHitPoints;
	int maxHitPoints;
	int tempHitPoints;
	int armorClass;
	int initiative;
	int speed;
	hitDice hitDice;
	deathSaves deathSaves;
	std::vector<Attack> attacks;
	std::vector<Trait> spellcastingTraits;
};