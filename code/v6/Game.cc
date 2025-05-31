export module game;
import <iostream>;
import <fstream>;
import <string>;
import gameboard;
using namespace std;

export class Game {
    GameBoard* game;
    bool testmode = false;
    int curPlayerindex = 0;
public:
    Game();
    ~Game();
    void loadGame(const string filename);
    void start();
    void saveGame(const string filename);
    void newGame();
    void showAsset();
    void showAll();
    void setTestMode();

};