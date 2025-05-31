import <iostream>;
import <fstream>;
import <string>;
import game;
using namespace std;

int main(int argc, char* argv[]) {
    cout << "Welcome to Watopoly! The race to fortune begins now—buy, trade, and conquer!";
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

                }
            }
        }
        else if (arg == "-loadfile") {
            string filename = argv[2];
            game->loadGame(filename);
        }
    }
    else {
        game->newGame();
    }
    game->start();
    delete game;
}
