#include "game.hpp"
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;


GameExtension::GameExtension(){
   piece_num = 4;
}
bool GameExtension::login(const std::map<std::string, std::string> &lookUpMap) {

   string inputID, inputPWD;

   cout << "ID : ";
   getline(cin, inputID);
   cout << "PASSWORD : ";
   getline(cin, inputPWD);

   auto mapIt = lookUpMap.find(inputID);

   if((mapIt != lookUpMap.end()) && (inputPWD == mapIt->second)){
      cout << "Login Succeed!" << endl;
      addLoggedInPlayer(inputID);
      return true;
   }
   else{
      cout << "Login Failed!" << endl;
      return false;
   }
}

/* menuSelect function
This function is used to choose "game start / login / end program"
The function returns 0 if the user selects the end
program, and returns 1 if the user selects the game start.
*/

int GameExtension::menuSelect() {
    int i;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    parseInfoMap();
    std::map<std::string, std::string> storedUserInfo = getInfoMap();
    while (true) {
        cout << "************************************************************"
             << endl;
        cout << "************************   Menu   **************************"
             << endl;
        cout << "************************************************************"
             << endl;

        cout << "Logged-in ID List : ";
        bool log_num = printLoggedIn();
   
        cout << "1. game start" << endl;
        cout << "2. login" << endl;
        cout << "3. end program" << endl;
        cout << "Select the function you want : ";

        int num; 
        string in_;
        getline(cin, in_);
        std::istringstream inss(in_);
        inss >> num;

        if(num == 3){
         return 0;
        }
        else if(num == 1 || num == 2){

            if(num == 1 && log_num){
               run(); 
               resetGame();
            }
            else if(num == 1 && !log_num){
               cout << "More than 1 player is needed to start the game" << endl;
            }
            if(num == 2){
               login(storedUserInfo);
            }
        }
    }
    return 1;
}

void GameExtension::resetGame(){
   aPlayer.clear();
   loggedInList.clear();
}

/*
This function is used to run the game.
The function is called when the user selects the game start.
The function is used to run the game until the game ends.
*/

set<string> GameExtension::makePlayerSet(vector<string> inputList){
   set<string> temp;
   for(auto& elem: inputList){
      temp.insert(elem);
   }
   return temp;
}

map<string, string> GameExtension::getPair() const{
   return playerAnimalPair;
}

void GameExtension::assignAnimals(){
   vector<string> pList = getLoggedInList();
   for(int i=0; i<pList.size(); i++){
      int num; 
      string in_;
      string pname = pList.at(i);
      cout << "Select animal type of " << pname << endl;
      cout << "(0: pig, 1: dog, 2: sheep, 3:cow) : ";
      getline(cin, in_);
      std::istringstream inss(in_);
      inss >> num;
      playerAnimalPair[pname] = playerToAnimalMatch(num);
   }
}

void GameExtension::printPlayerAnimalState(){
   vector<AnimalPlayer>  pList = getPlayers();
   // map<string, string> PApairs = getPair();
   cout << "-----------------------------------------" << endl;
   for(int i=0; i<pList.size(); i++){
      string pName = pList.at(i).getID();
      cout<<pName<<"("<<pList.at(i).getAnimalName()<<")"<<" ";
   }
   cout<<endl;
}

vector<AnimalPlayer> GameExtension::getPlayers() const{
   return aPlayer;
}

void GameExtension::addAnimalPlayer(AnimalPlayer& ap){
   aPlayer.push_back(ap);
}

void GameExtension::loadNewGame(Board& b){
   vector<string> pList = getLoggedInList();

   for(int i=0; i<pList.size(); i++){
         int num; 
         string in_;
         string pname = pList.at(i);
         cout << "Select animal type of " << pname << endl;
         cout << "(0: pig, 1: dog, 2: sheep, 3:cow) : ";
         getline(cin, in_);
         std::istringstream inss(in_);
         inss >> num;
         playerAnimalPair[pname] = playerToAnimalMatch(num);
         string animName = playerToAnimalMatch(num);
         vector<int> pla_piece = {0, 0, 0, 0};
         AnimalPlayer tempAP = AnimalPlayer(pname, i, num, pla_piece);
         tempAP.setAnimal(animName);
         addAnimalPlayer(tempAP);
      }
}

