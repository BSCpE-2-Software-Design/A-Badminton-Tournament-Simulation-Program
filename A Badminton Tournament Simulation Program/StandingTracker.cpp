#include "StandingTracker.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

StandingTracker::StandingTracker() {}

void StandingTracker::onMatchCompleted(const Match& match) {
    // Get winner and loser teams
    std::vector<Player> winners = match.getWinnerTeam();
    std::vector<Player> losers = match.getLoserTeam();

    int winnerScore = (match.getScoreA() > match.getScoreB()) ? match.getScoreA() : match.getScoreB();
    int loserScore = (match.getScoreA() < match.getScoreB()) ? match.getScoreA() : match.getScoreB();

    // Update winner stats
    for (const auto& winner : winners) {
        int playerId = winner.getId();

        if (playerStats.find(playerId) != playerStats.end()) {
            playerStats[playerId].addWin();
            playerStats[playerId].addPoints(winnerScore);
        }
        else {
            Player updated = winner;
            updated.addWin();
            updated.addPoints(winnerScore);
            playerStats[playerId] = updated;
        }
    }

    // Update loser stats
    for (const auto& loser : losers) {
        int playerId = loser.getId();

        if (playerStats.find(playerId) != playerStats.end()) {
            playerStats[playerId].addLoss();
            playerStats[playerId].addPoints(loserScore);
        }
        else {
            Player updated = loser;
            updated.addLoss();
            updated.addPoints(loserScore);
            playerStats[playerId] = updated;
        }
    }
}

void StandingTracker::updatePlayerStats(const Player& player) {
    int playerId = player.getId();
    if (playerStats.find(playerId) != playerStats.end()) {
        playerStats[playerId] = player;
    }
}

void StandingTracker::addPlayer(const Player& player) {
    playerStats[player.getId()] = player;
}

std::vector<Player> StandingTracker::getSortedStandings() const {
    std::vector<Player> standings;
    for (const auto& pair : playerStats) {
        standings.push_back(pair.second);
    }

    // Sort by wins (descending), then by total points (descending)
    std::sort(standings.begin(), standings.end(),
        [](const Player& a, const Player& b) {
            if (a.getWins() != b.getWins()) {
                return a.getWins() > b.getWins();
            }
            return a.getTotalPoints() > b.getTotalPoints();
        });

    return standings;
}

Player StandingTracker::getPlayerStats(int playerId) const {
    if (playerStats.find(playerId) != playerStats.end()) {
        return playerStats.at(playerId);
    }
    return Player();
}

void StandingTracker::printLeaderboard() const {
    std::vector<Player> standings = getSortedStandings();

    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "FINAL LEADERBOARD" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    std::cout << std::left
        << std::setw(5) << "Rank"
        << std::setw(20) << "Player"
        << std::setw(10) << "Wins"
        << std::setw(10) << "Losses"
        << std::setw(12) << "Points" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    for (size_t i = 0; i < standings.size(); i++) {
        std::cout << std::left
            << std::setw(5) << (i + 1)
            << std::setw(20) << standings[i].getName()
            << std::setw(10) << standings[i].getWins()
            << std::setw(10) << standings[i].getLosses()
            << std::setw(12) << standings[i].getTotalPoints() << std::endl;
    }
    std::cout << std::string(80, '=') << std::endl;
}

void StandingTracker::printDetailed() const {
    std::vector<Player> standings = getSortedStandings();

    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "DETAILED STATISTICS" << std::endl;
    std::cout << std::string(80, '=') << std::endl;

    for (size_t i = 0; i < standings.size(); i++) {
        const Player& p = standings[i];
        std::cout << std::left
            << "[" << (i + 1) << "] " << p.getName()
            << " | Skill: " << p.getSkillLevel()
            << " | Stamina: " << p.getStamina()
            << " | W/L: " << p.getWins() << "/" << p.getLosses()
            << " | Points: " << p.getTotalPoints() << std::endl;
    }
    std::cout << std::string(80, '=') << std::endl;
}
