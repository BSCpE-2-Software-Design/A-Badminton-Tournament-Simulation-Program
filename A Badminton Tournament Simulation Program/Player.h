#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Player {
private:
    int id;
    std::string name;
    int skillLevel;    // 1-10
    int stamina;       // 1-10
    int wins;
    int losses;
    int totalPoints;
    bool isActive;     // For tournament participation

public:
    Player();
    Player(int id, const std::string& name, int skillLevel, int stamina);

    // Getters
    int getId() const;
    std::string getName() const;
    int getSkillLevel() const;
    int getStamina() const;
    int getWins() const;
    int getLosses() const;
    int getTotalPoints() const;
    bool getIsActive() const;

    // Setters
    void setWins(int w);
    void setLosses(int l);
    void setTotalPoints(int p);
    void addWin();
    void addLoss();
    void addPoints(int points);
    void setActive(bool active);

    // Display
    void display() const;
};

#endif // PLAYER_H
