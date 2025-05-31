import <iostream>;
import <fstream>;
import <string>;
import game;
using namespace std;

int main(int argc, char* argv[]) {
    cout << "Welcome to Watopoly! The race to fortune begins now—buy, trade, and conquer!" << endl << endl;
    Game* game = new Game;
    if (argc > 1) {
        string arg = argv[1];
        if (arg == "-testing") {
            game->setTestMode();
            if (argc > 2) {
                string arg2 = argv[2];
                if (arg2 == "-loadfile") {
                    string filename = argv[3];
                    game->loadGame(filename);
                    game->start();
                }
            } else {
                game->start();
            }
        } else if (arg == "-loadfile") {
            string filename = argv[2];
            game->loadGame(filename);
            cout << "The previous Game has been loaded, please continue!"  << endl << endl;
            game->start();
        } else {
            game->setTestMode();
            game->newGame();
            game->start();
        }
    }
    else {
        game->newGame();
        game->start();
    }
    delete game;
}





