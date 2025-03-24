#include "yut.hpp"
#include <algorithm>
#include <set>
#include <string>
#include <vector>
#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__
using namespace std;

#define BACK_DO 0
#define DO 1
#define GAE 2
#define GEOL 3
#define YUT 4
#define MO 5

class Player {

  public:
    Player() {}
    Player(int idNum, vector<int> pieces_) : id(idNum), pieces(pieces_) {}
    virtual int movePlayer(int pos, string yut);
    virtual void throwYut(Yut &yut);

    virtual void setPiece(int);
    virtual vector<int> getPlayerPieces();
    void setId(int);
    int getId();

    void addArrived();
    int getArrivedSize();
    int getArrivedNum();
    multiset<YutName> getYutList();
    void resetYutList();
    void updatePiece(int, int);
    // void setNotStarted();
    void updateNotStarted(int);
    int getNotStarted();

    void removeUsedYut(string& usedYutName);
    bool checkWinner();
    virtual string getAnimalName();

  protected:
    vector<int> pieces;
    int arrived_piece_num = 0;
    multiset<YutName> yut_list;

    int id;
    vector<int> arrivedPieces;
    int not_started_num = 0;
    string animal = "None"; 

  private:
};

class AnimalPlayer : public Player {
    // 0:pig 1:dog 2:sheep 3:cow

    public:
      AnimalPlayer(string name_, int turn_, int animal_, vector<int> pieces_): Player(turn_, pieces_), ID(name_), animalType(animal_) {}
      void setAnimal(string);
      string getID();
      string getAnimalName();
      int getAnimalType();
      void setTurnNum(int);
      int moveCow(int, string);

    private:
      string ID;
      int animalType; 
      int totNumPieces = 4;
    
};

#endif