#include "Schedule.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Schedule::Schedule(Match::MatchType type) : matchType(type), matchCounter(0) {}

void Schedule::generateRoundRobinSingles(const std::vector<Player>& players) {
    matches.clear();
    matchCounter = 0;

    // Generate all unique pairs (i, j) where i < j
    for (size_t i = 0; i < players.size(); i++) {
        for (size_t j = i + 1; j < players.size(); j++) {
            std::vector<Player> teamA = { players[i] };
            std::vector<Player> teamB = { players[j] };

            Match match(++matchCounter, Match::SINGLES, teamA, teamB);
            matches.push_back(match);
        }
    }
}

void Schedule::generateRoundRobinDoubles(const std::vector<Player>& players) {
    matches.clear();
    matchCounter = 0;

    if (players.size() < 4) {
        std::cout << "Not enough players for doubles (need at least 4)" << std::endl;
        return;
    }

    // Generate all unique pairs of pairs
    // For each combination of 2 players from first half vs 2 players from second half
    int n = players.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;
                for (int l = k + 1; l < n; l++) {
                    if (l == i || l == j) continue;

                    // Avoid duplicate matches (team A vs B same as B vs A)
                    if (i < k) {
                        std::vector<Player> teamA = { players[i], players[j] };
                        std::vector<Player> teamB = { players[k], players[l] };

                        Match match(++matchCounter, Match::DOUBLES, teamA, teamB);
                        matches.push_back(match);
                    }
                }
            }
        }
    }
}

std::vector<Match> Schedule::getMatches() const { return matches; }
int Schedule::getTotalMatches() const { return matches.size(); }
Match Schedule::getMatch(int index) const { return matches[index]; }

void Schedule::displaySchedule() const {
    std::string typeStr = (matchType == Match::SINGLES) ? "SINGLES (1v1)" : "DOUBLES (2v2)";
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "Tournament Schedule - " << typeStr << std::endl;
    std::cout << "Total Matches: " << getTotalMatches() << std::endl;
    std::cout << std::string(80, '=') << std::endl;

    for (size_t i = 0; i < matches.size(); i++) {
        std::cout << "Match " << (i + 1) << ": ";
        for (const auto& p : matches[i].getTeamA()) {
            std::cout << p.getName() << " ";
        }
        std::cout << "vs ";
        for (const auto& p : matches[i].getTeamB()) {
            std::cout << p.getName() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::string(80, '=') << std::endl;
}
