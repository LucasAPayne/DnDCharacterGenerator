#pragma once

class dndCharacter;

class dndCharacterGenerator
{
private:
	bool random;

	void chooseXRandomlyFrom(int x, std::vector<std::reference_wrapper<Skill> > list);

public:
	dndCharacterGenerator();
	
	// Descriptors ==============================================================

	void generateClass(dndCharacter& character);
	void generateRace(dndCharacter& character);
	void generateBackground(dndCharacter& character);
	void generateAlignment(dndCharacter& character);
	void generateName(dndCharacter& character); // Also determines sex if not done by the user
	void generatePersonalityTraits(dndCharacter& character);
	void generateIdeals(dndCharacter& character);
	void generateBonds(dndCharacter& character);
	void generateFlaws(dndCharacter& character);

	// Skills, Abilities, and Level ==============================================

	// Generates random level and sets experience to the starting amount for that level
	void generateLevel(dndCharacter& character);

	void generateProficiencyBonus(dndCharacter& character);
	void generateAbilityScores(dndCharacter& character);
	void generateRacialAbilityBonuses(dndCharacter& character);
	void generateAbilityModifiers(dndCharacter& character);
	void generateSkillProficiencies(dndCharacter& character);
	void generateSkillModifiers(dndCharacter& character);
	void generateSavingThrowProficiencies(dndCharacter& character);
	void generateSavingThrowModifiers(dndCharacter& character);
	void generatePassiveWisdom(dndCharacter& character);

	// Feats, Traits, Proficiencies, Languages ===================================
	void generateFeatsAndTraits(dndCharacter& character);
	void generateProficienciesAndLanguages(dndCharacter& character);

	// Equipment and Combat ======================================================

	void generateEquipment(dndCharacter& character);
	void generateCombatValues(dndCharacter& character);
	void generateAttacks(dndCharacter& character);
	void generateSpellcastingTraits(dndCharacter& character);

	// Generate Character ========================================================

	// Calls all other generate functions so a character can be made with one function call
	void generateCharacter(dndCharacter& character);
};