int GameExtension::loadSavedGame(bool stored, int loc, Board& b){

   Board advBoard = Board();
   const std::vector<GameState>& prevGames = getSavedGames();
   int turn = 0;
   if(stored && loc != -1){

      GameState prevGame = prevGames.at(loc);
      turn = prevGame.turn;
      vector<string> playerList = getLoggedInList();

      for(int i=0; i<playerList.size(); i++){
         string name = playerList.at(i);
         vector<int> pla_piece = prevGame.playerState[name];
         string p_anim = prevGame.playerAnimal[name];
         int playerAn = prevGame.animalType[name];
         AnimalPlayer tempAP = AnimalPlayer(name, i, playerAn, pla_piece);
         // string animName = playerToAnimalMatch(num);
         tempAP.setAnimal(p_anim);
         addAnimalPlayer(tempAP);
      }
   }

   vector<AnimalPlayer> pLst = getPlayers();
   b.loadSavedBoard(pLst);
   return turn;
}

void printVec(vector<int> v){
   for(auto& elem:v){
      cout<<elem<<" ";
   }
   cout<<endl;
}

void GameExtension::printPieceState() {
    cout << "-----------------------------------------" << endl;
    cout << "Not started : ";
    cout << endl;
    vector<AnimalPlayer> pList = getPlayers(); 
    bool empty = true;
    for(int i=0; i<pList.size(); i++){

        vector<int> tempVec = pList.at(i).getPlayerPieces();
        int p_num = std::count(tempVec.begin(), tempVec.end(), 0);
        int id_ = pList.at(i).getId();
        printPiece(id_, p_num, " □ ");
    }
    cout<<endl;
    cout << "Arrived : ";
    cout << endl;

    for(int i=0; i<pList.size(); i++){
         int pa_num = pList.at(i).getArrivedNum();
         int id_ = pList.at(i).getId();
         printPiece(id_, pa_num, " ■ ");
    }
    cout<<endl;
    cout << "-----------------------------------------" << endl;
}

void GameExtension::printCurrentTurn(int player_order) {
    if (player_order == 0) {
        cout << "Player " << COLOR_RED << player_order << COLOR_DEFAULT<< " "<< aPlayer.at(player_order).getID()
             << " turn" << endl;
    }
    else if (player_order == 1) {
        cout << "Player " << COLOR_BLUE << player_order << COLOR_DEFAULT<< " "<< aPlayer.at(player_order).getID()
             << " turn" << endl;
    } else if (player_order == 2) {
        cout << "Player " << COLOR_GREEN << player_order << COLOR_DEFAULT<< " "<< aPlayer.at(player_order).getID()
             << " turn" << endl;
    } else if (player_order == 3) {
        cout << "Player " << COLOR_YELLOW << player_order << COLOR_DEFAULT<< " "<< aPlayer.at(player_order).getID()
             << " turn" << endl;
    } else {
        cout << COLOR_DEFAULT << ' ' << COLOR_DEFAULT;
    }
    cout << "Piece : ";

    vector<int> p_piece = aPlayer[player_order].getPlayerPieces();
    std::sort(p_piece.begin(), p_piece.end());

    for(auto& elem:p_piece){
        if(elem != 100){cout<<elem<<" ";}  //excluding arrived
    }

    cout << '\n';
    cout << "Yut : ";
    for(const auto& elem:aPlayer[player_order].getYutList()){
        cout<<elem.name<<" ";
    }
    cout << '\n';
}


