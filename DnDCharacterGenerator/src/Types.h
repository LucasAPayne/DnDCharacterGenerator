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

	struct Attack
	{
		std::string Name;
		int AttackBonus;
		std::string Damage; // string because it's based on die roll, e.g. "1d8+2 bludgeoning"

		Attack(const std::string& name, int attackBonus, const std::string& damage)
			: Name(name), AttackBonus(attackBonus), Damage(damage)
		{}
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
