#pragma once

#include <string>
#include <vector>

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
		std::string Type; // d6, d8, etc.
		int Number = 0;   // How many dice
	};


	struct DeathSaves
	{
		int Successes = 0;
		int Failures = 0;
	};


	class Character
	{
	public:
		Character();

		// Temporary
		const std::string& GetEthnicity() const { return m_Ethnicity; }
		void DisplayCharacterSheet();

	private:
		// Descriptors ==============================================================
		void GenerateClass();
		void GenerateRace();
		void GenerateBackground();
		void GenerateAlignment();
		void GenerateGender();
		void GenerateFirstName();
		void GenerateSurname();
		void GeneratePersonalityTraits();
		void GenerateIdeals();
		void GenerateBonds();
		void GenerateFlaws();


		// Skills, Abilities, and Level ==============================================

		// Generates random level and sets experience to the starting amount for that level
		void GenerateLevel();

		void GenerateProficiencyBonus();
		void GenerateAbilityScores();
		void GenerateRacialAbilityBonuses();
		void GenerateAbilityModifiers();
		void GenerateSkillProficiencies();
		void GenerateSkillModifiers();
		void GenerateSavingThrowProficiencies();
		void GenerateSavingThrowModifiers();
		void GeneratePassiveWisdom();


		// Feats, Traits, Proficiencies, Languages ===================================
		void GenerateFeatsAndTraits();
		void GenerateRacialTraits();
		void GenerateProficiencies();
		void GenerateLanguages();

		// Equipment and Combat ======================================================
		void GenerateHitDice();
		void GenerateHitPoints();
		void GenerateSpeed();
		void GenerateInitiative();
		void GenerateEquipment();
		void GenerateAttacks();
		void GenerateSpellcastingTraits();

	private:
		// Descriptors
		std::string m_PlayerName;
		std::string m_FirstName;
		std::string m_Surname;
		std::string m_Gender;
		std::string m_Class;
		std::string m_Background;
		std::string m_Race;
		std::string m_Ethnicity; // Only for humans
		std::string m_Alignment;
		std::string m_PersonalityTraits;
		std::string m_Ideals;
		std::string m_Bonds;
		std::string m_Flaws;

		// Values
		int m_Level = 0;
		int m_Experience = 0;
		int m_Inspiration = 0;
		int m_ProficiencyBonus = 0;
		int m_PassiveWisdom = 0;

		// Abilities
		Ability m_Strength;
		Ability m_Dexterity;
		Ability m_Constitution;
		Ability m_Intelligence;
		Ability m_Wisdom;
		Ability m_Charisma;

		// Skills
		Skill m_Acrobatics;
		Skill m_AnimalHandling;
		Skill m_Arcana;
		Skill m_Athletics;
		Skill m_Deception;
		Skill m_History;
		Skill m_Insight;
		Skill m_Intimidation;
		Skill m_Investigation;
		Skill m_Medicine;
		Skill m_Nature;
		Skill m_Perception;
		Skill m_Performance;
		Skill m_Persuasion;
		Skill m_Religion;
		Skill m_SleightOfHand;
		Skill m_Stealth;
		Skill m_Survival;

		// Saving Throws
		Skill m_StrengthSave;
		Skill m_DexteritySave;
		Skill m_ConstitutionSave;
		Skill m_IntelligenceSave;
		Skill m_WisdomSave;
		Skill m_CharismaSave;

		// Feats, Traits, Lanuguages, Proficiencies
		std::vector<Trait> m_FeatsAndTraits;
		std::vector<Trait> m_Profiencies;
		std::vector<std::string> m_Languages;

		// Equipment
		Wealth m_Wealth;
		std::string m_EquipmentList;

		// Combat
		int m_CurrentHitPoints = 0;
		int m_MaxHitPoints = 0;
		int m_TempHitPoints = 0;
		int m_ArmorClass = 0;
		int m_Initiative = 0;
		int m_Speed = 0;
		HitDice m_HitDice;
		DeathSaves m_DeathSaves;
		std::vector<Attack> m_Attacks;
		std::vector<Trait> m_SpellcastingTraits;
	};
}