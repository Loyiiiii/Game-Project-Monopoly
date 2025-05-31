module gameboard;
import <iostream>;
import <vector>;
import <cstddef>;
import <algorithm>;
import <sstream>;
import <fstream>;  // 
import <string>;
import <cstdlib>;  //
import <ctime>;    //
import player;
import square;
import propertyinfo;
import property;
import non_property;
import academic;
import gyms;
import residence;
import osap;
import goose_nesting;
import tuition;
import coop_fee;
import slc;
import nh;
import gototims;
import dctimsline;
using namespace std;

const int MONOPOLY_BLOCK_TYPE = 8;

GameBoard::GameBoard() {
    buildings.emplace_back(new OSAP(0));
    buildings.emplace_back(new Academic(1));
    buildings.emplace_back(new SLC(2));
    buildings.emplace_back(new Academic(3));
    buildings.emplace_back(new Tuition(4, 0));
    buildings.emplace_back(new Residence(5));
    buildings.emplace_back(new Academic(6));
    buildings.emplace_back(new NH(7));
    buildings.emplace_back(new Academic(8));
    buildings.emplace_back(new Academic(9));
    buildings.emplace_back(new DCTimsLine(10));
    buildings.emplace_back(new Academic(11));
    buildings.emplace_back(new Gyms(12));
    buildings.emplace_back(new Academic(13));
    buildings.emplace_back(new Academic(14));
    buildings.emplace_back(new Residence(15));
    buildings.emplace_back(new Academic(16));
    buildings.emplace_back(new SLC(17));
    buildings.emplace_back(new Academic(18));
    buildings.emplace_back(new Academic(19));
    buildings.emplace_back(new GooseNesting(20));
    buildings.emplace_back(new Academic(21));
    buildings.emplace_back(new NH(22));
    buildings.emplace_back(new Academic(23));
    buildings.emplace_back(new Academic(24));
    buildings.emplace_back(new Residence(25));
    buildings.emplace_back(new Academic(26));
    buildings.emplace_back(new Academic(27));
    buildings.emplace_back(new Gyms(28));
    buildings.emplace_back(new Academic(29));
    buildings.emplace_back(new GoToTims(30));
    buildings.emplace_back(new Academic(31));
    buildings.emplace_back(new Academic(32));
    buildings.emplace_back(new SLC(33));
    buildings.emplace_back(new Academic(34));
    buildings.emplace_back(new Residence(35));
    buildings.emplace_back(new NH(36));
    buildings.emplace_back(new Academic(37));
    buildings.emplace_back(new COOP_Fee(38));
    buildings.emplace_back(new Academic(39));
}

GameBoard::~GameBoard() {
    for (int i = 0; i < 40; i++) { delete buildings[i]; }
}

bool GameBoard::checkPlayer(const string name, const char token) const {
    for (auto& currentPlayer : players) {
        if (currentPlayer.getName() == name || 
            currentPlayer.getToken() == token) {
            return true;
        }
    }
    return false;
}


void GameBoard::addPlayer(int numPlayers) {
    string playerName;
    char token;
    int idx = 0;
    while (numPlayers > 0) {
        cout << "Please enter your player information: (player name, token)" << endl << endl;
        cin >> playerName >> token;
        if (!(token == 'G' || token == 'B' || token == 'D' ||
              token == 'P' || token == 'S' || token == '$' || 
              token == 'L' || token == 'T')) {
                cout << "Please choose a token from G B D P S $ L T, please re-enter." << endl << endl;
                continue;
        } else if (!players.empty() && checkPlayer(playerName, token)) {
            cout << "The player is already exist, please entre another player" << endl << endl;
            continue;
        } else {
            players.emplace_back(playerName, token);
            buildings[0]->add_player_to_square(token, idx);
            numPlayers -= 1;
            idx += 1;
        }
    }
}

int GameBoard::countPlayer() { return playerNumber; }

string GameBoard::getBuildingName(size_t index) {
    for (auto* currSquare : buildings) {
        if (currSquare->getBuildingIndex() == index) {
            return currSquare->getBuildingName();
        }
    }
    return "Not Found";
}

size_t GameBoard::getBuildingIndex(string buildingName) {
    for (auto* currBuilding : buildings) {
        if (currBuilding->getBuildingName() == buildingName) {
            return currBuilding->getBuildingIndex();
        }
    }
    return -1;
}

int GameBoard::getMonopolyValue(size_t index) {
    for (int i = 0; i < MONOPOLY_BLOCK_TYPE; i++) {
        for (auto currIndex : monopolyTable[i]) {
            if (index == currIndex) { return i; }
        }
    }
    return -1;
}

bool GameBoard::checkMonopoly(size_t target, const Player& pl) {
    vector<PropertyInfo> tempProp = pl.getProperty();
    int targetMonoVal = getMonopolyValue(target);
    vector<size_t> currentMonoBuildingHave;
    for (auto currBuilding : tempProp) {
        if (currBuilding.monopolyValue == targetMonoVal) {
            currentMonoBuildingHave.emplace_back(currBuilding.buildingIndex);
        }
    }

    vector<size_t> fixedMonoList = monopolyTable[targetMonoVal];

    sort(currentMonoBuildingHave.begin(), currentMonoBuildingHave.end());

   if (fixedMonoList != currentMonoBuildingHave) { return false; }
    return true;
}

bool GameBoard::checkPlayer(string name) {
    for (auto currPlayer : players) {
        if (currPlayer.getName() == name) { return true; }
    }
    return false;
}

bool GameBoard::checkPlayerOwnBuilding(string playerName, string buildingName) {
    for (auto currPlayer : players) {
        if (currPlayer.getName() == playerName) {
            if (currPlayer.checkProperty(getBuildingIndex(buildingName))) {
                return true;
            }
        }
    }
    return false;
}

bool GameBoard::checkSquareType(size_t position) {
    if (position == 1 || position == 3 || position == 5 || position == 6 || 
        position == 8 || position == 9 || position == 11 || position == 13 || 
        position == 14 || position == 16 || position == 18 || position == 19 || 
        position == 21 || position == 23 || position == 24 || position == 26 || 
        position == 27 || position == 29 || position == 31 || position == 32 || 
        position == 34 || position == 37 || position == 39 || position == 12 ||
        position == 15 || position == 25 || position == 35 || position == 28) {
            return true;
        }
        return false;
}

bool GameBoard::isResidence(size_t position) {
    if (position == 5 || position == 15 || position == 25 || position == 35) {
        return true;
    }
    return false;
}

bool GameBoard::isGym(size_t position) {
    if (position == 12 || position == 28) {
        return true;
    }
    return false;
}

// Game Command
void GameBoard::moveStep(int step, Player& pl) { pl.addPosition(step); }