void GameExtension::run() {
   parseSavedGames();
   Board advBoard = Board();
   int turnNum = 0;
   vector<AnimalPlayer> advPlayers = getPlayers();

   
   const std::vector<GameState>& prevGames = getSavedGames();
   std::vector<std::string> users = getLoggedInList();
   set<string> userSet = makePlayerSet(users);
   bool prevGamePresent = false;
   int gameLoc = -1;

   for(int i=0; i<prevGames.size(); i++){
      if(userSet == prevGames.at(i).players){
         prevGamePresent = true;
         gameLoc = i;
         break;
      }
      }

   if(prevGamePresent){
   cout << "There is a saved game. Start a new game (0) / Resume (1) : ";
   int num; 
   string in_;
   getline(cin, in_);
   std::istringstream inss(in_);
   inss >> num;

      if(num == 1){
         turnNum = loadSavedGame(1, gameLoc, advBoard);
         const string fname = "../data/game_info.txt";
         removeLoadedGame(fname, gameLoc);  //load saved game and remove record
      }
      else{
         loadNewGame(advBoard);
         const string fname = "../data/game_info.txt";
         removeLoadedGame(fname, gameLoc);} //start new game and remove record
   }

   else{
      loadNewGame(advBoard); //start new game
   }

   advBoard.printBoard();
   printPlayerAnimalState();
   printPieceState();


      while(true){

         for(int i=turnNum; i<users.size(); i++){ //only loops from current turn, reset at end

         aPlayer.at(i).throwYut(yut);
         string playerName = aPlayer.at(i).getAnimalName();
    
         while (!(aPlayer.at(i).getYutList().empty())) {

            bool save = saveExitPrompt(gameLoc, i);
            if(save){
               return;
            }
            else{
               advBoard.printBoard();
               printPlayerAnimalState();
               printPieceState();
            }

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

            string player_animal_name = aPlayer.at(i).getAnimalName();

            int new_pos = aPlayer.at(i).movePlayer(position, player_yut);//need to clear piece at position

            if(player_animal_name == "cow"){
               new_pos = aPlayer.at(i).moveCow(position, player_yut);
            }

            aPlayer.at(i).updatePiece(position, new_pos);
            bool gameEnd = aPlayer.at(i).checkWinner();
            if(gameEnd){
            printWinner(i);
            return;
            }

            aPlayer.at(i).removeUsedYut(player_yut);

            advBoard.updateBoardInfo(position, new_pos, i, yut, aPlayer);
            advBoard.printBoard();
            printPlayerAnimalState();
            printPieceState();
            }
            }
            turnNum = 0;  //reset
         }
}

vector<std::string> reloadGames(const std::string& filename) {
    vector<std::string> lines;
    std::ifstream file(filename);
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return lines;
}
void writeFile(const std::string& filename, const std::vector<std::string>& lines) {
    std::ofstream file(filename);
    for (const auto& line : lines) {
        file << line << std::endl;
    }
    file.close();
}

void GameExtension::removeLoadedGame(const std::string& filename, int i){
   std::vector<std::string> lines = reloadGames(filename);
   int stored_size = lines.size();

     if (i < stored_size) {
        if(i != -1){lines.erase(lines.begin() + i);}
        writeFile(filename, lines);
    } else {
        std::cerr << "Error: Line index out of range." << std::endl;
    }
}

