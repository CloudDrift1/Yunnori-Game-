#include "game.hpp"
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

/* menuSelect function
This function is used to choose "game start / end program"
The function returns 0 if the user selects the end
program, and returns 1 if the user selects the game start.
*/
int Game::menuSelect() {
    int i;
    while (true) {
        cout << "************************************************************"
             << endl;
        cout << "************************   Menu   **************************"
             << endl;
        cout << "************************************************************"
             << endl;

        cout << "1. game start" << endl;
        cout << "2. end program" << endl;
        cout << "Select the function you want : ";
        cin >> i;
        if (i < 1 || i > 2) {
            cout << "Type an integer from 1 to 2!" << endl;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        if (i == 2) {
            return 0;
        } else {
            run();
        }
    }
    // return 1;
}

/* run function
This function is used to run the game.
The function is called when the user selects the game start.
The function is used to run the game until the game ends.
*/
void Game::run() {
    int num_players{-1}, num_pieces{-1};
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while(true){
        cout<<"number of players (2, 3, 4) : ";
        string ds_;
        getline(std::cin, ds_);
        std::istringstream inss(ds_);
        inss >> num_players;
        if((num_players >=2 && num_players <= 4)){
            player_num = num_players;
        break;
    }
    cout<<"Invalid choice, please try again."<<endl;
    }
    while(true){
        cout << "number of pieces per player (1, 2, 3, 4) : ";
        string ds_;
        getline(cin, ds_);
        std::istringstream inss(ds_);
        if((inss >> num_pieces) && (num_pieces>=1 && num_pieces <= 4)){
            piece_num = num_pieces;
        break;
    }
    cout<<"Invalid choice, please try again."<<endl;
    }

    pPlayer = new Player[player_num];
    for(int i=0; i<player_num; i++){
        pPlayer[i].setPiece(num_pieces);
        pPlayer[i].setId(i);
    }

    // print the board

    Board board = Board();
    board.printBoard();

    printPieceState();

    while(true){

        for(int i=0; i<player_num; i++){

        (pPlayer+i)->throwYut(yut);

        while (!((pPlayer+i)->getYutList().empty())) {

        printCurrentTurn(i);

        cout << "Write down the position of the player to move and yut" << endl;
        cout << "(back-do, do, gae, geol, yut, and mo)" << endl;

        int position; string player_yut;

        cout << ">> position : ";

        string pos_;
        getline(cin, pos_);
        std::istringstream inss(pos_);
        inss >> position;

        cout << ">> yut : ";
        getline(cin, player_yut);

        int new_pos = pPlayer[i].movePlayer(position, player_yut);  //need to clear piece at position
        pPlayer[i].updatePiece(position, new_pos);
        bool gameEnd = pPlayer[i].checkWinner();
        if(gameEnd){
            printWinner(i);
            return;
        }

        (pPlayer+i)->removeUsedYut(player_yut);
        board.updateBoardInfo(position, new_pos, i, yut, pPlayer);

        board.printBoard();
        printPieceState();
        }
    }
    }
}

void Game::printWinner(int num){

    string dispNum;
        if(num == 0){
            dispNum = COLOR_RED + std::to_string(num) + COLOR_DEFAULT;
        }
        else if(num == 1){
            dispNum = COLOR_BLUE + std::to_string(num) + COLOR_DEFAULT;
        }
        else if(num == 2){
            dispNum = COLOR_GREEN + std::to_string(num) + COLOR_DEFAULT;
        }
        else if(num == 3){
            dispNum = COLOR_YELLOW + std::to_string(num) + COLOR_DEFAULT;
        }
    cout << "Player " << num << " wins!" << endl; 
}

/* printCurrentTurn function
This function is used to print the current player's turn.
The function is called when the player's turn is changed.
The function is used to print information of which player's turn, the player's
current piece positions, and the current yut result list.

(example)
Player 0 turn
Piece : 0 1 1 3
Yut : gae
*/
void Game::printCurrentTurn(int player_order) {

    if (player_order == 0) {
        cout << "Player " << COLOR_RED << player_order << COLOR_DEFAULT
             << " turn" << endl;
    }
    else if (player_order == 1) {
        cout << "Player " << COLOR_BLUE << player_order << COLOR_DEFAULT
             << " turn" << endl;
    } else if (player_order == 2) {
        cout << "Player " << COLOR_GREEN << player_order << COLOR_DEFAULT
             << " turn" << endl;
    } else if (player_order == 3) {
        cout << "Player " << COLOR_YELLOW << player_order << COLOR_DEFAULT
             << " turn" << endl;
    } else {
        cout << COLOR_DEFAULT << ' ' << COLOR_DEFAULT;
    }
    cout << "Piece : ";

    vector<int> p_piece = pPlayer[player_order].getPlayerPieces();
    std::sort(p_piece.begin(), p_piece.end());

    for(auto& elem:p_piece){
        if(elem != 100){cout<<elem<<" ";}  //excluding arrived
    }

    cout << '\n';
    cout << "Yut : ";
    for(const auto& elem:pPlayer[player_order].getYutList()){
        cout<<elem.name<<" ";
    }
    cout << '\n';
}

/* printPieceState function
This function is used to print the state of the pieces.
The function is called when the user selects the game start.
The function is used to print the state of the pieces that are not started
and the pieces that have arrived.

(example)
-----------------------------------------
Not started : 
 □  □  □  □  □  □  □  □  □  □  □  □ 
Arrived : 
 ■  ■ 
-----------------------------------------
*/

void Game::printPiece(int id, int num, string box){
    for(int i=0; i<num; i++){
    if (id == 0) {
        cout << COLOR_RED << box << COLOR_DEFAULT;
    } else if (id == 1) {
        cout << COLOR_BLUE << box << COLOR_DEFAULT;
    } else if (id == 2) {
        cout << COLOR_GREEN << box << COLOR_DEFAULT;
    } else if (id == 3) {
        cout << COLOR_YELLOW << box << COLOR_DEFAULT;
    } else {
        cout << COLOR_DEFAULT << ' ' << COLOR_DEFAULT;
    }
    }
}

void Game::printPieceState() {
    cout << "-----------------------------------------" << endl;
    cout << "Not started : ";
    cout << endl;

    for(int i=0; i<player_num; i++){
        vector<int> tempVec = pPlayer[i].getPlayerPieces();
        int p_num = std::count(tempVec.begin(), tempVec.end(), 0);
        int id_ = pPlayer[i].getId();
        printPiece(id_, p_num, " □ ");
    }
    cout<<endl;
    cout << "Arrived : ";
    cout << endl;

    for(int i=0; i<player_num; i++){

        int pa_num = pPlayer[i].getArrivedNum();
        int id_ = pPlayer[i].getId();
        printPiece(id_, pa_num, " ■ ");

    }
    cout<<endl;
    cout << "-----------------------------------------" << endl;
}

// Game::~Game(){
//     delete [] pPlayer;
// }