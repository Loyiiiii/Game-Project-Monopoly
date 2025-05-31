import <iostream>;
import <string>;
import <vector>;
import <cstddef>;
import player;
import gameboard;
using namespace std;

int main() {
    GameBoard* gb = new GameBoard;
    gb->addPlayer(2);
    // gb->all();

    // gb->buyBuilding(1, gb->players[0]);     // AL
    // //gb->buyBuilding(2, gb->players[0]);     // SLC
    // gb->buyBuilding(3, gb->players[0]);     // ML
    // gb->buyBuilding(31, gb->players[0]);
    // gb->buyBuilding(32, gb->players[0]);
    // gb->buyBuilding(34, gb->players[0]);
    // gb->buyBuilding(37, gb->players[0]);
    // gb->all();

    //vector<size_t> v1 = gb->deletePlayer(gb->players[0]);
    //gb->all();
    //gb->buyBuilding(3, gb->players[0]);
    //gb->all();
    /*for (auto curr : v1) {
        cout << curr << ' ';
    }
    cout << endl;*/
    // gb->auction(39);
    // sell improvement test
    /*gb->improve(3, gb->players[0]);
    gb->improve(3, gb->players[0]);
    gb->improve(3, gb->players[0]);
    gb->improve(3, gb->players[0]);
    gb->all();
    gb->sellImprovement(3, gb->players[0]);
    gb->all();
    gb->sellImprovement(3, gb->players[0]);
    gb->all();
    gb->sellImprovement(3, gb->players[0]);
    gb->all();
    gb->sellImprovement(3, gb->players[0]);
    gb->all();
    gb->sellImprovement(3, gb->players[0]);
    gb->all();*/

    /* Mortgage Test
    //gb->buyBuilding(39, gb->players[0]);
    gb->all();
    gb->mortgage(37, gb->players[0]);
    gb->unmortgage(37, gb->players[0]);
    gb->all();
    gb->mortgage(37, gb->players[0]);
    gb->unmortgage(37, gb->players[0]);
    gb->all();
    gb->mortgage(37, gb->players[0]);
    gb->unmortgage(37, gb->players[0]);
    gb->all();
    gb->mortgage(37, gb->players[0]);
    gb->unmortgage(37, gb->players[0]);
    gb->all();
    gb->mortgage(37, gb->players[0]);
    gb->unmortgage(37, gb->players[0]);
    gb->all();*/

    //gb->buyBuilding(6, gb->players[1]);     // ECH
    //gb->buyBuilding(8, gb->players[1]);     // PAS
    //gb->buyBuilding(9, gb->players[1]);     // HH
    //gb->all();
    
    //gb->improve(1, gb->players[0]);
    //gb->improve(1, gb->players[0]);
    //gb->improve(1, gb->players[0]);
    //gb->improve(1, gb->players[0]);
    //gb->all();

    /* Trade Test
    gb->trade(gb->players[0], "Kris", "ML", "ECH");
    gb->improve(1, gb->players[0]);
    gb->all();

    gb->trade(gb->players[0], "Kris", "ECH", 50);
    gb->all();

    gb->trade(gb->players[0], "Kris", 123, "ML");
    gb->improve(3, gb->players[0]);
    gb->all();*/
    // gb->buildings[2]->add_player_to_square('G', 0);
    // gb->buildings[0]->add_player_to_square('$', 4);

    // gb->printGameBoard();
    // int a = gb->rolldice();
    // cout << a << endl;
    gb->newGame();
    
}   
