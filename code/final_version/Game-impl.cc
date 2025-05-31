module game;
import <iostream>;
import <sstream>;
import <fstream>;
import <string>;
import gameboard;
using namespace std;

Game::Game() {
    board = new GameBoard;
}

Game::~Game() {
    delete board;
}

void Game::loadGame(const string filename) {
    board->loadGame(filename);
}

void Game::start() {
    while (board->playerNumber > 1) {

        cout << board->currPlayer->getName();
        cout << ", this is your turn, what action do you want to take?" << endl << endl;
        string cmd = "";
        cin >> cmd;
        if (cmd == "next") {
            board->next();
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
                    cout << "please set the die's value within 1 - 6" << endl << endl;
                    continue;
                } else {

                    // !!! move current player d1 + d2 steps
                    board->moveStep(d1 + d2, *(board->currPlayer));
                    board->action(board->currPlayer->getPosition(), d1 +d2);
                    cout << "Do you want to set the dice again?" << endl << endl;
                }
            } else {
                board->roll();
            }
        }

        else if (cmd == "roll") {
            board->roll();
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
                    cout << "You can not offer money to trade money, please re-enter your command" << endl << endl;
                    continue;
                }

                // current player use money to buy other player's building
                else {
                    if (board->checkPlayerOwnBuilding(name, receive)) {
                        cout << name << ". would you accept the trade, please enter accept or reject." << endl << endl;
                        string decision;
                        cin >> decision;
                        if (decision == "accept") {
                            board->trade(*(board->currPlayer), name, numgive, receive);
                        } else {
                            cout << "The trade has been rejected, please enter your command." << endl << endl;
                            continue;
                        }
                    } else {
                        cout << name << " does not own the building, you could enter all to show the owner of the building." << endl << endl;
                        continue;
                    }
                }

            // when current player offers building
            } else {
                if (board->checkPlayerOwnBuilding(board->currPlayer->getName(), give)){
                    if (receivestream >> numreceive) {
                        cout << name << ". would you accept the trade, please enter accept or reject." << endl << endl;
                        string decision;
                        cin >> decision;
                        if (decision == "accept") {
                            board->trade(*(board->currPlayer), name, give, numreceive);
                        } else {
                            cout << "The trade has been rejected, please enter your command." << endl << endl;
                            continue;
                        }
                    } else {
                        if (board->checkPlayerOwnBuilding(name, receive)) {
                            cout << name << ". would you accept the trade, please enter accept or reject." << endl << endl;
                            string decision;
                            cin >> decision;
                            if (decision == "accept") {
                                board->trade(*(board->currPlayer), name, give, receive);
                            } else {
                                cout << "The trade has been rejected, please enter your command." << endl << endl;
                                continue;
                            }
                        } else {
                            cout << name << " does not own this building, please enter your command." << endl << endl;
                            continue;
                        }
                    }
                } else {
                    cout << "you do not own this building, please enter your command." << endl << endl;
                    continue;
                }
            }
        }

        else if (cmd == "improve") {
                string property, option;
                cin >> property >> option;
                if (board->checkPlayerOwnBuilding(board->currPlayer->getName(), property)) {
                    if (board->checkMonopoly(board->getBuildingIndex(property), *(board->currPlayer))) {
                        if (option == "buy") {
                            board->improve(board->getBuildingIndex(property), *(board->currPlayer));
                        }
                        if (option == "sell") {
                            board->sellImprovement(board->getBuildingIndex(property), *(board->currPlayer));
                        }
                    } else {
                        cout << "you do not have monopoly, please enter your command." << endl << endl;
                        continue;
                    }
                } else {
                    cout << "you do not own this building, please enter your command." << endl << endl;
                    continue;
                }
            }

        else if (cmd == "mortgage") {
                string property;
                cin >> property;
                if (board->checkPlayerOwnBuilding(board->currPlayer->getName(), property)) {
                    board->mortgage(board->getBuildingIndex(property), *(board->currPlayer));
                } else {
                    cout << "you do not own this building, please enter your command." << endl << endl;
                    continue;
                }
            }

        else if (cmd == "unmortgage") {
                string property;
                cin >> property;
                if (board->checkPlayerOwnBuilding(board->currPlayer->getName(), property)) {
                    board->unmortgage(board->getBuildingIndex(property), *(board->currPlayer));
                } else {
                    cout << "you do not own this building, please enter your command." << endl << endl;
                    continue;
                }
            }

        else if (cmd == "bankrupt") {
                if (board->isBankrupt()) {
                    board->bankrupt();
                } else {
                    cout << "you still have money, do not give up, please continue!" << endl << endl;
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
                cout << "The game is saved." << endl << endl;
                return;
            }

        else if (cmd == "exit") {
                cout << "Thanks for playing!" << endl << endl;
                return;
            }

        else if (cmd == "print") {
                board->printGameBoard();
            }

        else {
            cout << "Invalid command, please enter your command." << endl << endl;
        }
    }
    
    cout << "The game is finished. " << board->players[0].getName() << " is the winner!" << endl << endl;

}


void Game::saveGame(const string filename) {
    board->saveGame(filename, board->curidx);
}

void Game::newGame() {
    board->newGame();
}

void Game::showAsset() {
    board->assets(*(board->currPlayer));
}

void Game::showAll() {
    board->all();
}

void Game::setTestMode() {
    testmode = true;
}


