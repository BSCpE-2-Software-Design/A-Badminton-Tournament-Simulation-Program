#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include "Match.h"
#include "Player.h"
#include <vector>

class Display {
public:
    // Static display methods
    static void displayWelcome();
    static void displayMainMenu();
    static void displayModeSelection();
    static void displayPlayerSelection(const std::vector<Player>& players, int playerCount);
    static void displayTeamSelection(const std::vector<Player>& players, int teamSize);
    static void displayMatchResult(const Match& match);
    static void displayAllMatches(const std::vector<Match>& matches);
    static void displayMatchProgress(int current, int total);
    static void displayError(const std::string& error);
    static void displaySuccess(const std::string& message);
    static void clearScreen();
    static void pressEnter();
};

#endif // DISPLAY_H
