#include "dndCharacter.h"
#include "dndCharacterGenerator.h"
#include <ctime>
#include <random>
#include <string>
#include <vector>
using std::default_random_engine;
using std::string;
using std::uniform_int_distribution;
using std::vector;

dndCharacterGenerator::dndCharacterGenerator()
{
}

int dndCharacterGenerator::roll(int min, int max)
{
	default_random_engine engine(time(0));
	uniform_int_distribution<unsigned> dist(min, max);

	return dist(engine);
}

// ======================================================================================
// Desriptors
// ======================================================================================

void dndCharacterGenerator::generateClass(dndCharacter& character)
{
	vector<string> classes = { "Barbarian", "Bard", "Cleric", "Druid", "Fighter", "Monk", "Paladin", "Ranger", "Rogue", 
							"Sorcerer", "Warlock", "Wizard" };

	character.characterClass = classes[roll(0, classes.size() - 1)];
}

void dndCharacterGenerator::generateRace(dndCharacter& character)
{
	vector<string> races = { "Dwarf", "Elf", "Halfling", "Human" };

	character.race = races[roll(0, races.size() - 1)];
}

void dndCharacterGenerator::generateBackground(dndCharacter& character)
{
	// Variants: Spy (Criminal), Gladiator (Entertainer), Guild Merchant (Guild Artisan), Knight (Noble), Pirate (Sailor)
	vector<string> backgrounds = { "Acolyte", "Charlatan", "Criminal", "Entertainer", "Folk Hero", "Gladiator", "Guild Artisan", 
								"Guild Merchant", "Hermit", "Knight", "Noble", "Outlander", "Pirate", "Sage", "Sailor", "Soldier", 
								"Spy", "Urchin" };

	character.background = backgrounds[roll(0, backgrounds.size() - 1)];
}

void dndCharacterGenerator::generateAlignment(dndCharacter& character)
{
	vector<string> alignments = { "Lawful Good", "Neutral Good", "Chaotic Good", "Lawful Neutral", "Neutral", "Chaotic Neutral",
								"Lawful Evil", "Neutral Evil", "Chaotic Evil" };

	character.alignment = alignments[roll(0, alignments.size() - 1)];
}

void dndCharacterGenerator::generateName(dndCharacter& character)
{
	// Gender needed to generate random name
	if (character.gender == "")
	{
		// Probably overkill, but for for the sake of consistency . . .

		vector<string> genders = { "Male", "Female" };

		character.gender = genders[roll(0, genders.size() - 1)];
	}

	// Generate Random Name
}

void dndCharacterGenerator::generatePersonalityTraits(dndCharacter & character)
{
}

void dndCharacterGenerator::generateIdeals(dndCharacter & character)
{
}

void dndCharacterGenerator::generateBonds(dndCharacter & character)
{
}

void dndCharacterGenerator::generateFlaws(dndCharacter & character)
{
}


// ======================================================================================
// Values
// ======================================================================================

void dndCharacterGenerator::generateLevel(dndCharacter& character)
{
}

void dndCharacterGenerator::generateProficiencyBonus(dndCharacter & character)
{
}

void dndCharacterGenerator::generatePassiveWisdom(dndCharacter & character)
{
}


// ======================================================================================
// Skills and Abilities
// ======================================================================================


void dndCharacterGenerator::generateAbilities(dndCharacter & character)
{
}

void dndCharacterGenerator::generateSkills(dndCharacter & character)
{
}

void dndCharacterGenerator::generateSavingThrows(dndCharacter & character)
{
}


// ======================================================================================
// Feats, Traits, Proficiencies, Languages
// ======================================================================================

void dndCharacterGenerator::generateFeatsAndTraits(dndCharacter & character)
{
}

void dndCharacterGenerator::generateProficienciesAndLanguages(dndCharacter & character)
{
}


// ======================================================================================
// Equipment and Combat
// ======================================================================================

void dndCharacterGenerator::generateEquipment(dndCharacter & character)
{
}

void dndCharacterGenerator::generateCombatValues(dndCharacter & character)
{
}

void dndCharacterGenerator::generateAttacks(dndCharacter & character)
{
}

void dndCharacterGenerator::generateSpellcastingTraits(dndCharacter & character)
{
}


// ======================================================================================
// Generate Character
// ======================================================================================

void dndCharacterGenerator::generateCharacter(dndCharacter & character)
{
	// Descriptors
	generateClass(character);
	generateRace(character);
	generateBackground(character);
	generateAlignment(character);
	generateName(character);
	generatePersonalityTraits(character);
	generateIdeals(character);
	generateBonds(character);
	generateFlaws(character);

	// Values
	generateLevel(character);

	generateProficiencyBonus(character);
	generatePassiveWisdom(character);

	// Skills and Abilities
	generateAbilities(character);
	generateSkills(character);
	generateSavingThrows(character);

	// Feats, Traits, Proficiencies, Languages
	generateFeatsAndTraits(character);
	generateProficienciesAndLanguages(character);

	// Equipment and Combat
	generateEquipment(character);
	generateCombatValues(character);
	generateAttacks(character);
	generateSpellcastingTraits(character);
}