void GameBoard::trade(Player& pl, string playerName, string buildingName, int money) {
    bool exist = false;
    for (auto& currPlayer : players) {
        if (currPlayer.getName() == playerName) {
            exist = true;
        }
    }

    if (exist) {
        for (auto& currPlayer : players) {
            if (currPlayer.getName() == playerName) {
                if (currPlayer.getMoney() < money) {
                    cout << "Trade Failed. " << playerName << 
                         " donesn't have enough money." << endl << endl;
                    return;
                }
            }
        }
    
        size_t tempIndex = getBuildingIndex(buildingName);
        Square* buildingPtr = buildings[tempIndex];
    
        // pl give the building, pl get the money. 
        pl.deleteProperty(tempIndex);
        pl.addMoney(money);
    
        // playerName pay the money, playerName get the buidingName
        for (auto& currPlayer : players) {
            if (currPlayer.getName() == playerName) {
                currPlayer.addMoney(-money);
                currPlayer.buyProperty(tempIndex);
                currPlayer.changeMonopolyValue(tempIndex, getMonopolyValue(tempIndex));
            }
        }
    
        buildingPtr->setOwner(playerName);
    
        cout << "Trade Successful! " << endl; 
        cout << pl.getName() << " give the " << buildingName << " to " 
             << playerName << " then reveive $" << money  << "." << endl;
        cout << playerName << " receive the " << buildingName << " from " << pl.getName()
             << " and pay $" << money << "." << endl << endl;
    } else {
        cout << "The player you want to trade does not exist, please re-enter the command." << endl << endl;
    }
    
}

void GameBoard::trade(Player& pl, string playerName, int money, string buildingName) {
    bool exist = false;
    for (auto& currPlayer : players) {
        if (currPlayer.getName() == playerName) {
            exist = true;
        }
    }

    if (exist) {
        if (pl.getMoney() < money) {
            cout << "Trade Failed. " << pl.getName() << " donesn't have enough money." 
                 << endl << endl;
            return;
        }
    
        size_t tempIndex = getBuildingIndex(buildingName);
        Square* buildingPtr = buildings[tempIndex];
    
        // playerName receive the money, playerName give the buidingName.
        for (auto& currPlayer : players) {
            if (currPlayer.getName() == playerName) {
                currPlayer.addMoney(money);
                currPlayer.deleteProperty(tempIndex);
            }
        }
    
        // pl give the money, pl get the building. 
        pl.addMoney(-money);
        pl.buyProperty(tempIndex);
        pl.changeMonopolyValue(tempIndex, getMonopolyValue(tempIndex));
    
        buildingPtr->setOwner(pl.getName());
    
        cout << "Trade Successful! " << endl; 
        cout << pl.getName() << " give $" << money << " to " 
             << playerName << " then reveive the " << buildingName << "." << endl;
        cout << playerName << " receive $" << money << " and give the " << buildingName << 
             " to " << pl.getName() << "." << endl << endl;
    } else {
        cout << "The player you want to trade does not exist, please re-enter the command." << endl << endl;
    }
    
}

void GameBoard::trade(Player& pl, string playerName, string building1, string building2) {
    bool exist = false;
    for (auto& currPlayer : players) {
        if (currPlayer.getName() == playerName) {
            exist = true;
        }
    }

    if (exist) {
        size_t tempB1Index = getBuildingIndex(building1);
        size_t tempB2Index = getBuildingIndex(building2);
        Square* buildingPtr1 = buildings[tempB1Index];
        Square* buildingPtr2 = buildings[tempB2Index];

        // playerName receive the building1, playerName give the buiding2.
        pl.deleteProperty(tempB1Index);
        for (auto& currPlayer : players) {
            if (currPlayer.getName() == playerName) {
                currPlayer.deleteProperty(tempB2Index);
            }
        }

        // pl give the building1, pl get the building2. 
        pl.buyProperty(tempB2Index);
        pl.changeMonopolyValue(tempB2Index, getMonopolyValue(tempB2Index));
        for (auto& currPlayer : players) {
            if (currPlayer.getName() == playerName) {
                currPlayer.buyProperty(tempB1Index);
                currPlayer.changeMonopolyValue(tempB1Index, getMonopolyValue(tempB1Index));
            }
        }

        buildingPtr1->setOwner(playerName);
        buildingPtr2->setOwner(pl.getName());

        cout << "Trade Successful! " << endl; 
        cout << pl.getName() << " trades " << building1 << " to " << playerName << "." << endl; 
        cout << playerName << " trades " << building2 << " to " << pl.getName() << "." << endl << endl;
    } else {
        cout << "The player you want to trade does not exist, please re-enter the command." << endl << endl;
    }
}

void GameBoard::buyBuilding(size_t index, Player& pl) {
    Square* buildingPtr = buildings[index];
    string playerName = pl.getName();
    int needToPay = buildingPtr->getPurchaseCost(index);
    if (!checkSquareType(index)) {
        cout << "Sorry this building is non-property, you cannot buy it." << endl << endl;
        return;
    } 
    if (pl.getMoney() < needToPay) {
        cout << "Sorry you don't have enough money to buy this building." << endl << endl;
        return; 
    }
    if (buildingPtr->getOwner() == playerName) {
        cout << "You have been bought this building, you cannot buy again." << endl << endl;
        return;
    }
    if (buildingPtr->isOwned()) {
        cout << "Sorry this building has an owner called " << buildingPtr->getOwner() <<
             ", you cannot buy it." << endl << endl;
        return;
    }
    pl.buyProperty(index);
    pl.changeMonopolyValue(index, getMonopolyValue(index));
    buildingPtr->setOwner(playerName);
    pl.addMoney(-needToPay);
    cout << playerName << " bought a property called " << getBuildingName(index) << endl << endl;
}

void GameBoard::improve(size_t index, Player& pl) {
    Square* buildingPtr = buildings[index];
    int needToPay = buildingPtr->getImprovementCost(index);
    if (checkMonopoly(index, pl)) {
        if (pl.getMoney() < needToPay) {
            cout << "Sorry you don't have enough money to improve the building." << endl << endl;
        } else {
            pl.improveProperty(index);
            pl.addMoney(-needToPay);
            buildingPtr->LevelImprove();
            cout << "Improve Successful! " << getBuildingName(index) << " improved into level " 
                 << pl.getImproveLevel(index) << endl << endl;
        }
    } else if (!checkPlayerOwnBuilding(pl.getName(), getBuildingName(index))) {
        cout << "Sorry you don't have this building, you cannot imporve it." << endl;
    } else if (pl.getImproveLevel(index) == -1) {
        cout << "This building has been mortgaged, you cannot imporve it." << endl;
    } else {
        cout << "You don't have all of the monopoly block same as this building." << endl;
    }
}

void GameBoard::sellImprovement(size_t index, Player& pl) {
    Square* buildingPtr = buildings[index];
    string buildingName = getBuildingName(index);
    string playerName = pl.getName();

    if (buildingPtr->getOwner() != playerName) {
        cout << "You don't have this building, you cannot sell the improvements of this building." 
             << endl << endl;
        return;
    }
    int currentImproveLevel = pl.getImproveLevel(index);
    if (currentImproveLevel <= 0) {
        cout << "You don't have any improvement at this building, you cannot sell it." << endl << endl;
        return;
    }

    buildingPtr->LevelDegrade();
    pl.setImproveLevel(index, currentImproveLevel - 1);
    pl.addMoney(buildingPtr->getImprovementCost(index) / 2);
    cout << "Selling Successful! " << buildingName << " improvement level into " << 
            currentImproveLevel - 1 << endl << endl;
}

