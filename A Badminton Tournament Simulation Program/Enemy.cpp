#include "Enemy.h"
#include <iostream>
#include <iomanip>

std::vector<Player> Enemy::getAllCharacters() {
    std::vector<Player> characters;

    // Character 0: Speed Demon - High agility (skill), Medium stamina
    characters.push_back(Player(0, "Mommy Oni yahh", 9, 6));

    // Character 1: Power Hitter - High skill, Medium stamina
    characters.push_back(Player(1, "Malupiton Arayy koh", 8, 7));

    // Character 2: Balanced Player - Medium skill, High stamina
    characters.push_back(Player(2, "Frieza ngekk", 6, 9));

    // Character 3: Endurance Master - Low skill, High stamina
    characters.push_back(Player(3, "Master Jawii grrr", 5, 10));

    // Character 4: Technical Expert - High skill, Low stamina
    characters.push_back(Player(4, "Princess goraa na", 10, 4));

    // Character 5: Young Talent - Medium skill, Medium stamina
    characters.push_back(Player(5, "Youngstown gengss", 7, 7));

    return characters;
}

Player Enemy::getCharacterById(int id) {
    std::vector<Player> characters = getAllCharacters();
    if (id >= 0 && id < TOTAL_CHARACTERS) {
        return characters[id];
    }
    return Player(); // Return default if ID invalid
}

void Enemy::displayAllCharacters() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "Available Characters:" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    std::cout << std::left << std::setw(3) << "ID"
        << std::setw(20) << "Name"
        << std::setw(15) << "Skill Level"
        << std::setw(15) << "Stamina" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    std::vector<Player> characters = getAllCharacters();
    for (const auto& character : characters) {
        std::cout << std::left << std::setw(3) << character.getId()
            << std::setw(20) << character.getName()
            << std::setw(15) << character.getSkillLevel()
            << std::setw(15) << character.getStamina() << std::endl;
    }
    std::cout << std::string(70, '=') << std::endl;
}
