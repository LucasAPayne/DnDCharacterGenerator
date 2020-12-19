#pragma once

#include "Types.h"

#include <string>
#include <vector>

namespace dnd
{
	class Character
	{
	public:
		Character();

		// Temporary
		void DisplayCharacterSheet();

	private:
		// Descriptors ==============================================================
		void GenerateClass();
		void GenerateRace();
		void GenerateBackground();
		void GenerateAlignment();
		void GenerateGender();
		void GenerateName();
		void GeneratePersonality();

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
		void GenerateRacialFeats();
		void GenerateBackgroundFeats();
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
		std::string m_MajorRace;
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