void GameBoard::mortgage(size_t index, Player& pl) {
    Square* buildingPtr = buildings[index];
    string playerName = pl.getName();
    string buildingName = getBuildingName(index);

    if (!checkPlayerOwnBuilding(playerName, buildingName)) {
        cout << "Sorry you don't have this building, you cannot mortgage it." << endl << endl;
        return;
    }
    // 查看此建筑是否已经是mortgage的状态

    if (pl.getImproveLevel(index) > 0) {
        cout << "Sorry you cannot mortgage the building have been improved." << endl << endl;
        return;
    } else if (pl.getImproveLevel(index) == -1 && buildingPtr->isMortgaged()) {
        cout << "Sorry " << buildingName << " has been mortgaged, you cannot again." << endl << endl;
        return;
    } else {
        pl.mortgageProperty(index);
        pl.addMoney(buildingPtr->getPurchaseCost(index) / 2);
        buildingPtr->mortgage();
        cout << "Mortgage " << buildingName << " Successful!" << endl << endl;
    }
}

void GameBoard::unmortgage(size_t index, Player& pl) {
    Square* buildingPtr = buildings[index];
    string playerName = pl.getName();
    string buildingName = getBuildingName(index);

    int needToPay = buildingPtr->getPurchaseCost(index) * 0.6;

    if (!checkPlayerOwnBuilding(playerName, buildingName)) {
        cout << "Sorry you don't have this building, you cannot unmortgage it." << endl << endl;
        return;
    }

    if (pl.getImproveLevel(index) != -1) {
        cout << "Sorry you cannot unmortgage the building that in unmortgaged state." << endl << endl;
    } else {
        if (pl.getMoney() < needToPay) {
            cout << "Sorry you don't have enough money to unmortgage this building." << endl << endl;
        } else {
            pl.addMoney(-needToPay);
            buildingPtr->unmortgage();
            pl.unMortgageProperty(index);
            cout << "Unmortgage " << buildingName << " Successful!" << endl << endl;
        }
    }
}

void GameBoard::assets(const Player& pl) {
    cout << "Player: " << pl.getName() << endl;
    cout << "Token: " << pl.getToken() << endl;
    cout << "Position: " << pl.getPosition() << endl;
    cout << "Money: $" << pl.getMoney() << endl;
    vector<PropertyInfo> temp = pl.getProperty();
    if (temp.empty()) {
        cout << "This player doesn't have any property." << endl << endl;
    } else {
        cout << "Property: " << endl;
        for (auto pr : temp) {
            cout << getBuildingName(pr.buildingIndex) << "(improve level: " 
                << pr.improveLevel << ")  ";
        }
        cout << endl << endl;
    }
}

void GameBoard::all() {
    for (auto pl : players) { assets(pl); }
}

vector<size_t> GameBoard::deletePlayer(Player& pl) {
    vector<size_t> buildingList;
    vector<PropertyInfo> tempProp = pl.getProperty();
    string playerName = pl.getName();
    for (auto currProp : tempProp) {
        buildingList.emplace_back(currProp.buildingIndex);
    }
    for (auto currIndex : buildingList) {
        buildings[currIndex]->setOwner("");
        //buildings[currIndex]->getOwner();
        cout << buildings[currIndex]->isOwned() << endl;
        pl.deleteProperty(currIndex);
    }
    for (auto it = players.begin(); it != players.end(); ) {
        if (it->getName() == playerName) {
            //cout << it->getName() << ' ' << playerName <<endl;
            it = players.erase(it);
        } else {
            ++it;
        }
    }
    cout << "delete successful" << endl << endl;
    return buildingList;
}

int GameBoard::assetEva() {
    int total = currPlayer->getMoney();
    vector<PropertyInfo> tempProp = currPlayer->getProperty();
    for (auto currProp : tempProp) {
        size_t currBuildingIndex = currProp.buildingIndex;
        Square* buildingPtr = buildings[currBuildingIndex];
        int improveNumber = currProp.improveLevel;
        int improveAsset = improveNumber * 
                           (buildingPtr->getImprovementCost(currBuildingIndex) / 2); 
        int currBuildingAsset = buildingPtr->getPurchaseCost(currBuildingIndex) / 2;
        total += (improveAsset + currBuildingAsset);
    }
    return total;
}

void GameBoard::auction(size_t index) {
    Square* AuctionProperty = buildings[index];

    cout << "This property (" << AuctionProperty->getBuildingName() << ") is up for auction!\n";
    cout << "Starting bid: $0" << endl;

    int playerNum = playerNumber;
    vector<int> biddingOrder;
    for (int i = 0; i < playerNum; ++i) {
        biddingOrder.push_back(i);
    }
    int highestBid = 0;
    int highestBidderIndex = -1;
    size_t current = 0;

    while (biddingOrder.size() > 1 || current != 0) {
        int playerIndex = biddingOrder[current];
        Player p = players[playerIndex];

        cout << "Player " << p.getName() << "'s turn. Highest bid: $" << highestBid << "\n";
        cout << "Enter your bid (or 'pass'): ";
        string input;
        cin >> input;

        if (input == "pass") {
            cout << p.getName() << " passed.\n";
            biddingOrder.erase(biddingOrder.begin() + current);
            if (current >= biddingOrder.size()) {
                current = 0;
            } 
        } else {
            stringstream ss(input);
            int bid;
            if (ss >> bid && ss.eof()) {
                if (p.getMoney() < bid) {
                    cout << "You don't have enough money for the auction. \n";
                    cout << p.getName() << " passed.\n";
                    biddingOrder.erase(biddingOrder.begin() + current);
                    if (current >= biddingOrder.size()) {
                        current = 0;
                    }
                    continue;
                }
                if (bid > highestBid) {
                    highestBid = bid;
                    highestBidderIndex = playerIndex;
                    cout << p.getName() << " bids $" << bid << endl;
                    current = (current + 1) % biddingOrder.size();
                } else {
                    cout << "Bid must be higher than $" << highestBid << endl;
                }
            } else {
                cout << "Invalid input. Please enter a number or 'pass'.\n";
            }
        }
    }

    if (biddingOrder.size() == 1) {
        highestBidderIndex = biddingOrder[0];
    } 
    if (highestBidderIndex != -1) {
        Player winner = players[highestBidderIndex];
        cout << winner.getName() << " wins the auction for $" << highestBid << "!\n";
        winner.addMoney(-highestBid);
        AuctionProperty->setOwner(winner.getName());
    } else {
        cout << "No one won the auction.\n";
    }
}

void GameBoard::printPlayers() {
    for (auto& currentPlayer : players) {
        cout << currentPlayer << endl;
    }
}

void GameBoard::printBuildings() {
    for (auto* currentBuilding : buildings) {
        cout << *currentBuilding;
    }
    cout << endl;
}


