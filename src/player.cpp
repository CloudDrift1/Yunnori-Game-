#include "player.hpp"
#include "yut.hpp"
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

/*
- player throws yut using Yut class
(Yut class declares Player class as a friend class)
- The results of the thrown yut are inserted into multiset<YutName>
yut_list;
- If the result is yut or mo, the player should throw one more time.
  (ex1) yut yut geol
  (ex2) mo gae
  (ex3) gae
  (ex4) do
  (ex5) mo yut back-do
*/
void Player::throwYut(Yut &yut) {
    string yuts = yut.throwFourYuts();
    yut_list.insert({yuts});

    if(getAnimalName() == "dog")
    {while(yuts == "yut" || yuts == "mo" || yuts == "geol"){
        yuts = yut.throwFourYuts();
        yut_list.insert({yuts});
    }}

    else {while(yuts == "yut" || yuts == "mo"){
        yuts = yut.throwFourYuts();
        yut_list.insert({yuts});
    }}
}

string Player::getAnimalName(){
    return "None";
}


/* movePlayer
- A function that moves the player's piece based on the yut result.
- The results of the position should be updated in a (vector<int> piece) and an
(int arrived_piece_num).

- Input
    - pos: current position of the player's piece
    - yut: yut result (back-do, do, gae, geol, yut, and mo)
- Output
    - return value: the final position of the player's piece
*/

int Player::movePlayer(int pos, string yut) {

    int final_pos = pos;
    
    if(yut == "back-do"){
        switch (pos){
            case 0:
                final_pos = 0;
                break;
            case 1:
                final_pos = 29;
                break;
            case 29:
                final_pos = 19;
                break;
            case 20:
                final_pos = 5;
                break;
            case 25:
                final_pos = 10;
                break;
            case 27:
                final_pos = 22;
                break;
            default:
                final_pos = pos - 1;
                break;
        }}

    if(yut == "do"){
        switch (pos){
            case 5:
                final_pos = 20;
                break;
            case 10:
                final_pos = 25;
                break;
            case 19:
                final_pos = 29;
                break;
            case 22:
                final_pos = 27;
                break;
            case 29:
                final_pos = 100;
                break;
            case 26:
                final_pos = 22;
                break;
            case 24:
                final_pos = 15;
                break;
            default:
                final_pos = pos + DO;
                break;
        }}

    if(yut == "gae"){

        switch (pos){
            case 5:
                final_pos = 21;
                break;
            case 10:
                final_pos = 26;
                break;
            case 18:
                final_pos = 29;
                break;
            case 19:
                final_pos = 100;
                break;
            case 22:
                final_pos = 28;
                break;
            case 25:
                final_pos = 22;
                break;
            case 26:
                final_pos = 27;
                break;
            case 23:
                final_pos = 15;
                break;
            case 24:
                final_pos = 16;
                break;
            default:
                final_pos = pos + GAE;
                break;
        }}

    if(yut == "geol"){
        switch (pos){
            case 5:
                final_pos = 22;
                break;
            case 10:
                final_pos = 22;
                break;
            case 17:
                final_pos = 29;
                break;
            case 18:
                final_pos = 100;
                break;
            case 19:
                final_pos = 100;
                break;
            case 22:
                final_pos = 29;
                break;
            case 25:
                final_pos = 27;
                break;
            case 26:
                final_pos = 28;
                break;
            case 23:
                final_pos = 16;
                break;
            case 24:
                final_pos = 17;
                break;
            default:
                final_pos = pos + GEOL;
                break;
        }}

    if(yut == "yut"){

        switch (pos){
            case 5:
                final_pos = 23;
                break;
            case 10:
                final_pos = 27;
                break;
            case 16:
                final_pos = 29;
                break;
            case 22:
                final_pos = 100;
                break;
            case 21:
                final_pos = 15;
                break;
            case 23:
                final_pos = 17;
                break;
            case 24:
                final_pos = 18;
                break;
            case 25:
                final_pos = 28;
                break;
            case 26:
                final_pos = 29;
                break;
            default:
                final_pos = pos + YUT;
                break;
        }
        if(pos >= 17 && pos <= 19){
            final_pos = 100;
        }
    }

    if(yut == "mo"){
        switch (pos){
            case 5:
                final_pos = 24;
                break;
            case 10:
                final_pos = 28;
                break;
            case 22:
                final_pos = 100;
                break;
            case 26:
                final_pos = 100;
                break;
            case 25:
                final_pos = 29;
                break;
            case 20:
                final_pos = 15;
                break;
            case 21:
                final_pos = 16;
                break;
            case 23:
                final_pos = 18;
                break;
            case 24:
                final_pos = 19;
                break;
            case 15:
                final_pos = 29;
                break;
            default:
                final_pos = pos + MO;
                break;
        }
        if(pos >= 16 && pos <= 19){
            final_pos = 100;
        }
    }

    if(final_pos >= 30){
        final_pos = 100;
    }

    return final_pos;
}

