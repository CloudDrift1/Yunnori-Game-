#include "board.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

// Initialize the board
void Board::initializeBoard() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            player_to_board[i][j] = {-1, 0};
        }
    }
}

// If a player's pieces are on the board, print the number of pieces
void Board::printPlayer(int player_order, int num_pieces) {
    if (player_order == 0) {
        cout << COLOR_RED << num_pieces << COLOR_DEFAULT;
    } else if (player_order == 1) {
        cout << COLOR_BLUE << num_pieces << COLOR_DEFAULT;
    } else if (player_order == 2) {
        cout << COLOR_GREEN << num_pieces << COLOR_DEFAULT;
    } else if (player_order == 3) {
        cout << COLOR_YELLOW << num_pieces << COLOR_DEFAULT;
    } else {
        cout << COLOR_DEFAULT << ' ' << COLOR_DEFAULT;
    }
}

/*
- printing the entire board state
(initialized board state)
[ ] - [ ] - [ ] - [ ] - [ ] - [ ]
 | [ ]                     [ ] |
[ ]    .                 .    [ ]
 |       [ ]         [ ]       |
[ ]          .     .          [ ]
 |             [ ]             |
[ ]          .     .          [ ]
 |       [ ]         [ ]       |
[ ]    .                 .    [ ]
 | [ ]                     [ ] |
[ ] - [ ] - [ ] - [ ] - [ ] - [ ]^Start
*/


set<int> makeSet(vector<int> vec){
    set<int> tempSet;
    for(auto& elem:vec){
        tempSet.insert(elem);
    }
    return tempSet;
}


void Board::loadSavedBoard(vector<AnimalPlayer>& paLst){

    for(AnimalPlayer& aPl: paLst){
        vector<int> piecePos = aPl.getPlayerPieces();
        set<int> posLst = makeSet(piecePos);
        int pid = aPl.getId();
        for(int pos:posLst){
            int count = std::count(piecePos.begin(), piecePos.end(), pos);
            if(pos != 0 && pos != 100){
                int_pair coor = board_mapping[pos];
                int i = coor.first; int j = coor.second;
                player_to_board[i][j] = {pid, count};
            }
        }
    }
}

int Board::updateBoardInfo(int prev_pos, int new_pos, int player_id, Yut& player_yut, Player* players){

    // player_to_board;
    int_pair prev_coor = board_mapping[prev_pos];
    int_pair new_coor = board_mapping[new_pos];


    int i_pre = prev_coor.first;
    int j_pre = prev_coor.second;
    int piece_nums = 1;

    if(i_pre != -1 && j_pre != -1) {piece_nums = player_to_board[i_pre][j_pre].second;}
    
    if(i_pre != -1 && j_pre != -1) {player_to_board[i_pre][j_pre] = {-1, 0};}  //update the piece here

    int catch_id = -1;


    if(new_pos != 100){
        if(piece_nums == 0){
        piece_nums = 1;  //putting a new piece
    }

    int i = new_coor.first;
    int j = new_coor.second;

    int_pair cur_val = player_to_board[i][j];

    int prev_pid = cur_val.first;
    

    if((cur_val.second != 0) && (prev_pid != player_id)){ //catching
        catch_id = prev_pid;
        players[prev_pid].updatePiece(new_pos, 0); //back-do check
        players[player_id].throwYut(player_yut);
    }

    if(prev_pid == player_id){
        piece_nums += cur_val.second;  //stacking
    }
    
    player_to_board[i][j] = {player_id, piece_nums};}

    return catch_id;
}


int Board::updateBoardInfo(int prev_pos, int new_pos, int player_id, Yut& player_yut, vector<AnimalPlayer>& players){

    // player_to_board;
    int_pair prev_coor = board_mapping[prev_pos];
    int_pair new_coor = board_mapping[new_pos];


    int i_pre = prev_coor.first;
    int j_pre = prev_coor.second;
    int piece_nums = 1;

    if(i_pre != -1 && j_pre != -1) {piece_nums = player_to_board[i_pre][j_pre].second;}
    
    if(i_pre != -1 && j_pre != -1) {player_to_board[i_pre][j_pre] = {-1, 0};}  //update the piece here

    int catch_id = -1;

    if(new_pos != 100){
        if(piece_nums == 0){
        piece_nums = 1;  //putting a new piece
    }

    int i = new_coor.first;
    int j = new_coor.second;

    int_pair cur_val = player_to_board[i][j];

    int prev_pid = cur_val.first;
    
    string currAnimalName = players[player_id].getAnimalName();
    string prevAnimalName = "None";

    if(prev_pid != -1) {prevAnimalName = players[prev_pid].getAnimalName();}

    if((cur_val.second != 0) && (prev_pid != player_id)){  //catching

        if(prevAnimalName == "pig"){ //pig gets caught

            players[prev_pid].updatePiece(new_pos, 0); //back-do check, remove pig's pieces

            if(prev_pid == player_id){
             piece_nums += cur_val.second;  //stacking - doesn't happen - filler
            }

            player_to_board[i][j] = {player_id, piece_nums};
            players.at(player_id).resetYutList();

            return 0;
        }

        catch_id = prev_pid;
        players[prev_pid].updatePiece(new_pos, 0); //back-do check
        players[player_id].throwYut(player_yut);

        if(currAnimalName == "sheep"){
            players[player_id].throwYut(player_yut);
        }

    }

    if(prev_pid == player_id){
        piece_nums += cur_val.second;  //stacking
    }
    
    player_to_board[i][j] = {player_id, piece_nums};}


    return catch_id;
}

void Board::printBoard() {
 
    for(auto& elem:board_mapping){

        int i = elem.first;
        int j = elem.second;

        if(i == -1 || j == -1){continue;}

        int player_id = player_to_board[i][j].first;
        int piece_nums = player_to_board[i][j].second;

        if(piece_nums != 0){
        if(player_id == 0){
            board[i][j] = std::string("[") + COLOR_RED + std::to_string(piece_nums) + COLOR_DEFAULT + std::string("]");
        }
        else if(player_id == 1){
            board[i][j] = std::string("[") + COLOR_BLUE + std::to_string(piece_nums) + COLOR_DEFAULT + std::string("]");
        }
        else if(player_id == 2){
            board[i][j] = std::string("[") + COLOR_GREEN + std::to_string(piece_nums) + COLOR_DEFAULT + std::string("]");
        }
        else if(player_id == 3){
            board[i][j] = std::string("[") + COLOR_YELLOW + std::to_string(piece_nums) + COLOR_DEFAULT + std::string("]");
        }
    }
    else{
        board[i][j] = "[ ]";
    }
    }
    for(int i=0; i<ROW; i++){
        for(int j=0; j<=COL; j++){
            cout<<board[i][j];
        }
        cout<<endl;
    }
}

vector<int_pair> Board::getBoardMap(){
    return board_mapping;
}

// void Board::clearPiece(int_pair){

// }