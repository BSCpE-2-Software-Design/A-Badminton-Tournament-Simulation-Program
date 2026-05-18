#include "Player.h"
#include "Enemy.h"
#include "Match.h"
#include "Schedule.h"
#include "SimulationEngine.h"
#include "StandingTracker.h"
#include "Display.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>

int main() {
    srand(static_cast<unsigned>(time(0)));

    Display::displayWelcome();

    SimulationEngine engine;
    StandingTracker tracker;

    bool running = true;

    while (running) {
        Display::displayMainMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            // Start tournament
            Display::clearScreen();
            Display::displayModeSelection();
            int modeChoice;
            std::cin >> modeChoice;

            Match::MatchType mode;
            int playerNeeded;

            if (modeChoice == 1) {
                mode = Match::SINGLES;
                playerNeeded = 1;
            }
            else if (modeChoice == 2) {
                mode = Match::DOUBLES;
                playerNeeded = 2;
            }
            else {
                Display::displayError("Invalid choice!");
                Display::pressEnter();
                break;
            }

            // Get all available characters
            std::vector<Player> allPlayers = Enemy::getAllCharacters();

            // Player selection
            std::vector<Player> selectedPlayers;
            std::vector<int> selectedIds;

            for (int i = 0; i < playerNeeded; i++) {
                Display::clearScreen();
                Display::displayPlayerSelection(allPlayers, i + 1);

                int selectedId;
                bool validSelection = false;

                while (!validSelection) {
                    std::cout << "Enter player ID for player " << (i + 1) << ": ";
                    std::cin >> selectedId;

                    // Check if player already selected
                    bool alreadySelected = false;
                    for (int id : selectedIds) {
                        if (id == selectedId) {
                            alreadySelected = true;
                            Display::displayError("Player already selected!");
                            break;
                        }
                    }

                    if (!alreadySelected && selectedId >= 0 && selectedId < Enemy::TOTAL_CHARACTERS) {
                        selectedPlayers.push_back(Enemy::getCharacterById(selectedId));
                        selectedIds.push_back(selectedId);
                        validSelection = true;
                    }
                    else if (!alreadySelected) {
                        Display::displayError("Invalid player ID!");
                    }
                }
            }

            // Display selected team
            Display::clearScreen();
            Display::displayTeamSelection(selectedPlayers, playerNeeded);
            Display::pressEnter();

            // Create list of enemies (all players except selected ones)
            std::vector<Player> enemies;
            for (const auto& allPlayer : allPlayers) {
                bool isSelected = false;
                for (int selectedId : selectedIds) {
                    if (allPlayer.getId() == selectedId) {
                        isSelected = true;
                        break;
                    }
                }
                if (!isSelected) {
                    enemies.push_back(allPlayer);
                }
            }

            // Create matches: Your team vs 5 random enemies
            std::vector<Match> matches;
            int matchId = 1;

            // We'll play against up to 5 different opponents
            int numMatches = std::min(5, (int)enemies.size());
            if (numMatches == 0) {
                Display::displayError("Not enough enemies to create matches.");
                Display::pressEnter();
                break;
            }

            // Build and shuffle indices
            std::vector<int> enemyIndices;
            for (size_t i = 0; i < enemies.size(); i++) {
                enemyIndices.push_back((int)i);
            }
            // Simple Fisher-Yates shuffle using rand() to preserve original approach
            for (int i = (int)enemyIndices.size() - 1; i > 0; --i) {
                int j = rand() % (i + 1);
                std::swap(enemyIndices[i], enemyIndices[j]);
            }

            // Generate matches against random enemies
            for (int m = 0; m < numMatches; m++) {
                if (mode == Match::SINGLES) {
                    // 1v1 match
                    std::vector<Player> yourTeam = { selectedPlayers[0] };
                    std::vector<Player> enemyTeam = { enemies[enemyIndices[m]] };

                    Match match(matchId++, Match::SINGLES, yourTeam, enemyTeam);
                    matches.push_back(match);
                }
                else {
                    // 2v2 match - need 2 different enemies
                    std::vector<Player> yourTeam = selectedPlayers;
                    std::vector<Player> enemyTeam;

                    // First enemy
                    enemyTeam.push_back(enemies[enemyIndices[m]]);

                    // Find another enemy index different from enemyIndices[m]
                    int secondEnemyIdx = -1;
                    for (size_t k = 0; k < enemyIndices.size(); ++k) {
                        if ((int)k == m) continue;
                        secondEnemyIdx = enemyIndices[k];
                        break;
                    }

                    // If we couldn't find a different one (rare), try next modulo
                    if (secondEnemyIdx == -1 && enemies.size() > 1) {
                        secondEnemyIdx = enemyIndices[(m + 1) % enemyIndices.size()];
                        if (secondEnemyIdx == enemyIndices[m] && enemyIndices.size() > 1) {
                            secondEnemyIdx = enemyIndices[(m + 2) % enemyIndices.size()];
                        }
                    }

                    if (secondEnemyIdx != -1) {
                        enemyTeam.push_back(enemies[secondEnemyIdx]);
                    }
                    else {
                        // Fallback: duplicate the same enemy if no other available (shouldn't happen)
                        enemyTeam.push_back(enemies[enemyIndices[m]]);
                    }

                    Match match(matchId++, Match::DOUBLES, yourTeam, enemyTeam);
                    matches.push_back(match);
                }
            }

            // Initialize tracker with selected players
            for (const auto& player : selectedPlayers) {
                tracker.addPlayer(player);
            }

            // Attach tracker to engine
            engine.attach(&tracker);

            // Display matches schedule
            Display::clearScreen();
            std::cout << "\n" << std::string(80, '=') << std::endl;
            std::string typeStr = (mode == Match::SINGLES) ? "SINGLES (1v1)" : "DOUBLES (2v2)";
            std::cout << "Tournament Mode: " << typeStr << std::endl;
            std::cout << "Your Team: ";
            for (const auto& p : selectedPlayers) {
                std::cout << p.getName() << " ";
            }
            std::cout << std::endl;
            std::cout << "Total Matches: " << matches.size() << std::endl;
            std::cout << std::string(80, '=') << std::endl;
            std::cout << "Matches:" << std::endl;
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
            Display::pressEnter();

            // Run tournament
            Display::clearScreen();
            std::cout << "Starting tournament simulation..." << std::endl << std::endl;
            int wins = 0;
            int losses = 0;
            for (size_t i = 0; i < matches.size(); i++) {
                Display::displayMatchProgress((int)i + 1, (int)matches.size());
                engine.simulateMatch(matches[i]);
                Display::displayMatchResult(matches[i]);

                // Track wins/losses for your team (teamA is your team in created matches)
                if (matches[i].getScoreA() > matches[i].getScoreB()) {
                    wins++;
                }
                else {
                    losses++;
                }
            }
            // Display final standings (only your players)
            Display::clearScreen();
            std::cout << " " << std::string(80, '=') << std::endl;
            std::cout << "TOURNAMENT COMPLETE!" << std::endl;
            std::cout << std::string(80, '=') << std::endl;
            std::cout << "Your Team Statistics:" << std::endl;
            std::cout << std::string(80, '-') << std::endl;
            for (const auto& player : selectedPlayers) {
                auto stats = tracker.getPlayerStats(player.getId());
                std::cout << std::left << std::setw(20) << stats.getName()
                    << std::setw(10) << ("Wins: " + std::to_string(stats.getWins()))
                    << std::setw(10) << ("Losses:" + std::to_string(stats.getLosses()))
                    << std::setw(12) << ("Points: " + std::to_string(stats.getTotalPoints())) << std::endl;
            }
            std::cout << std::string(80, '=') << std::endl;
            std::cout << "Team Overall Record: " << wins << " wins, " << losses << " losses" << std::endl;
            if (wins > losses) {
                std::cout << "CONGRATULATIONS! Your team is the champion!" << std::endl;
            }
            else if (wins == losses) {
                std::cout << "Balanced performance! Keep improving!" << std::endl;
            }
            else {
                std::cout << "Better luck next time! Keep training!" << std::endl;
            }
            std::cout << std::string(80, '=') << std::endl;
            Display::pressEnter();

            // Reset tracker for next tournament
            tracker = StandingTracker();
            break;
        }
        case 2: {
            // View available players
            Display::clearScreen();
            Enemy::displayAllCharacters();
            Display::pressEnter();
            break;
        }
        case 3: {
            // Exit
            std::cout << "Thank you for playing! Goodbye!" << std::endl;
            running = false;
            break;
        }
        default:
            Display::displayError("Invalid choice! Please try again.");
            Display::pressEnter();
            break;
        }
    }
    return 0;
}


