#pragma once
#ifndef SIMULATION_ENGINE_H
#define SIMULATION_ENGINE_H

#include "Match.h"
#include <random>
#include <vector>

class IMatchObserver {
public:
    virtual ~IMatchObserver() = default;
    virtual void onMatchCompleted(const Match& match) = 0;
};

class SimulationEngine {
private:
    std::vector<IMatchObserver*> observers;
    std::mt19937 randomGenerator;

public:
    SimulationEngine();

  
    void attach(IMatchObserver* observer);
    void detach(IMatchObserver* observer);
    void notifyObservers(const Match& match);


    void simulateMatch(Match& match);

private:
    int calculateTeamPerformance(const std::vector<Player>& team);
    int generateRandomVariance();
};

#endif
