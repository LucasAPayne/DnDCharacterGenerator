#pragma once

namespace dnd
{
	// Descriptors ==============================================================
	void generateClass(Character& character);
	void generateRace(Character& character);
	void generateBackground(Character& character);
	void generateAlignment(Character& character);
	void generateSex(Character& character);
	void generateFirstName(Character& character);
	void generateSurname(Character& character);
	void generatePersonalityTraits(Character& character);
	void generateIdeals(Character& character);
	void generateBonds(Character& character);
	void generateFlaws(Character& character);


	// Skills, Abilities, and Level ==============================================

	// Generates random level and sets experience to the starting amount for that level
	void generateLevel(Character& character);

	void generateProficiencyBonus(Character& character);
	void generateAbilityScores(Character& character);
	void generateRacialAbilityBonuses(Character& character);
	void generateAbilityModifiers(Character& character);
	void generateSkillProficiencies(Character& character);
	void generateSkillModifiers(Character& character);
	void generateSavingThrowProficiencies(Character& character);
	void generateSavingThrowModifiers(Character& character);
	void generatePassiveWisdom(Character& character);


	// Feats, Traits, Proficiencies, Languages ===================================
	void generateFeatsAndTraits(Character& character);
	void generateRacialTraits(Character& character);
	void generateProficiencies(Character& character);
	void generateLanguages(Character& character);

	// Equipment and Combat ======================================================
	void generateHitDice(Character& character);
	void generateHitPoints(Character& character);
	void generateSpeed(Character& character);
	void generateInitiative(Character& character);
	void generateEquipment(Character& character);
	void generateAttacks(Character& character);
	void generateSpellcastingTraits(Character& character);

	// Generate Character ========================================================

	// Calls all other generate functions so a character can be made with one function call
	void generateCharacter(Character& character);
}