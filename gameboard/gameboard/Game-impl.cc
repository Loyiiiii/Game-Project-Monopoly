module game;
import <iostream>;
import <sstream>;
import <fstream>;
import <string>;
import gameboard;
using namespace std;

Game::Game() {
    game = new GameBoard;
}

Game::~Game() {
    delete game;
}

void Game::loadGame(const string filename) {
    game->loadGame(filename);
}

void Game::start() {
    while (game->playerNumber != 1) {

        cout << game->currPlayer->getName();
        cout << ", this is your turn, what action do you want to take?" << endl;
        string cmd = "";

        if (cmd == "next") {
            game->next();
            continue;
        }

        else if (testmode && cmd == "roll") {
            string setdices = "";
            getline(cin, setdices);
            int d1, d2;

            // check does the client want to set the dices manually
            if (setdices != "") {

                istringstream iss{setdices};
                iss >> d1 >> d2;
                if (d1 > 6 || d1 < 1 || d2 > 6 || d2 < 1) {
                    cout << "please set the die's value within 1 - 6" << endl;
                    continue;
                } else {

                    // !!! move current player d1 + d2 steps
                    game->moveStep(d1 + d2, *(game->currPlayer));

                }
            } else {
                game->roll();
            }
        }

        else if (cmd == "roll") {
            game->roll();
        }

        else if (cmd == "trade") {
            int numgive, numreceive;
            string name, give, receive;
            cin >> name >> give >> receive;
            stringstream givestream(give);
            stringstream receivestream(receive);
            
            // when current player offers money
            if (givestream >> numgive) {

                // when the other player recive money 
                if (receivestream >> numreceive) {
                    cout << "You can not offer money to trade money, please re-enter your command" << endl;
                    continue;
                }

                // current player use money to buy other player's building
                else {
                    if (game->checkPlayerOwnBuilding(name, receive)) {
                        cout << name << ". would you accept the trade, please enter accept or reject." << endl;
                        string decision;
                        cin >> decision;
                        if (decision == "accept") {
                            game->trade(*(game->currPlayer), name, numgive, receive);
                        } else {
                            cout << "The trade has been rejected, please enter your command." << endl;
                            continue;
                        }
                    } else {
                        cout << name << " does not own the building, you could enter all to show the owner of the building." << endl;
                        continue;
                    }
                }

            // when current player offers building
            } else {
                if (game->checkPlayerOwnBuilding(game->currPlayer->getName(), give)){
                    if (receivestream >> numreceive) {
                        cout << name << ". would you accept the trade, please enter accept or reject." << endl;
                        string decision;
                        cin >> decision;
                        if (decision == "accept") {
                            game->trade(*(game->currPlayer), name, give, numreceive);
                        } else {
                            cout << "The trade has been rejected, please enter your command." << endl;
                            continue;
                        }
                    } else {
                        if (game->checkPlayerOwnBuilding(name, receive)) {
                            cout << name << ". would you accept the trade, please enter accept or reject." << endl;
                            string decision;
                            cin >> decision;
                            if (decision == "accept") {
                                game->trade(*(game->currPlayer), name, give, receive);
                            } else {
                                cout << "The trade has been rejected, please enter your command." << endl;
                                continue;
                            }
                        } else {
                            cout << name << " does not own this building, please enter your command." << endl;
                            continue;
                        }
                    }
                } else {
                    cout << "you do not own this building, please enter your command." << endl;
                    continue;
                }
            }
        }

        else if (cmd == "improve") {
                string property, option;
                cin >> property >> option;
                if (game->checkPlayerOwnBuilding(game->currPlayer->getName(), property)) {
                    if (game->checkMonopoly(game->getBuildingIndex(property), *(game->currPlayer))) {
                        if (option == "buy") {
                            game->improve(game->getBuildingIndex(property), *(game->currPlayer));
                        }
                        if (option == "sell") {
                            game->sellImprovement(game->getBuildingIndex(property), *(game->currPlayer));
                        }
                    } else {
                        cout << "you do not have monopoly, please enter your command." << endl;
                        continue;
                    }
                } else {
                    cout << "you do not own this building, please enter your command." << endl;
                    continue;
                }
            }

        else if (cmd == "mortgage") {
                string property;
                cin >> property;
                if (game->checkPlayerOwnBuilding(game->currPlayer->getName(), property)) {
                    game->mortgage(game->getBuildingIndex(property), *(game->currPlayer));
                } else {
                    cout << "you do not own this building, please enter your command." << endl;
                    continue;
                }
            }

        else if (cmd == "unmortgage") {
                string property;
                cin >> property;
                if (game->checkPlayerOwnBuilding(game->currPlayer->getName(), property)) {
                    game->unmortgage(game->getBuildingIndex(property), *(game->currPlayer));
                } else {
                    cout << "you do not own this building, please enter your command." << endl;
                    continue;
                }
            }

        else if (cmd == "bankrupt") {
                if (game->isBankrupt()) {
                    game->bankrupt();
                } else {
                    cout << "you still have money, do not give up, please continue!" << endl;
                    game->OwnMoney();
                }
            }

        else if (cmd == "assets") {
                showAsset();
            }

        else if (cmd == "all") {
                showAll();
            }

        else if (cmd == "save") {
                string filename;
                cin >> filename;
                saveGame(filename);
            }

        else if (cmd == "exit") {
                cout << "Thanks for playing!" << endl;
                break;
            }

        else if (cmd == "print") {
                game->printGameBoard();
            }

        else {
            cout << "Invalid command, please enter your command." << endl;
        }
    }

}


void Game::saveGame(const string filename) {
    game->saveGame(filename, game->curidx);
}

void Game::newGame() {
    game->newGame();
}

void Game::showAsset() {
    game->assets(*(game->currPlayer));
}

void Game::showAll() {
    game->all();
}

void Game::setTestMode() {
    testmode = true;
}


