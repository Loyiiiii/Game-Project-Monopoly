module gameboard;
import <iostream>;
import <vector>;
import <cstddef>;
import <algorithm>;
import <sstream>;
import <string>;
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

void GameBoard::addPlayer(size_t numPlayers) {
    string playerName;
    char token;
    while (numPlayers > 0) {
        cout << "Please enter your player information: (player name, token)" << endl;
        cin >> playerName >> token;
        if (!players.empty() && checkPlayer(playerName, token)) {
            cout << "The player is already exist, please entre another player" << endl;
        } else {
            players.emplace_back(playerName, token);
            numPlayers -= 1;
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
    if (position == 1 || position == 3 || position == 6 || position == 8 ||
        position == 9 || position == 11 || position == 13 || position == 14 ||
        position == 16 || position == 18 || position == 19 || position == 21 ||
        position == 23 || position == 24 || position == 26 || position == 27 ||
        position == 29 || position == 31 || position == 32 || position == 34 ||
        position == 37 || position == 39) {
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
}

void GameBoard::trade(Player& pl, string playerName, int money, string buildingName) {
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
}

void GameBoard::trade(Player& pl, string playerName, string building1, string building2) {
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
