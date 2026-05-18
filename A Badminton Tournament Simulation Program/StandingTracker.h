#pragma once
#ifndef STANDING_TRACKER_H
#define STANDING_TRACKER_H

#include "SimulationEngine.h"
#include "Player.h"
#include <vector>
#include <map>

class StandingTracker : public IMatchObserver {
private:
    std::map<int, Player> playerStats;  

public:
    StandingTracker();

    void onMatchCompleted(const Match& match) override;

    void updatePlayerStats(const Player& player);
    void addPlayer(const Player& player);

    std::vector<Player> getSortedStandings() const;
    Player getPlayerStats(int playerId) const;

    void printLeaderboard() const;
    void printDetailed() const;
};

#endif
