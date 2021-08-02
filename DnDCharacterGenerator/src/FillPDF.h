#pragma once

#include "DnDCharacter.h"

#include <vector>
#include <string>

// Helper functions
bool foundException(const std::string& str, const std::vector<std::string>& exceptionList);
bool isVowel(char c);

void fillCharacterSheet_1Page(dnd::Character character);
