#include <string>
#include <vector>
#ifndef __BOARD_H_INCLUDED__
#define __BOARD_H_INCLUDED__

#include "player.hpp"

using namespace std;
typedef pair<int, int> int_pair;
#define COLOR_RED "\033[31m"    /* Red */
#define COLOR_YELLOW "\033[33m" /* Yellow */
#define COLOR_BLUE "\033[94m"   /* Blue */
#define COLOR_GREEN "\033[32m"  /* Green */
#define COLOR_DEFAULT "\033[0m" /* Default */

class Board {

  public:
    Board() {
        player_to_board.assign(ROW, vector<int_pair>(COL, {-1, 0}));
        board_mapping = {{-1, -1}, {8, 10}, {6, 10}, {4, 10}, {2, 10},
                         {0, 10},  {0, 8},  {0, 6},  {0, 4},  {0, 2},
                         {0, 0},   {2, 0},  {4, 0},  {6, 0},  {8, 0},
                         {10, 0},  {10, 2}, {10, 4}, {10, 6}, {10, 8},
                         {1, 9},   {3, 7},  {5, 5},  {7, 3},  {9, 1},
                         {1, 1},   {3, 3},  {7, 7},  {9, 9},  {10, 10}};
    
    board = vector<vector<string>>(ROW, vector<string>(COL+1, "   "));
    for(int i=0; i<ROW; i++){
        for(int j=0; j<COL; j++){

            if((j%2) && (i == 0 || i == ROW-1)){
               board[i][j] = " - ";
            }

            if((i%2) && (j == 0 || j == COL-1)){
               board[i][j] = " | ";
            }

            if( (i==j) && !(i%2) && (i != 0) && (i != ROW-1)){
                board[i][j] = " . ";
            }
            if((i+j == ROW-1) && (i != 0) && (i != ROW-1)){
                board[i][j] = " . ";
            }
        }
     }
    board[ROW-1][COL] = "^Start";
    initializeBoard();
    
    }
    // int updateBoardInfo(int_pair, int_pair, int, Player*);
    int updateBoardInfo(int, int, int, Yut&, Player*);
    int updateBoardInfo(int, int, int, Yut&, vector<AnimalPlayer>&);
    void initializeBoard();
    void printBoard();
    vector<int_pair> getBoardMap();

    void clearPiece(int_pair);
    void loadSavedBoard(vector<AnimalPlayer>&, Board&);
    void loadSavedBoard(vector<AnimalPlayer>&);

  private:
    const int ROW = 11;
    const int COL = 11;
    vector<int_pair> board_mapping;
    vector<vector<int_pair>> player_to_board;
    void printPlayer(int player_order, int num_pieces);
    vector<vector<string>> board;
};

#endif
