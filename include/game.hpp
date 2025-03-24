#include "board.hpp"
#include "player.hpp"
#include "yut.hpp"
#include <algorithm>
#include <string>
#include <vector>
#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

using namespace std;

struct GameState{
    set<string> players;
    vector<string> playerOrders;
    map<string, string> playerAnimal;
    map<string, vector<int>> playerState;
    map<string, int> animalType;
    int turn;
};

class Game {

  public:
    Game() {}
    ~Game() {}
    virtual int menuSelect();
    void run();
    virtual void printPieceState();
    virtual void printCurrentTurn(int player_order);
    virtual void printPiece(int, int, string);
    void printWinner(int);
  protected:
    int player_num;
    int piece_num;
    Board board;
    Yut yut = Yut(0.5);

  private:
    Player *pPlayer;
};

class GameExtension : public Game {

  public:
    int menuSelect() override;
    bool login(const std::map<std::string, std::string> &);
    void run();

    GameExtension();
    vector<string> getLoggedInList() const;
    map<string, string> getInfoMap();
    void parseInfoMap();
    void addLoggedInPlayer(string&);
    bool printLoggedIn();
    void parseSavedGames();
    set<string> makePlayerSet(vector<string>);
    void assignAnimals();
    string playerToAnimalMatch(int);
    int loadSavedGame(bool, int, Board&);
    void printPlayerAnimalState();
    map<string, string> getPair() const;

    void parseAnimalPlayers();
    void addAnimalPlayer(AnimalPlayer&);
    void loadNewGame(Board&);
    void printCurrentTurn(int);

    vector<AnimalPlayer> getPlayers() const;
    void printPieceState();
    bool saveExitPrompt(int, int);
    void resetGame();
    bool saveGame(int, int);

    void removeLoadedGame(const std::string&, int);
    void removeExistingGame(const std::string&, string, int);
    
    

  private:
    vector<string> loggedInList;
    map<string, string> userInfoMap;
    vector<GameState> savedGames;
    const vector<GameState>& getSavedGames() const;
    map<string, string> playerAnimalPair;
    map<string, int> playerAnimalNum;
    // AnimalPlayer *aPlayer;
    vector<AnimalPlayer> aPlayer;

};

#endif
