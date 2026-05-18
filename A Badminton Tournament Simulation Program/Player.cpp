#include "Player.h"
#include <iostream>
#include <iomanip>

Player::Player() : id(0), name(""), skillLevel(0), stamina(0), wins(0), losses(0), totalPoints(0), isActive(true) {}

Player::Player(int id, const std::string& name, int skillLevel, int stamina)
    : id(id), name(name), skillLevel(skillLevel), stamina(stamina), wins(0), losses(0), totalPoints(0), isActive(true) {
}

int Player::getId() const { return id; }
std::string Player::getName() const { return name; }
int Player::getSkillLevel() const { return skillLevel; }
int Player::getStamina() const { return stamina; }
int Player::getWins() const { return wins; }
int Player::getLosses() const { return losses; }
int Player::getTotalPoints() const { return totalPoints; }
bool Player::getIsActive() const { return isActive; }

void Player::setWins(int w) { wins = w; }
void Player::setLosses(int l) { losses = l; }
void Player::setTotalPoints(int p) { totalPoints = p; }
void Player::addWin() { wins++; }
void Player::addLoss() { losses++; }
void Player::addPoints(int points) { totalPoints += points; }
void Player::setActive(bool active) { isActive = active; }

void Player::display() const {
    std::cout << std::left << std::setw(3) << id
        << std::setw(15) << name
        << "Skill: " << std::setw(2) << skillLevel
        << "Stamina: " << std::setw(2) << stamina
        << "W: " << std::setw(2) << wins
        << "L: " << std::setw(2) << losses
        << "Points: " << std::setw(4) << totalPoints << std::endl;
}