#include "Display.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

void Display::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Display::displayWelcome() {
    clearScreen();
    std::cout << std::string(80, '=') << std::endl;
    std::cout << std::setw(50) << "BADMINTON TOURNAMENT SIMULATOR" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "\nWelcome to the Enhanced Badminton Tournament Simulator!" << std::endl;
    std::cout << "Choose your players and compete in exciting tournaments." << std::endl;
    std::cout << std::string(80, '=') << std::endl << std::endl;
}

void Display::displayMainMenu() {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "MAIN MENU" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "1. Start Tournament" << std::endl;
    std::cout << "2. View Available Players" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "Enter your choice (1-3): ";
}

void Display::displayModeSelection() {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "SELECT TOURNAMENT MODE" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "1. SINGLES (1v1) - One on one matches" << std::endl;
    std::cout << "2. DOUBLES (2v2) - Two on two matches" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "Enter your choice (1-2): ";
}

void Display::displayPlayerSelection(const std::vector<Player>& players, int playerCount) {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "SELECT " << playerCount << " PLAYER(S) FOR YOUR TEAM" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    std::cout << std::left << std::setw(3) << "ID"
        << std::setw(20) << "Name"
        << std::setw(15) << "Skill"
        << std::setw(15) << "Stamina" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    for (const auto& player : players) {
        std::cout << std::left << std::setw(3) << player.getId()
            << std::setw(20) << player.getName()
            << std::setw(15) << player.getSkillLevel()
            << std::setw(15) << player.getStamina() << std::endl;
    }
    std::cout << std::string(80, '=') << std::endl;
}

void Display::displayTeamSelection(const std::vector<Player>& players, int teamSize) {
    std::cout << "\nYour selected team (" << teamSize << "/" << teamSize << "):" << std::endl;
    for (const auto& player : players) {
        std::cout << "  - " << player.getName()
            << " (Skill: " << player.getSkillLevel()
            << ", Stamina: " << player.getStamina() << ")" << std::endl;
    }
}

void Display::displayMatchResult(const Match& match) {
    std::cout << "\n" << std::string(80, '-') << std::endl;

    // Team A
    std::cout << "Team A: ";
    for (size_t i = 0; i < match.getTeamA().size(); i++) {
        std::cout << match.getTeamA()[i].getName();
        if (i < match.getTeamA().size() - 1) std::cout << " & ";
    }
    std::cout << " | Score: " << match.getScoreA() << std::endl;

    // Team B
    std::cout << "Team B: ";
    for (size_t i = 0; i < match.getTeamB().size(); i++) {
        std::cout << match.getTeamB()[i].getName();
        if (i < match.getTeamB().size() - 1) std::cout << " & ";
    }
    std::cout << " | Score: " << match.getScoreB() << std::endl;

    //Winner
    if (match.getScoreA() > match.getScoreB()) {
        std::cout << "\n*** WINNER: Team A ***" << std::endl;
    }
    else {
        std::cout << "\n*** WINNER: Team B ***" << std::endl;
    }
}

void Display::displayAllMatches(const std::vector<Match>& matches) {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "ALL MATCH RESULTS" << std::endl;
    std::cout << std::string(80, '=') << std::endl;

    for (size_t i = 0; i < matches.size(); i++) {
        std::cout << "\nMatch " << (i + 1) << ":" << std::endl;
        displayMatchResult(matches[i]);
    }
    std::cout << std::string(80, '=') << std::endl;
}

void Display::displayMatchProgress(int current, int total) {
    std::cout << "\n[Match " << current << " of " << total << "]" << std::endl;
}

void Display::displayError(const std::string& error) {
    std::cout << "\n[ERROR] " << error << std::endl;
}

void Display::displaySuccess(const std::string& message) {
    std::cout << "\n[SUCCESS] " << message << std::endl;
}

void Display::pressEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}
