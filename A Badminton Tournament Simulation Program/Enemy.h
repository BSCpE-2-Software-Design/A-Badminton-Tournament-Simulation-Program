#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include <vector>

class Enemy {
public:
    
    static const int TOTAL_CHARACTERS = 6;

    
    enum CharacterType {
        SPEED_DEMON = 0,     
        POWER_HITTER = 1,     
        BALANCED_PLAYER = 2,  
        ENDURANCE_MASTER = 3, 
        TECHNICAL_EXPERT = 4, 
        YOUNG_TALENT = 5      
    };

    
    static std::vector<Player> getAllCharacters();

    
    static Player getCharacterById(int id);

    
    static void displayAllCharacters();
};

#endif 

