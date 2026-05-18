# Badminton-Tournament-Simulator
```mermaid
sequenceDiagram
    autonumber
    participant BT as Badminton Tournament Simulator
    participant Sched as RoundRobinScheduler
    participant Eng as BadmintonSimulationEngine
    participant Track as StandingTracker
    participant Disp as DisplayStandings
    participant Match as Match
    participant Player as Player

    Note over BT: Tournament Flow Starts
    BT->>+Sched: GenerateSchedule()
    Sched->>Sched: Nested Loop: Every player vs every other
    Sched-->>-BT: List<Match>
    loop For Each Match in Schedule
        BT->>+Eng: SimulateMatch(match)
        Eng->>+Match: Calculate Performance<br/>Home: Power + Variance(1-20)<br/>Away: Agility + Variance(1-20)
        Match->>+Eng: Determine Winner<br/>Higher perf = 21 points<br/>Loser = Random(10-20)
        Eng->>+Match: Set IsCompleted = true<br/>Set HomeScore, AwayScore
        Match-->>-Eng: Updated Match
        Eng->>+Track: RecordMatch(match)
        Track->>+Player: Update Winner Stats<br/>(Wins++, PointsScored += score)
        Track->>+Player: Update Loser Stats<br/>(PointsScored += score)
        Player-->>-Track: Stats Updated
        Track-->>-Eng: Match Recorded
        Eng->>+Disp: DisplayMatchResult(match)
        Disp-->>-Eng: Result Displayed
        Eng-->>-BT: Match Completed
    end
    Note over BT,Disp: Final Standings
    BT->>+Disp: DisplayStandings()
    Disp->>Disp: Sort Players by Wins
    Disp-->>-BT: Print Leaderboard<br/>(Name, Wins, PointsScored)
    Note over BT: Tournament Complete
```
```mermaid
---



config:
layout: elk
---
graph TB
subgraph interfaces["Interfaces (Contract Layer)"]
IMatchObserver["IMatchObserver
+ OnMatchCompleted(match)"]
end

subgraph models["Domain Models (Data Layer)"]
Player["Player
+ Name: string
+ Stamina: int
+ SkillLevel: int
+ Wins: int
+ TotalPoints: int"]
Match["Match
+ SideA: Player
+ SideB: Player
+ ScoreA: int
+ ScoreB: int"]
end

subgraph components["Core Logic (Component Layer)"]
TournamentScheduler["TournamentScheduler
+ CreateRoundRobin(players)
Returns: List of Matches"]
BadmintonEngine["BadmintonEngine
- _observers: List
- _random: Random
+ Attach(observer)
+ RunMatch(match)
- Notify(match)"]
StatTracker["StatTracker
+ OnMatchCompleted(match)
+ PrintLeaderboard(players)"]
end

subgraph coordinator["Coordinator (Main Entry)"]
Program["Program
+ Main()"]
end

Player -->|"2 players per match"| Match
TournamentScheduler -->|"generates"| Match
BadmintonEngine -->|"processes"| Match
StatTracker -->|"implements"| IMatchObserver
BadmintonEngine -->|"notifies"| StatTracker
Program -->|"orchestrates"| TournamentScheduler
Program -->|"orchestrates"| BadmintonEngine
Program -->|"orchestrates"| StatTracker
Program -->|"populates"| Player

classDef interface stroke:#a78bfa,fill:#f5f3ff,color:#1e1b4b
classDef model stroke:#2dd4bf,fill:#f0fdfa,color:#1e1b4b
classDef component stroke:#fb923c,fill:#fff7ed,color:#1e1b4b
classDef coord stroke:#f87171,fill:#fef2f2,color:#1e1b4b
classDef section stroke:#818cf8,fill:#eef2ff,color:#1e1b4b

class IMatchObserver interface
class Player,Match model
class TournamentScheduler,BadmintonEngine,StatTracker component
class Program coord
class interfaces,models,components,coordinator section
