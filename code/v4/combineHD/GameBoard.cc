export module gameboard;
import <iostream>;
import <string>;
import <vector>;
import <cstddef>;
import player;
import square;
import propertyinfo;
using namespace std;

export class GameBoard {
public:
    int timsCups = 0;
    int playerNumber = 2;
    int curidx = 0;
    Player* currPlayer;
    vector<Player> players;
    vector<Square*> buildings;
    const vector<vector<size_t>> monopolyTable = {
        {1, 3}, {6, 8, 9}, {11, 13, 14}, {16, 18, 19}, 
        {21, 23, 24}, {26, 27, 29}, {31, 32, 34}, {37, 39}
    };
    // Basic GameBoard Construction
    GameBoard();
    ~GameBoard();
    bool checkPlayer(const string name, const char token) const;            // 1
    void addPlayer(size_t numPlayer);                                       // 1
    int countPlayer();                                                      // 1
    string getBuildingName(size_t index);                                   // 1
    size_t getBuildingIndex(string buildingName);                           // 1
    int getMonopolyValue(size_t index);                                     // 1
    // target是想要improve的这块地的index
    // To check whether player got all monopoly block or not.
    bool checkMonopoly(size_t target, const Player& pl);                    // 1
    bool checkPlayer(string name);                                          // 1
    bool checkPlayerOwnBuilding(string playerName, string buildingName);    // 1
    
    // Extra
    bool checkSquareType(size_t position);                                  // 1
    bool isResidence(size_t position);                                      // 1
    bool isGym(size_t position);                                            // 1

    // Game command
    void moveStep(int step, Player& pl);                                    // 1
    void trade(Player& pl, string playerName, string buildingName, int money);// 1
    void trade(Player& pl, string playerName, int money, string buildingName);// 1
    void trade(Player& pl, string playerName, string building1, string building2);// 1
    void buyBuilding(size_t index, Player& pl);                             // 1
    void improve(size_t index, Player& pl);                                 // 1
    void sellImprovement(size_t index, Player& pl);
    void mortgage(size_t index, Player& pl);                                // 0
    void unmortgage(size_t index, Player& pl);                              // 0
    vector<size_t> deletePlayer(Player& pl);
    //void bankrupt();
    void assets(const Player& pl);                                          // 1
    void all();                                                             // 1
    int assetEva();
    void auction(size_t index);
    //void save(string filename);

    // print method (helping debug, not quite useful)
    void printPlayers();                                                    // 1
    void printBuildings();                                                  // 1
};