int AnimalPlayer::moveCow(int pos, string yut){
    int final_pos = pos;
    
    if(yut == "back-do"){

            switch (pos){
            case 0:
                final_pos = 0;
                break;
            case 1:
                final_pos = 29;
                break;
            case 29:
                final_pos = 19;
                break;
            case 20:
                final_pos = 5;
                break;
            case 15:
                final_pos = 24;
                break;
            default:
                final_pos = pos - 1;
                break;
        }
        }

    if(yut == "do"){
        switch (pos){
            case 5:
                final_pos = 20;
                break;
            case 19:
                final_pos = 29;
                break;
            case 22:
                final_pos = 23;
                break;
            case 29:
                final_pos = 100;
                break;
            case 24:
                final_pos = 15;
                break;
            default:
                final_pos = pos + DO;
                break;
        }
        }

    if(yut == "gae"){

        switch (pos){
            case 4:
                final_pos = 20;
                break;
            case 5:
                final_pos = 21;
                break;
            case 18:
                final_pos = 29;
                break;
            case 19:
                final_pos = 100;
                break;
            case 22:
                final_pos = 24;  //not exactly necessary
                break;
            case 23:
                final_pos = 15;
                break;
            case 24:
                final_pos = 16;
                break;
            default:
                final_pos = pos + GAE;
                break;
        }
    }

    if(yut == "geol"){
        switch (pos){
            case 3:
                final_pos = 20;
                break;
            case 4:
                final_pos = 21;
                break;
            case 5:
                final_pos = 22;
                break;
            case 17:
                final_pos = 29;
                break;
            case 18:
                final_pos = 100;
                break;
            case 19:
                final_pos = 100;
                break;
            case 22:
                final_pos = 15;
                break;
            case 23:
                final_pos = 16;
                break;
            case 24:
                final_pos = 17;
                break;
            default:
                final_pos = pos + GEOL;
                break;
        }
        }

    if(yut == "yut"){

        switch (pos){
            case 2:
                final_pos = 20;
                break;
            case 3:
                final_pos = 21;
                break;
            case 4:
                final_pos = 22;
                break;
            case 5:
                final_pos = 23;
                break;
            case 16:
                final_pos = 29;
                break;
            case 22:
                final_pos = 16;
                break;
            case 21:
                final_pos = 15;
                break;
            case 23:
                final_pos = 17;
                break;
            case 24:
                final_pos = 18;
                break;
            default:
                final_pos = pos + YUT;
                break;
        }
        if(pos >= 17 && pos <= 19){
            final_pos = 100;
        }
    }

    if(yut == "mo"){
        switch (pos){
            case 1:
                final_pos = 20;
                break;
            case 2:
                final_pos = 21;
                break;
            case 3:
                final_pos = 22;
                break;
            case 4:
                final_pos = 23;
                break;
            case 5:
                final_pos = 24;
                break;
            case 15:
                final_pos = 29;
                break;
            case 16:
                final_pos = 100;  //duplicate
                break;
            case 22:
                final_pos = 17;
                break;
            case 20:
                final_pos = 15;
                break;
            case 21:
                final_pos = 16;
                break;
            case 23:
                final_pos = 18;
                break;
            case 24:
                final_pos = 19;
                break;
            default:
                final_pos = pos + MO;
                break;
        }
        if(pos >= 16 && pos <= 19){
            final_pos = 100;
        }
    }

    if(final_pos >= 30){
        final_pos = 100;
    }

    return final_pos;
}


void Player::setPiece(int num_pieces){
    for(int i=0; i<num_pieces; i++){
        pieces.push_back(0); 
    }
    not_started_num = num_pieces;
}

vector<int> Player::getPlayerPieces(){
    std::sort(pieces.begin(), pieces.end()); 
    return pieces;}

int Player::getId(){
    return id;
}
void Player::setId(int id_){
    id = id_;
}

void Player::addArrived(){
    arrivedPieces.push_back(0);
    arrived_piece_num += 1;
}

int Player::getArrivedSize(){
    return arrivedPieces.size();
}

multiset<YutName> Player::getYutList(){
    return yut_list;
}

int Player::getArrivedNum(){
    return arrived_piece_num;
}

void Player::resetYutList(){
    yut_list.clear();
}

bool Player::checkWinner(){
    vector<int> playerPiece = getPlayerPieces();
    int count = std::count(playerPiece.begin(), playerPiece.end(), 100);
    int totNumPiece = playerPiece.size();
    if(count == totNumPiece){
        return true;
    }
    return false;
}

void Player::updatePiece(int cur_val, int new_val){

    auto it = std::find(pieces.begin(), pieces.end(), cur_val);
    *it = new_val;
    bool duplicate = false;

   if(cur_val != 0){ while (it != pieces.end()) {
        duplicate = true;
        it = std::find(it + 1, pieces.end(), cur_val);
        *it = new_val;
    } 
    }

    int arrived_num = std::count(pieces.begin(), pieces.end(), 100);
    arrived_piece_num = arrived_num;
}

void Player::updateNotStarted(int num){
    not_started_num += num;
}
int Player::getNotStarted(){
    return not_started_num;
}

void Player::removeUsedYut(string& usedYutName){
    auto it = yut_list.find({usedYutName});
        if (it != yut_list.end()) {
            yut_list.erase(it);
        }
}
void AnimalPlayer::setAnimal(string aniName){
    animal = aniName;
}
void AnimalPlayer::setTurnNum(int num_){
    id = num_;
}
string AnimalPlayer::getID(){
    return ID;
}

string AnimalPlayer::getAnimalName(){
    return animal;
}
int AnimalPlayer::getAnimalType(){
    return animalType;
}