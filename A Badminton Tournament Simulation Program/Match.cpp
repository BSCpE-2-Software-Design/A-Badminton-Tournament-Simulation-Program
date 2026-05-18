#include "Match.h"
#include <iostream>
#include <iomanip>

Match::Match() : type(SINGLES), scoreA(0), scoreB(0), status(PENDING), matchId(0) {}

Match::Match(int id, MatchType type, const std::vector<Player>& tA, const std::vector<Player>& tB)
    : matchId(id), type(type), teamA(tA), teamB(tB), scoreA(0), scoreB(0), status(PENDING) {
}

Match::MatchType Match::getType() const { return type; }
std::vector<Player> Match::getTeamA() const { return teamA; }
std::vector<Player> Match::getTeamB() const { return teamB; }
int Match::getScoreA() const { return scoreA; }
int Match::getScoreB() const { return scoreB; }
Match::MatchStatus Match::getStatus() const { return status; }
int Match::getMatchId() const { return matchId; }

void Match::setScoreA(int score) { scoreA = score; }
void Match::setScoreB(int score) { scoreB = score; }
void Match::setStatus(MatchStatus s) { status = s; }
void Match::addScoreA(int points) { scoreA += points; }
void Match::addScoreB(int points) { scoreB += points; }

std::vector<Player> Match::getWinnerTeam() const {
    return (scoreA > scoreB) ? teamA : teamB;
}

std::vector<Player> Match::getLoserTeam() const {
    return (scoreA > scoreB) ? teamB : teamA;
}

bool Match::isCompleted() const {
    return status == COMPLETED;
}

void Match::display() const {
    std::string typeStr = (type == SINGLES) ? "SINGLES (1v1)" : "DOUBLES (2v2)";
    std::cout << "\nMatch #" << matchId << " [" << typeStr << "]" << std::endl;
    std::cout << "Team A: ";
    for (const auto& p : teamA) {
        std::cout << p.getName() << " ";
    }
    std::cout << " vs Team B: ";
    for (const auto& p : teamB) {
        std::cout << p.getName() << " ";
    }
    std::cout << std::endl;
}

void Match::displayResult() const {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "Match #" << matchId << " Result" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    // Team A
    std::cout << "Team A: ";
    for (size_t i = 0; i < teamA.size(); i++) {
        std::cout << teamA[i].getName();
        if (i < teamA.size() - 1) std::cout << " & ";
    }
    std::cout << std::endl;

    // Team B
    std::cout << "Team B: ";
    for (size_t i = 0; i < teamB.size(); i++) {
        std::cout << teamB[i].getName();
        if (i < teamB.size() - 1) std::cout << " & ";
    }
    std::cout << std::endl;

    // Score
    std::cout << "\nScore: " << scoreA << " - " << scoreB << std::endl;

    if (scoreA > scoreB) {
        std::cout << "Winner: Team A";
    }
    else {
        std::cout << "Winner: Team B";
    }
    std::cout << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}
