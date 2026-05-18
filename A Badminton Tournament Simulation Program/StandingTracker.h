#pragma once
#ifndef STANDING_TRACKER_H
#define STANDING_TRACKER_H

#include "SimulationEngine.h"
#include "Player.h"
#include <vector>
#include <map>

class StandingTracker : public IMatchObserver {
private:
    std::map<int, Player> playerStats;  // Map player ID to their updated stats

public:
    StandingTracker();

    // From IMatchObserver
    void onMatchCompleted(const Match& match) override;

    // Update player stats
    void updatePlayerStats(const Player& player);
    void addPlayer(const Player& player);

    // Getters
    std::vector<Player> getSortedStandings() const;
    Player getPlayerStats(int playerId) const;

    // Display
    void printLeaderboard() const;
    void printDetailed() const;
};

#endif // STANDING_TRACKER_H
