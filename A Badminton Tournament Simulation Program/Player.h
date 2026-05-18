#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Player {
private:
    int id;
    std::string name;
    int skillLevel;    
    int stamina;       
    int wins;
    int losses;
    int totalPoints;
    bool isActive;     

public:
    Player();
    Player(int id, const std::string& name, int skillLevel, int stamina);

    
    int getId() const;
    std::string getName() const;
    int getSkillLevel() const;
    int getStamina() const;
    int getWins() const;
    int getLosses() const;
    int getTotalPoints() const;
    bool getIsActive() const;

    
    void setWins(int w);
    void setLosses(int l);
    void setTotalPoints(int p);
    void addWin();
    void addLoss();
    void addPoints(int points);
    void setActive(bool active);

    
    void display() const;
};

#endif 
