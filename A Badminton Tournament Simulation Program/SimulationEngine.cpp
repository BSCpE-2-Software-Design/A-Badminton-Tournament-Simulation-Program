#include "SimulationEngine.h"
#include <iostream>
#include <ctime>
#include <algorithm>

SimulationEngine::SimulationEngine() {
    randomGenerator.seed(static_cast<unsigned>(time(0)));
}

void SimulationEngine::attach(IMatchObserver* observer) {
    if (observer != nullptr) {
        observers.push_back(observer);
    }
}

void SimulationEngine::detach(IMatchObserver* observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void SimulationEngine::notifyObservers(const Match& match) {
    for (auto observer : observers) {
        observer->onMatchCompleted(match);
    }
}

int SimulationEngine::generateRandomVariance() {
    std::uniform_int_distribution<> dis(1, 20);
    return dis(randomGenerator);
}

int SimulationEngine::calculateTeamPerformance(const std::vector<Player>& team) {
    int totalSkill = 0;
    int totalStamina = 0;

    for (const auto& player : team) {
        totalSkill += player.getSkillLevel();
        totalStamina += player.getStamina();
    }

    // Average performance = (Skill + Stamina) / 2 + variance
    int avgSkill = totalSkill / team.size();
    int avgStamina = totalStamina / team.size();
    int basePerformance = (avgSkill + avgStamina) / 2;
    int variance = generateRandomVariance();

    return basePerformance + variance;
}

void SimulationEngine::simulateMatch(Match& match) {
    // Calculate performance for each team
    int perfA = calculateTeamPerformance(match.getTeamA());
    int perfB = calculateTeamPerformance(match.getTeamB());

    // Determine scores
    int scoreA, scoreB;

    if (perfA > perfB) {
        // Team A wins
        scoreA = 21;
        std::uniform_int_distribution<> dis(10, 20);
        scoreB = dis(randomGenerator);
    }
    else {
        // Team B wins
        scoreB = 21;
        std::uniform_int_distribution<> dis(10, 20);
        scoreA = dis(randomGenerator);
    }

    // Update match
    match.setScoreA(scoreA);
    match.setScoreB(scoreB);
    match.setStatus(Match::COMPLETED);

    // Notify observers
    notifyObservers(match);
}