void GameExtension::removeExistingGame(const std::string& filename, string addLine, int i) {
    std::vector<std::string> lines = reloadGames(filename);

    int stored_size = lines.size();

    if (i < stored_size) {
        lines.push_back(addLine);
        writeFile(filename, lines);
    } else {
        std::cerr << "Error: Line index out of range." << std::endl;
    }
}
string vecToStr(vector<int> intVec){
   string res;
   for(auto elem:intVec){
      res += std::to_string(elem) + " ";
   }
   return res;
}
bool GameExtension::saveGame(int loc, int i){
   string res;
   string fname = "../data/game_info.txt";
   vector<AnimalPlayer> plaState = getPlayers();
   string names, pos, turn;
   for(auto elem:plaState){
      names += elem.getID() + " "; 
      pos += elem.getID() + " " + std::to_string(elem.getAnimalType()) + " " + vecToStr(elem.getPlayerPieces()) + "| "; //sort pieces
   }
   res = names + "| " + pos + std::to_string(i);
   removeExistingGame(fname, res, loc);
   return true;
}
bool GameExtension::saveExitPrompt(int saveLoc, int turn){
   cout << "Continue (0) / Save and Exit the game (1) : ";
   int num = 0;
   string response;
   getline(cin, response);
   std::istringstream inss(response);
   inss >> num;
   if(num == 0){
      return 0;
   }
   else if(num == 1){
      bool flag = saveGame(saveLoc, turn);
      if(flag) {cout << "Game saved successfully!" << endl;}
      return 1;
   }
   else{
      cout<<"Invalid input!"<<endl;
      return -1; 
   }
}
void GameExtension::parseInfoMap(){

    ifstream user_file;
    stringstream uss;
    string file_name = "../data/user_info.txt";
    user_file.open(file_name);

    if(user_file.fail()){
        std::cout<<"Failed to parse "<< file_name <<" file."<<std::endl;
        exit(1);
    }

    if(user_file.is_open()){

        uss<<user_file.rdbuf();

        std::string line;
        int lineNum = 0;

        while (std::getline(uss, line)) { 
            if(line == ""){break;}
            lineNum++;

            std::istringstream inss(line);

            string user_id, user_pwd;
            inss >> user_id >> user_pwd;
            userInfoMap[user_id] = user_pwd;

        }
        }
        user_file.close();
}

bool GameExtension::printLoggedIn(){
   if(loggedInList.size() == 0){
      cout << "No player is logged in" << endl;
   }
   else{
      for(auto& elem:loggedInList){
         cout<<elem<<" ";
      }
      cout<<endl;
   }

   if(loggedInList.size() >= 2){
      return true;
   }
   else{
      return false;
   }
}

std::vector<std::string> GameExtension::getLoggedInList() const {
        return loggedInList;
    }

map<string, string> GameExtension::getInfoMap(){
   return userInfoMap;
}
void GameExtension::addLoggedInPlayer(string& userName){
   loggedInList.push_back(userName);
}

string GameExtension::playerToAnimalMatch(int num){
    if(num == 0){
        return "pig";
    }
    else if(num == 1){
        return "dog";
    }
    else if(num == 2){
        return "sheep";
    }
    else if(num == 3){
        return "cow";
    }
    else{
        return "None";
    }
}

void GameExtension::parseSavedGames(){

   ifstream game_file;
   string file_name = "../data/game_info.txt";
   game_file.open(file_name);
   stringstream uss;
   string name;

   if(game_file.is_open()){

      uss<<game_file.rdbuf();

      std::string line;

      while (std::getline(uss, line)) { 

         if(line == ""){break;}

         GameState game;

         std::istringstream ss(line);
         std::string nameList;
         std::getline(ss, nameList, '|');
         std::istringstream nss(nameList);
         string name;

         while(nss >> name){
               game.playerOrders.push_back(name);
               game.players.insert(name); //set finished here
         }

         set<string> tempSet = game.players;
         string peicePosList;

         for(int i=0; i<tempSet.size(); i++){
               getline(ss, peicePosList, '|');
               std::istringstream pss(peicePosList);
               string pName;
               int position;
               int animalType;
               pss >> pName;
               pss >> animalType;
               game.playerAnimal[pName] = playerToAnimalMatch(animalType);
               game.animalType[pName] = animalType;
               vector<int> playerScores;
               while(pss >> position){
                  playerScores.push_back(position);
               }
               game.playerState[pName] = playerScores;
         }

         string gameTurn;
         getline(ss, gameTurn);
         game.turn = std::stoi(gameTurn);

         savedGames.push_back(game);
      }
   }
   game_file.close();

}

const vector<GameState>& GameExtension::getSavedGames() const{
   return savedGames;
}
