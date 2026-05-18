#pragma once
#ifndef MATCH_H
#define MATCH_H

#include "Player.h"
#include <vector>

class Match {
public:
    enum MatchType {
        SINGLES,  
        DOUBLES   
    };

    enum MatchStatus {
        PENDING,
        IN_PROGRESS,
        COMPLETED
    };

private:
    MatchType type;
    std::vector<Player> teamA;  
    std::vector<Player> teamB;  
    int scoreA;
    int scoreB;
    MatchStatus status;
    int matchId;

public:
    Match();
    Match(int id, MatchType type, const std::vector<Player>& tA, const std::vector<Player>& tB);

    
    MatchType getType() const;
    std::vector<Player> getTeamA() const;
    std::vector<Player> getTeamB() const;
    int getScoreA() const;
    int getScoreB() const;
    MatchStatus getStatus() const;
    int getMatchId() const;

    
    void setScoreA(int score);
    void setScoreB(int score);
    void setStatus(MatchStatus s);
    void addScoreA(int points);
    void addScoreB(int points);

    
    std::vector<Player> getWinnerTeam() const;
    std::vector<Player> getLoserTeam() const;
    bool isCompleted() const;

    
    void display() const;
    void displayResult() const;
};

#endif 