void GameBoard::printGameBoard() {

// print the first line
    for (int i = 0; i < 89; i++) {
        cout << "_";
    }
    cout << endl;

// first row
    for (int i = 1; i < 6; i++) {
        for (int j = 20; j < 31; j++) {
            cout << "|";
            string name = buildings[j]->getBuildingName();

            // first line
            if (i == 1) {

                // special cases
                if (name == "GooseNesting") {
                    cout << "Goose  ";
                }
                else if (name == "NH") {
                    cout << "NEEDLES";
                }
                else if (name == "V1") {
                    cout << "V1     ";
                }
                else if (name == "CIF") {
                    cout << "CIF    ";
                }
                else if (name == "GoToTims") {
                    cout << "GO TO  ";
                }

                // Academic Buildings
                else {
                    const int imp = buildings[j]->getCurrentLevel();
                    if (imp < 0) {
                        cout << "MTGE   ";
                    }
                    else {
                        for (int k = 0; k < imp; k++) {
                            cout << "I";
                        }
                        for (int v = 0; v < 7 - imp; v++) {
                            cout << " ";
                        }
                    }
                }
            }

            // second line
            if (i == 2) {

                // special cases
                if (name == "GooseNesting") {
                    cout << "Nesting";
                }
                else if (name == "NH") {
                    cout << "HALL   ";
                }
                else if (name == "V1" || name == "CIF") {
                    cout << "       ";
                }
                else if (name == "GoToTims") {
                    cout << "TIMS   ";
                }

                // Academic Buildings
                else {
                    cout << "-------";
                }
            }

            // third line
            if (i == 3) {
                bool printspace = name == "GooseNesting" || 
                                    name == "NH"  ||
                                    name == "V1"            ||
                                    name == "CIF"           ||
                                    name == "GoToTims";
                // special cases
                if (printspace) {
                    cout << "       ";
                }
                // Academic Buildings
                else {
                    cout << name;
                    size_t space = 7 - name.size();
                    for (size_t v = 0; v < space; v++) {
                        cout << " ";
                    }
                }
            }

            // fourth line
            if (i == 4) {
                // print the players who are on the square
                buildings[j]->get_square();
            }

            // fifth line
            if (i == 5) {
                cout << "_______";
            }
        }
        cout << "|" << endl;
    }

// second row

    // first line
    int row2imp1 = buildings[19]->getCurrentLevel();
    int row2imp1space = 7 - row2imp1;
    int row2imp2 = buildings[31]->getCurrentLevel();
    int row2imp2space = 7 - row2imp2;
    cout << "|";
    for (int i = 0; i < row2imp1; i++) {
        cout << "I";
    }
    for (int i = 0; i < row2imp1space; i++) {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < row2imp2; i++) {
        cout << "I";
    }
    for (int i = 0; i < row2imp2space; i++) {
        cout << " ";
    }
    cout << "|" << endl;

    // second line
    cout << "|-------|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|-------|" << endl;

    // third line
    cout << "|OPT    |";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|EIT    |" << endl;

    // fourth line
    cout << "|";
    buildings[19]->get_square();
    cout << "|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|";
    buildings[31]->get_square();
    cout << "|" << endl;

    // fifth line
    cout << "|_______|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|_______|" << endl;

// third row

    // first line
    int row3imp1 = buildings[18]->getCurrentLevel();
    int row3imp1space = 7 - row3imp1;
    int row3imp2 = buildings[32]->getCurrentLevel();
    int row3imp2space = 7 - row3imp2;
    cout << "|";
    for (int i = 0; i < row3imp1; i++) {
        cout << "I";
    }
    for (int i = 0; i < row3imp1space; i++) {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < row3imp2; i++) {
        cout << "I";
    }
    for (int i = 0; i < row3imp2space; i++) {
        cout << " ";
    }
    cout << "|" << endl;

    // second line
    cout << "|-------|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|-------|" << endl;

    // third line
    cout << "|BMH    |";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|ESC    |" << endl;

    // fourth line
    cout << "|";
    buildings[18]->get_square();
    cout << "|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|";
    buildings[32]->get_square();
    cout << "|" << endl;

    // fifth line
    cout << "|_______|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|_______|" << endl;

// fourth row

    // first line
    cout << "|SLC    |";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|SLC    |" << endl;

    // second line
    cout << "|       |";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|       |" << endl;

    // third line
    cout << "|       |";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|       |" << endl;

    // fourth line
    cout << "|";
    buildings[17]->get_square();
    cout << "|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|";
    buildings[33]->get_square();
    cout << "|" << endl;

    // fifth line
    cout << "|_______|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|_______|" << endl;

// fifth row

    // first line
    int row5imp1 = buildings[16]->getCurrentLevel();
    int row5imp1space = 7 - row5imp1;
    int row5imp2 = buildings[34]->getCurrentLevel();
    int row5imp2space = 7 - row5imp2;
    cout << "|";
    for (int i = 0; i < row5imp1; i++) {
        cout << "I";
    }
    for (int i = 0; i < row5imp1space; i++) {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < row5imp2; i++) {
        cout << "I";
    }
    for (int i = 0; i < row5imp2space; i++) {
        cout << " ";
    }
    cout << "|" << endl;

    // second line
    cout << "|-------|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|-------|" << endl;

    // third line
    cout << "|LHI    |";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|C2     |" << endl;

    // fourth line
    cout << "|";
    buildings[16]->get_square();
    cout << "|";
    for (int i = 0; i < 13; i++) {
        cout << " ";
    }
    for (int i = 0; i < 45; i++) {
        cout << "_";
    }
    for (int i = 0; i < 13; i++) {
        cout << " ";
    }
    cout << "|";
    buildings[34]->get_square();
    cout << "|" << endl;

    // fifth line
    cout << "|_______|";
    for (int i = 0; i < 12; i++) {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < 45; i++) {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < 12; i++) {
        cout << " ";
    }
    cout << "|_______|" << endl;

// sixth row

    // first line
    cout << "|UWP    |";
    for (int i = 0; i < 12; i++) {
        cout << " ";
    }
    cout << "| #   #  ##  #####  ###  ###   ###  #   #   # |";
    for (int i = 0; i < 12; i++) {
        cout << " ";
    }
    cout << "|REV    |" << endl;

    // second line
    cout << "|       |";
    for (int i = 0; i < 12; i++) {
        cout << " ";
    }
    cout << "| #   # #  #   #   #   # #  # #   # #   #   # |";
    for (int i = 0; i < 12; i++) {
        cout << " ";
    }
    cout << "|       |" << endl;

    // third line
    cout << "|       |";
    for (int i = 0; i < 12; i++) {
        cout << " ";
    }
    cout << "| # # # ####   #   #   # ###  #   # #    # #  |";
    for (int i = 0; i < 12; i++) {
        cout << " ";
    }
    cout << "|       |" << endl;

    // fourth line
    cout << "|";
    buildings[17]->get_square();
    cout << "|";
    for (int i = 0; i < 12; i++) {
        cout << " ";
    }
    cout << "| # # # #  #   #   #   # #    #   # #     #   |";
    for (int i = 0; i < 12; i++) {
        cout << " ";
    }
    cout << "|";
    buildings[33]->get_square();
    cout << "|" << endl;

    // fifth line
    cout << "|_______|";
    for (int i = 0; i < 12; i++) {
        cout << " ";
    }
    cout << "| ##### #  #   #    ###  #     ###  ## #  #   |";
    for (int i = 0; i < 12; i++) {
        cout << " ";
    }
    cout << "|_______|" << endl;

// seventh row

    // first line
    int row7imp1 = buildings[14]->getCurrentLevel();
    int row7imp1space = 7 - row7imp1;
    cout << "|";
    for (int i = 0; i < row7imp1; i++) {
        cout << "I";
    }
    for (int i = 0; i < row7imp1space; i++) {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < 12; i++) {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < 45; i++) {
        cout << "_";
    }
    cout << "|";
    for (int i = 0; i < 12; i++) {
        cout << " ";
    }
    cout << "|NEEDLES|" << endl;

    // second line
    cout << "|-------|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|HALL   |" << endl;

    // third line
    cout << "|CPH    |";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|       |" << endl;

    // fourth line
    cout << "|";
    buildings[14]->get_square();
    cout << "|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|";
    buildings[36]->get_square();
    cout << "|" << endl;

    // fifth line
    cout << "|_______|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|_______|" << endl;

// eighth row

    // first line
    int row8imp1 = buildings[13]->getCurrentLevel();
    int row8imp1space = 7 - row8imp1;
    int row8imp2 = buildings[37]->getCurrentLevel();
    int row8imp2space = 7 - row8imp2;
    cout << "|";
    for (int i = 0; i < row8imp1; i++) {
        cout << "I";
    }
    for (int i = 0; i < row8imp1space; i++) {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < row8imp2; i++) {
        cout << "I";
    }
    for (int i = 0; i < row8imp2space; i++) {
        cout << " ";
    }
    cout << "|" << endl;

    // second line
    cout << "|-------|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|-------|" << endl;

    // third line
    cout << "|DWE    |";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|MC     |" << endl;

    // fourth line
    cout << "|";
    buildings[13]->get_square();
    cout << "|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|";
    buildings[37]->get_square();
    cout << "|" << endl;

    // fifth line
    cout << "|_______|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|_______|" << endl;

// ninth row

    // first line
    cout << "|PAC    |";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|COOP   |" << endl;

    // second line
    cout << "|       |";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|FEE    |" << endl;

    // third line
    cout << "|       |";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|       |" << endl;

    // fourth line
    cout << "|";
    buildings[12]->get_square();
    cout << "|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|";
    buildings[38]->get_square();
    cout << "|" << endl;

    // fifth line
    cout << "|_______|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|_______|" << endl;

// tenth row

    // first line
    int row10imp1 = buildings[11]->getCurrentLevel();
    int row10imp1space = 7 - row10imp1;
    int row10imp2 = buildings[39]->getCurrentLevel();
    int row10imp2space = 7 - row10imp2;
    cout << "|";
    for (int i = 0; i < row10imp1; i++) {
        cout << "I";
    }
    for (int i = 0; i < row10imp1space; i++) {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < row10imp2; i++) {
        cout << "I";
    }
    for (int i = 0; i < row10imp2space; i++) {
        cout << " ";
    }
    cout << "|" << endl;

    // second line
    cout << "|-------|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|-------|" << endl;

    // third line
    cout << "|RCH    |";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|DC     |" << endl;

    // fourth line
    cout << "|";
    buildings[11]->get_square();
    cout << "|";
    for (int i = 0; i < 71; i++) {
        cout << " ";
    }
    cout << "|";
    buildings[39]->get_square();
    cout << "|" << endl;

    // fifth line
    cout << "|_______|";
    for (int i = 0; i < 71; i++) {
        cout << "_";
    }
    cout << "|_______|" << endl;

// eleventh row
    for (int i = 1; i < 6; i++) {
        for (int j = 10; j >= 0; j--) {
            cout << "|";
            string name = buildings[j]->getBuildingName();

            // first line
            if (i == 1) {

                // special cases
                if (name == "DCTimsLine") {
                    cout << "DC Tims";
                }
                else if (name == "NH") {
                    cout << "NEEDLES";
                }
                else if (name == "MKV") {
                    cout << "MKV    ";
                }
                else if (name == "Tuition") {
                    cout << "TUITION";
                }
                else if (name == "SLC") {
                    cout << "SLC    ";
                }
                else if (name == "COLLECT OSAP") {
                    cout << "COLLECT";
                }

                // Academic Buildings
                else {
                    const int imp = buildings[j]->getCurrentLevel();
                    if (imp < 0) {
                        cout << "MTGE   ";
                    }
                    else {
                        for (int k = 0; k < imp; k++) {
                            cout << "I";
                        }
                        for (int k = 0; k < 7 - imp; k++) {
                            cout << " ";
                        }
                    }
                }
            }

            // second line
            if (i == 2) {

                // special cases
                if (name == "DCTimsLine") {
                    cout << "Line   ";
                }
                else if (name == "NH") {
                    cout << "HALL   ";
                }
                else if (name == "MKV" || name == "SLC" || name == "Tuition") {
                    cout << "       ";
                }
                else if (name == "COLLECT OSAP") {
                    cout << "OSAP   ";
                }

                // Academic Buildings
                else {
                    cout << "-------";
                }
            }

            // third line
            if (i == 3) {
                bool printspace = name == "DCTimsLine"  || 
                                    name == "NH"  ||
                                    name == "MKV"           ||
                                    name == "SLC"           ||
                                    name == "Tuition"       ||
                                    name == "COLLECT OSAP";
                // special cases
                if (printspace) {
                    cout << "       ";
                }
                // Academic Buildings
                else {
                    cout << name;
                    size_t space = 7 - name.size();
                    for (size_t v = 0; v < space; v++) {
                        cout << " ";
                    }
                }
            }

            // fourth line
            if (i == 4) {
                // print the players who are on the square
                buildings[j]->get_square();
            }

            // fifth line
            if (i == 5) {
                cout << "_______";
            }
        }
        cout << "|" << endl;
    }
}

