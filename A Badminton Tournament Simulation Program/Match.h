#pragma once
#ifndef MATCH_H
#define MATCH_H

#include "Player.h"
#include <vector>

class Match {
public:
    enum MatchType {
        SINGLES,  // 1v1
        DOUBLES   // 2v2
    };

    enum MatchStatus {
        PENDING,
        IN_PROGRESS,
        COMPLETED
    };

private:
    MatchType type;
    std::vector<Player> teamA;  // 1 or 2 players
    std::vector<Player> teamB;  // 1 or 2 players
    int scoreA;
    int scoreB;
    MatchStatus status;
    int matchId;

public:
    Match();
    Match(int id, MatchType type, const std::vector<Player>& tA, const std::vector<Player>& tB);

    // Getters
    MatchType getType() const;
    std::vector<Player> getTeamA() const;
    std::vector<Player> getTeamB() const;
    int getScoreA() const;
    int getScoreB() const;
    MatchStatus getStatus() const;
    int getMatchId() const;

    // Setters
    void setScoreA(int score);
    void setScoreB(int score);
    void setStatus(MatchStatus s);
    void addScoreA(int points);
    void addScoreB(int points);

    // Methods
    std::vector<Player> getWinnerTeam() const;
    std::vector<Player> getLoserTeam() const;
    bool isCompleted() const;

    // Display
    void display() const;
    void displayResult() const;
};

#endif // MATCH_H
