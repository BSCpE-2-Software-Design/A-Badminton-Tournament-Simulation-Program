#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include <vector>

class Enemy {
public:
    // Predefined 6 characters with different stats
    static const int TOTAL_CHARACTERS = 6;

    // Character IDs
    enum CharacterType {
        SPEED_DEMON = 0,      // High agility, Medium stamina
        POWER_HITTER = 1,     // High skill, Medium stamina
        BALANCED_PLAYER = 2,  // Medium skill, High stamina
        ENDURANCE_MASTER = 3, // Low skill, High stamina
        TECHNICAL_EXPERT = 4, // High skill, Low stamina
        YOUNG_TALENT = 5      // Medium skill, Medium stamina
    };

    // Static method to get all available enemies/characters
    static std::vector<Player> getAllCharacters();

    // Get specific character by ID
    static Player getCharacterById(int id);

    // Display all available characters
    static void displayAllCharacters();
};

#endif // ENEMY_H

