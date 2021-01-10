#pragma once

#include <string>

namespace dnd
{

	// The six main abilities: Str, Dex, Con, Int, Wis, Cha
	struct Ability
	{
		int Score = 0;
		int Modifier = 0;
	};


	// Specific aspects of abilities
	struct Skill
	{
		Ability Parent; // The ability that governs the skill
		int Modifier = 0;
		bool Proficient = false; // Fill in the bubble on character sheet and allows proficiency bonus to be applied to modifier
	};


	struct Trait
	{
		std::string Name;
		std::string Description;

		Trait(const std::string& name, const std::string& description)
			: Name(name), Description(description)
		{}
	};

	// A collection of the different types of coins a character owns
	struct Wealth
	{
		int CopperPieces = 0;
		int SilverPieces = 0;
		int ElectrumPieces = 0;
		int GoldPieces = 0;
		int PlatinumPieces = 0;
	};

	struct Attack
	{
		std::string Name;
		int AtkBonus;
		std::string Type;
		std::string Damage; // string b/c it's based on die roll, ex. "1d8 + 2"
	};

	// The dice a character's hit points are based on
	struct HitDice
	{
		int Type = 0; // How many faces each die has
		int Number = 0;   // How many dice
	};


	struct DeathSaves
	{
		int Successes = 0;
		int Failures = 0;
	};
}
