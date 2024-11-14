// PenaltyShootoutLobby.h

#ifndef PENALTYSHOOTOUTLOBBY_H
#define PENALTYSHOOTOUTLOBBY_H

#include <string>
#include <vector>

// declaration of Player class
class Player;

// PenaltyShootoutLobby class definition
class PenaltyShootoutLobby {
private:
    int gameDuration; // Duration of the penalty shootout session in seconds
    int rounds; // Number of rounds in the session
    std::string sessionStatus; // Status of the session (waiting, active, completed)
    int score; // Player's accumulated score during the session

public:
    // Constructor
    PenaltyShootoutLobby(int duration, int numRounds);

    // Methods
    void startSession();
    void endSession();
    void updateScore(int points);
    void selectRole(const std::string& role);
    void matchmakingStatus();
};

// Player class definition
class Player {
private:
    std::string playerID;
    std::string name;
    std::string role; // "Shooter" or "Defender"
    int score;
    std::string performance; // "Excellent", "Good", "Average"

public:
    // Constructor
    Player(std::string id, std::string playerName);

    // Methods
    void shootBall();
    void defendGoal();
    void updatePerformance();
    void setRole(const std::string& playerRole);
};

// Matchmaking class definition
class Matchmaking {
private:
    std::string status; // "waiting", "matched"
    std::vector<Player> playerQueue;

public:
    // Constructor
    Matchmaking();

    // Methods
    void startMatchmaking();
    void assignOpponent(Player& player);
};

// Leaderboard class definition
class Leaderboard {
private:
    std::vector<Player> leaderboardList;
    int roundScore;

public:
    // Constructor
    Leaderboard();

    // Methods
    void updateLeaderboard(Player& player);
    void displayLeaderboard();
};

// PracticeMode class definition
class PracticeMode {
private:
    bool isEnabled;
    int gameDuration;
    int rounds;

public:
    // Constructor
    PracticeMode(bool enabled, int duration, int numRounds);

    // Methods
    void startPractice();
    void endPractice();
    void selectRole(const std::string& role);
};

#endif // PENALTYSHOOTOUTLOBBY_H