bool GameBoard::rolldice() {
    srand(time(0));
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    cout << "You have rolled " << die1 << " and " << die2 << endl << endl;
    if (die1 == die2) {
        return true;
    }
    return false;

}

void GameBoard::next() {
    if (rolled == false) {
        cout << "You have not rolled yet, please roll!" << endl << endl;
        return;
    }
    numroll = 0;
    rolled = false;
    if (curidx == playerNumber - 1) {
        curidx = 0;
        
    } else {
        curidx += 1;
    }

    currPlayer = &players[curidx];

}

int GameBoard::move(size_t oldpos, size_t newpos) {
    buildings[oldpos]->remove_player_to_square(curidx);
    
    if (newpos > 40) {
        newpos = newpos % 40;
        currPlayer->addMoney(200);
        cout << "You have passed OSAP, you get $200." << endl << endl;
    } 
    if (newpos < 0) {
        newpos = newpos + 40;
    }
    buildings[newpos]->add_player_to_square(currPlayer->getToken(), curidx);
    currPlayer->setPosition(newpos);
    return newpos;
}

bool GameBoard::isBankrupt() {
    if (assetEva() < ownMoney) {
        return true;
    } else {
        return false;
    }
}

void GameBoard::OwnMoney() {
    while (currPlayer->getMoney() < ownMoney) {
        cout << "Please choose trade or mortgage to raise money." << endl << endl;
        string cmd;
        cin >> cmd;
        if (cmd == "trade") {
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
                    if (checkPlayerOwnBuilding(name, receive)) {
                        cout << name << ". would you accept the trade, please enter accept or reject." << endl << endl;
                        string decision;
                        cin >> decision;
                        if (decision == "accept") {
                            trade(*currPlayer, name, numgive, receive);
                        } else {
                            cout << "The trade has been rejected, please enter your command." << endl << endl;
                            continue;
                        }
                    } else {
                        cout << name << " does not own the building, you could enter all to show the owner of the building." << endl << endl;
                        continue;
                    }
                }
            }
            // when current player offers building
            else {
                if (checkPlayerOwnBuilding(currPlayer->getName(), give)){
                    if (receivestream >> numreceive) {
                        cout << name << ". would you accept the trade, please enter accept or reject." << endl << endl;
                        string decision;
                        cin >> decision;
                        if (decision == "accept") {
                            trade(*currPlayer, name, give, numreceive);
                        } else {
                            cout << "The trade has been rejected, please enter your command." << endl << endl;
                            continue;
                        }
                    } else {
                        if (checkPlayerOwnBuilding(name, receive)) {
                            cout << name << ". would you accept the trade, please enter accept or reject." << endl << endl;
                            string decision;
                            cin >> decision;
                            if (decision == "accept") {
                                trade(*currPlayer, name, give, receive);
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
        } else if (cmd == "mortgage") {
            string property;
            cin >> property;
            if (checkPlayerOwnBuilding(currPlayer->getName(), property)) {
                mortgage(getBuildingIndex(property), *currPlayer);
            } else {
                cout << "you do not own this building, please enter your command." << endl << endl;
                continue;
            }

        } else {
            cout << "Please re-enter a valid command." << endl << endl;
        }
    }

    currPlayer->addMoney(-ownMoney);
    
    if (ownBank) {
        ownBank = false;
        cout << "You have paid the tuition to bank. Please continue." << endl << endl;
    } else {
        int buildidx = currPlayer->getPosition();
        string buildowner = buildings[buildidx]->getOwner();
        int playeridx = 0;
        for (int i = 0; i < playerNumber; i++) {
            if (players[i].getName() == buildowner) {
                break;
            }
            playeridx += 1;
        }
        players[playeridx].addMoney(ownMoney);
        cout << "You have paid the tuition to the owner. Please continue." << endl << endl;
    }
    ownMoney = 0;
}

void GameBoard::bankrupt() {
    size_t pos = currPlayer->getPosition();
    string ownername;
    vector<size_t> auctname = deletePlayer(*currPlayer);
    if (ownBank) {
        for (size_t i = 0; i < auctname.size(); i++) {
            auction(auctname[i]);
        }
    } else {
        for (size_t i = 0; i < auctname.size(); i++) {
            int pay = 0;
            ownername = buildings[pos]->getOwner();
            buildings[i]->setOwner(ownername);
            if (buildings[i]->isMortgaged()) {
                pay += buildings[i]->getPurchaseCost(i) * 0.1;
            } else {
                buildings[i]->setImprovement(0);
            }
            int idx = 0;
            for (int i = 0; i < playerNumber; i++) {
                if (players[i].getName() == ownername) {
                    break;
                }
                idx += 1;
            }

            if (players[idx].getMoney() < pay) {
                currPlayer = &players[idx];
                if (isBankrupt()) {
                    bankrupt();
                } else {
                    OwnMoney();
                }
            } else {
                players[idx].addMoney(-pay);
            }
        }
    }
}

void GameBoard::action(size_t position, int diceSum) {

    // Property type
    if (checkSquareType(position)) {
        cout << "You have step on a property." << endl << endl;

        // Has Owner
        if (buildings[position]->isOwned()) {
            string owner = buildings[position]->getOwner();

            // Current player is the owner
            if (owner == currPlayer->getName()) {
                cout << "You are the owner of this building, please enter your command." << endl << endl;
                return;

            // Owner is someone else
            } else {
                cout << owner << " is the owner of this land.";
                int owneridx = 0;
                for (int i = 0; i < playerNumber; i++) {
                    if (players[i].getName() == owner) {
                        break;
                    }
                    owneridx++;
                }
                int tuition;

                // Residence type
                if (isResidence(position)) {
                    tuition = buildings[position]->getImprovementTuition(position, 0, players[owneridx].getResidenceNumber());
                    cout << " You need to pay $" << tuition << " to " << owner << endl << endl;

                    // do not have enough money
                    if (tuition > currPlayer->getMoney()) {
                        cout << "You do not have enough money to pay the tuition";
                        cout << endl << endl;
                        ownBank = false;
                        ownMoney = tuition;
                        if (isBankrupt()) {
                            bankrupt();
                        } else {
                            OwnMoney();
                        }
                        return;
                    } else {
                        currPlayer->addMoney(-tuition);
                        players[owneridx].addMoney(tuition);
                        cout << "You have paid $" << tuition << " to " << owner << endl << endl;
                    }

                // Gym type 
                } else if (isGym(position)) {
                    tuition = buildings[position]->getImprovementTuition(position, diceSum, players[owneridx].getGymNumber());
                    cout << " You need to pay $" << tuition << " to " << owner << endl << endl;
                    if (tuition > currPlayer->getMoney()) {
                        cout << "You do not have enough money to pay the tuition";
                        cout << endl << endl;
                        ownBank = false;
                        ownMoney = tuition;
                        if (isBankrupt()) {
                            bankrupt();
                        } else {
                            OwnMoney();
                        }
                        return;
                        
                    } else {
                        currPlayer->addMoney(-tuition);
                        players[owneridx].addMoney(tuition);
                        cout << "You have paid $" << tuition << " to " << owner << endl << endl;
                    }

                // Academic type
                } else {
                    tuition = buildings[position]->getImprovementTuition(position, 0, 0);
                    cout << " You need to pay $" << tuition << " to " << owner << endl << endl;
                    if (tuition > currPlayer->getMoney()) {
                        cout << "You do not have enough money to pay the tuition";
                        ownBank = false;
                        ownMoney = tuition;
                        if (isBankrupt()) {
                            bankrupt();
                        } else {
                            OwnMoney();
                        }
                        return;
                    } else {
                        currPlayer->addMoney(-tuition);
                        players[owneridx].addMoney(tuition);
                        cout << "You have paid $" << tuition << " to " << owner << endl << endl;
                    }
                }
            }
        
        // no owner
        } else {
            cout << "The building is not owned by anyone, do you want to buy it or not, please enter Y/N." << endl << endl;
            string decision;
            while (cin >> decision) {
                if (decision == "Y") {
                    buyBuilding(position, *currPlayer);
                    if (isResidence(position)) {
                        currPlayer->addResidenceNumber(1);
                    } else if (isGym(position)) {
                        currPlayer->addGymNumber(1);
                    }
                    break;
                } else if (decision == "N") {
                    auction(position);
                    break;
                } else {
                    cout << "Your input is invalid, please enter Y/N." << endl << endl;
                }
            }
        }

    // non-property
    } else {

        int result, newpos;

        if (position == 2 || position == 17 || position == 33) {
            result = buildings[position]->advanture(position);
            if (result == 12345) {
                if (timsCups < 4) {
                    cout << "Congratulation! You got a Roll Up the Rim cup." << endl << endl;
                    currPlayer->addTimsCups(1);
                    timsCups++;
                } else {
                    cout << "Sorry, the number of Roll up the Rim cup is full, please enter your command." << endl << endl;
                }
            } else if (result == -3) {
                
                newpos = move(position, position + result);
                action(newpos, diceSum);
            } else if (result == -2) {
                newpos = move(position, position + result);
                action(newpos, diceSum);
            } else if (result == -1) {
                newpos = move(position, position + result);
                action(newpos, diceSum);
            } else if (result == 1) {
                newpos = move(position, position + result);
                action(newpos, diceSum);
            } else if (result == 2) {
                newpos = move(position, position + result);
                action(newpos, diceSum);
            } else if (result == 3) {
                newpos = move(position, position + result);
                action(newpos, diceSum);
            } else if (result == 100) {
                currPlayer->setPosition(10);
                currPlayer->changeJailTurn(1);
                currPlayer->changeWay();
                newpos = move(position, 10);
                cout << "You are in DC Tims Line now!" << endl << endl;
            } else {
                currPlayer->setPosition(0);
                newpos = move(position, 0);
                currPlayer->addMoney(200);
                cout << "You are in COLLECT OSAP now!" << endl << endl;
            }
            
        } else if (position == 4) {
            result = buildings[position]->advanture(position);
            if (result == -300) {
                if (currPlayer->getMoney() < 300) {
                    cout << "You do not have enough money to pay for the tuition." << endl << endl;
                    ownBank = true;
                    ownMoney = 300;
                    if (isBankrupt()) {
                        bankrupt();
                    } else {
                        OwnMoney();
                    }
                    return;
                } else {
                    currPlayer->addMoney(result);
                    cout << "You have paid $300 to the bank." << endl << endl;
                }
            } else {
                int pay = assetEva() * 0.1;
                if (currPlayer->getMoney() < pay) {
                    cout << "You do not have enough money to pay for the tuition." << endl << endl;
                    ownBank = true;
                    ownMoney = pay;
                    if (isBankrupt()) {
                        bankrupt();
                    } else {
                        OwnMoney();
                    }
                    return;
                } else {
                    currPlayer->addMoney(-pay);
                    cout << "You have paid $" << pay << " to the bank." << endl << endl;
                }
            }
        } else if (position == 7 || position == 22 || position == 36) {
            result = buildings[position]->advanture(position);
            if (result == -200) {
                if (currPlayer->getMoney() < 200) {
                    cout << "You do not have enough money to pay for the tuition." << endl << endl;
                    ownBank = true;
                    ownMoney = 200;
                    if (isBankrupt()) {
                        bankrupt();
                    } else {
                        OwnMoney();
                    }
                    return;
                } else {
                    currPlayer->addMoney(result);
                    cout << "You have paid $200 to the bank." << endl << endl;
                }
            } else if (result == -100) {
                if (currPlayer->getMoney() < 100) {
                    cout << "You do not have enough money to pay for the tuition." << endl << endl;
                    ownBank = true;
                    ownMoney = 100;
                    if (isBankrupt()) {
                        bankrupt();
                    } else {
                        OwnMoney();
                    }
                    return;
                } else {
                    currPlayer->addMoney(result);
                    cout << "You have paid $100 to the bank." << endl << endl;
                }
            } else if (result == 25) {
                currPlayer->addMoney(result);
                cout << "You just earned $25." << endl << endl;
            } else if (result == 50) {
                currPlayer->addMoney(result);
                cout << "You just earned $50." << endl << endl;
            } else if (result == 100) {
                currPlayer->addMoney(result);
                cout << "You just earned $100." << endl << endl;
            } else if (result == 200) {
                currPlayer->addMoney(result);
                cout << "You just earned $200." << endl << endl;
            } else {
                if (timsCups < 4) {
                    cout << "Congratulation! You got a Roll Up the Rim cup." << endl << endl;
                    currPlayer->addTimsCups(1);
                    timsCups++;
                } else {
                    cout << "Sorry, the number of Roll up the Rim cup is full, please enter your command." << endl << endl;
                }
            }
        } else if (position == 20) {
            cout << "Goose Attack!" << endl << endl;
        } else if (position == 30) {
            currPlayer->setPosition(10);
            currPlayer->changeJailTurn(1);
            currPlayer->changeWay();
            newpos = move(position, 10);
            cout << "You are in DC Tims Line now." << endl << endl;
        } else if (position == 38) {
            if (currPlayer->getMoney() < 150) {
                cout << "You do not have enough money to pay for the COOP FEE." << endl << endl;
                ownBank = true;
                ownMoney = 150;
                if (isBankrupt()) {
                    bankrupt();
                } else {
                    OwnMoney();
                }
                return;
            } else {
                currPlayer->addMoney(-150);
                cout << "You have paid $150 to the bank." << endl << endl;
            }
        } else if (position == 0) {
            return;

        } else {
            cout << "you are not inside DC Tims Line, nothing happened." << endl << endl;
            return;
        }
    }
}

void GameBoard::roll() {
    if (rolled) {
        cout << "You have rolled before, you can not roll again." << endl << endl;
        return;
    }
    rolled = true;
    srand(time(0));
    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;
    bool doubleroll = false;
    if (dice1 == dice2) {
        doubleroll = true;
        rolled = false;
    }
    int pos = currPlayer->getPosition();
    cout << "You have rolled " << dice1 << " and " << dice2 << endl << endl;
    cout << "You have moved from " << getBuildingName(pos) << " to " << getBuildingName(pos + dice1 + dice2) << "." << endl << endl;
    numroll += 1;
    if (numroll == 3) {
        cout << "You have rolled three times, you are send to Tims Line." << endl << endl;
        currPlayer->setPosition(10);
        currPlayer->changeJailTurn(1);
        currPlayer->changeWay();
        move(pos, 10);
        return;
    }

    // when in tims line
    if (pos == 10) {
        if (doubleroll) {
            int timsturn = currPlayer->getTurn();
            if (timsturn == 0) {
                currPlayer->changeJailTurn(-1);
                move(pos, pos + dice1 + dice2);
                action(pos + dice1 + dice2, dice1 + dice2);
            } else if (timsturn == 1) {
                currPlayer->changeJailTurn(-2);
                move(pos, pos + dice1 + dice2);
                action(pos + dice1 + dice2, dice1 + dice2);
            } else {
                currPlayer->changeJailTurn(-3);
                move(pos, pos + dice1 + dice2);
                action(pos + dice1 + dice2, dice1 + dice2);
            }
        } else {
            if (currPlayer->getTurn() == 2) {
                cout << "You must pay $50 or use a Roll Up the Rim cup, enter money or cup." << endl << endl;
                string option;
                cin >> option;
                if (option == "money") {
                    if (currPlayer->getMoney() < 50) {
                        cout << "You do not have enough money to pay for the tuition." << endl << endl;
                        ownBank = true;
                        ownMoney = 50;
                        if (isBankrupt()) {
                            bankrupt();
                            return;
                        } else {
                            OwnMoney();
                            return;
                        }
                        return;
                    } else {
                        currPlayer->addMoney(-50);
                        return;
                    }
                } else if (option == "cup") {
                    if (currPlayer->getTimsCups() <= 0) {
                        cout << "You do not have enough cup, please use money to pay." << endl << endl;
                        if (currPlayer->getMoney() < 50) {
                            cout << "You do not have enough money to pay for the tuition." << endl << endl;
                            ownBank = true;
                            ownMoney = 50;
                            if (isBankrupt()) {
                                bankrupt();
                                return;
                            } else {
                                OwnMoney();
                                return;
                            }
                            return;
                        } else {
                            currPlayer->addMoney(-50);
                            return;
                        }
                    } else {
                        currPlayer->addTimsCups(-1);
                        timsCups--;
                        return;
                    }
                }
            currPlayer->changeJailTurn(-3);
            move(pos, pos + dice1 + dice2);
            currPlayer->changeWay();
            action(pos + dice1 + dice2, dice1 + dice2);
            }
            
            else {
                cout << "You could pay $50 or use a Roll Up the Rim cup, enter money, cup, or stay."  << endl << endl;
                string option;
                cin >> option;
                if (option == "money") {
                    if (currPlayer->getMoney() < 50) {
                        cout << "You do not have enough money to pay for the tuition." << endl << endl;
                        ownBank = true;
                        ownMoney = 50;
                        if (isBankrupt()) {
                            bankrupt();
                            return;
                        } else {
                            OwnMoney();
                            return;
                        }
                    } else {
                        if (currPlayer->getTurn() == 0) {
                            currPlayer->changeJailTurn(-1);
                            return;
                        } else {
                            currPlayer->changeJailTurn(-2);
                            return;
                        }
                        currPlayer->addMoney(-50);
                        move(pos, pos + dice1 + dice2);
                        action(pos + dice1 + dice2, dice1 + dice2);
                    }
                } else if (option == "cup") {
                    if (currPlayer->getTimsCups() <= 0) {
                        cout << "You do not have enough cup, please use money to pay." << endl << endl;
                        if (currPlayer->getMoney() < 50) {
                            cout << "You do not have enough money to pay for the tuition." << endl << endl;
                            ownBank = true;
                            ownMoney = 50;
                            if (isBankrupt()) {
                                bankrupt();
                            } else {
                                OwnMoney();
                            }
                            return;
                        } else {
                            currPlayer->addMoney(-50);
                            return;
                        }
                    } else {
                        currPlayer->addTimsCups(-1);
                        timsCups--;
                        if (currPlayer->getTurn() == 0) {
                            currPlayer->changeJailTurn(-1);
                            return;
                        } else {
                            currPlayer->changeJailTurn(-2);
                            return;
                        }
                        currPlayer->changeWay();
                        move(pos, pos + dice1 + dice2);
                        action(pos + dice1 + dice2, dice1 + dice2);
                    }
                }
            }
        }
    }
    
    int newpos = move(pos, pos + dice1 +dice2);
    action(newpos, dice1 + dice2);


    
    

    // tims cup
    if (numroll < 3 && doubleroll) {
        cout << "Since you rolled a double, you can roll again" << endl << endl;
        roll();
    } else if (numroll == 3) {
            currPlayer->changeJailTurn(1);
            currPlayer->setPosition(10);
            currPlayer->changeWay();
            newpos = move(newpos, 10);
    }
}

void GameBoard::newGame() {
    cout << "A new Game has been created, please insert the number of player from 2 to 6;" << endl << endl;
    int num = 0;
    while (cin >> num) {
        if (num >= 2 && num <= 6) {
            playerNumber = num;
            break;
        } else {
            cout << "Your input is invalid, please enter a number between 2 to 6" << endl << endl;
        }
    }
    addPlayer(num);
    playerNumber = num;
    
    currPlayer = &players[0];
    cout << "All players are set, you can start the game now!" << endl;
}

void GameBoard::loadGame(const string filename) {
    ifstream infile;
    infile.open(filename);

    infile >> playerNumber;
    string playername;
    char playerchar;
    size_t position;
    int numcups, money;
    int intims = -1;
    int timsturn = -1;
    
    for (int i = 0; i < playerNumber; i++) {
        
        infile >> playername >> playerchar >> numcups >> money >> position;
        buildings[position]->add_player_to_square(playerchar, i);
        // in Tims Line

        if (position == 10) {
            infile >> intims;
            if (intims) {
                infile >> timsturn;
            }
        }

        
        players.emplace_back(playername, playerchar, position, money, numcups, timsturn, intims, 0, 0);
    }
    currPlayer = &players[0];
    string buildname;
    string owner;
    int improvements;
    
    for (int i = 0; i < 28; i++) {
        infile >> buildname >> owner >> improvements;
        if (owner == "BANK") {
            continue;
        }
        
        // building has owner
        else {
            for (int j = 0; j < playerNumber; j++) {
                if (players[j].getName() == owner) {
                    int index = getBuildingIndex(buildname);
                    players[j].buyProperty(index);
                    players[j].changeMonopolyValue(index, getMonopolyValue(index));
                }
            }
        
            for (int k = 0; k < 40; k++) {
                if (getBuildingName(k) == buildname) {
                    buildings[k]->setOwner(owner);
                    if (improvements == -1) {
                        int idx = 0;
                        for (int s = 0; s < playerNumber; s++) {
                            if (players[s].getName() == owner) {
                                break;
                            }
                            idx++;
                        }
                        mortgage(k, players[idx]);
                    }
                    
                    if (checkSquareType(k) && !(isResidence(k) || isGym(k))) {
                        // is academic building
                        buildings[k]->setImprovement(improvements);
                    }
                }
            }
        }
    }
}

void GameBoard::saveGame(const string filename, int curPlayerindex) {
    ofstream savefile;
    savefile.open(filename);
    savefile << playerNumber << endl;
    for (int i = curPlayerindex + 1; i < playerNumber; i++) {
        string playername;
        char playerToken;
        int playerTimsCups, money;
        size_t position;
        playername = players[i].getName();
        playerToken = players[i].getToken();
        playerTimsCups = players[i].getTimsCups();
        money = players[i].getMoney();
        position = players[i].getPosition();
        if (position == 10) {
            if (players[i].getWay()) {
                savefile << playername << " " << playerToken << " " << playerTimsCups << " " << money << " " << position << " 1 " << players[i].getTurn() << endl;
                continue;
            } else {
                savefile << playername << " " << playerToken << " " << playerTimsCups << " " << money << " " << position << " 0" << endl;
                continue;
            }
        }
        savefile << playername << " " << playerToken << " " << playerTimsCups << " " << money << " " << position << endl;
    }
    for (int i = 0; i < curPlayerindex + 1; i++) {
        string playername;
        char playerToken;
        int playerTimsCups, money;
        size_t position;
        playername = players[i].getName();
        playerToken = players[i].getToken();
        playerTimsCups = players[i].getTimsCups();
        money = players[i].getMoney();
        position = players[i].getPosition();
        if (position == 10) {
            if (players[i].getWay()) {
                savefile << playername << " " << playerToken << " " << playerTimsCups << " " << money << " " << position << " 1 " << players[i].getTurn() << endl;
                continue;
            } else {
                savefile << playername << " " << playerToken << " " << playerTimsCups << " " << money << " " << position << " 0" << endl;
                continue;
            }
        }
        savefile << playername << " " << playerToken << " " << playerTimsCups << " " << money << " " << position << endl;
    }
    for (int i = 0; i < 40; i++) {
        if (checkSquareType(i)) {
            string buildingname = getBuildingName(i);
            string owner = buildings[i]->getOwner();
            bool owned = buildings[i]->isOwned();
            int improvements = buildings[i]->getCurrentLevel();
            savefile << buildingname << " ";
            if (owned) {
                savefile << owner << " ";
            }
            else {
                savefile << "BANK" << " ";
            }
            if (improvements == -1) {
                savefile << "Mortgaged" << endl;
            }
            else {
                savefile << improvements << endl;
            }
        }
    }
    savefile.close();
}





