#include "game.hpp"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    int game_type;
    Game *game;
    cout << "************************************************************"
         << endl;
    cout << "************************************************************"
         << endl;
    cout << "*************   Welcome to Yunnori game   ****************"
         << endl;
    cout << "************************************************************"
         << endl;
    cout << "************************************************************"
         << endl;

    cout << "1. Yunnori Basic" << endl;
    cout << "2. Yunnori Advanced" << endl;

    while (true) {
        cout << "Choose a game to play (1, 2) : ";
        cin >> game_type;

        if (game_type == 1) {
            game = new Game();
            cout << "You will play a normal Yunnori!" << endl;
            break;
        } else if (game_type == 2) {
            game = new GameExtension();
            cout << "You will play Yunnori advanced version!" << endl;
            break;
        } else {
            cout << "Enter only 1 or 2." << endl;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    while (1) {
        int result = game->menuSelect();
        if (result == 0) {
            cout << "Game finished!" << endl;
            delete game;
            break;
        }
    }
    return 0;
}