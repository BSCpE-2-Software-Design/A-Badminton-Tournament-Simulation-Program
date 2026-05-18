#pragma once
#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Match.h"
#include "Player.h"
#include <vector>

class Schedule {
private:
    std::vector<Match> matches;
    Match::MatchType matchType;
    int matchCounter;

public:
    Schedule(Match::MatchType type);

    // Generate schedule
    void generateRoundRobinSingles(const std::vector<Player>& players);
    void generateRoundRobinDoubles(const std::vector<Player>& players);

    // Getters
    std::vector<Match> getMatches() const;
    int getTotalMatches() const;
    Match getMatch(int index) const;

    // Display
    void displaySchedule() const;
};

#endif