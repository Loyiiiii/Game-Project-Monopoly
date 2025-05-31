module player;
import <iostream>;
import <string>;
import <vector>;
import <cstddef>;
import propertyinfo;
using namespace std;

const int INITIAL_FUND = 1500;
const int BIGGEST_BOARD_INDEX = 39;

Player::Player(string name, char token):
    name{name}, token{token}, position{0}, money{INITIAL_FUND}, timsCups{0},
    jailTurnNumber{-1}, wayToTheJail{false}, GymNumber{0}, ResidenceNumber{0} { }

Player::Player(string name, char token, size_t position, int money, int timsCups, 
    int jailTurnNumber, bool wayToTheJail, int GymNumber, int ResidenceNumber):
    name{name}, token{token}, position{position}, money{money}, timsCups{timsCups},
    jailTurnNumber{jailTurnNumber}, wayToTheJail{wayToTheJail}, GymNumber{GymNumber},
    ResidenceNumber{ResidenceNumber} { }

string Player::getName() const { return name; }

char Player::getToken() const { return token; }

size_t Player::getPosition() const { return position; }

int Player::getMoney() const { return money; }

vector<PropertyInfo> Player::getProperty() const { return property; }

int Player::getTimsCups() const { return timsCups; }

bool Player::checkProperty(size_t index) {
    for (auto currProp : property) {
        if (currProp.buildingIndex == index) { return true; }
    }
    return false;
}

int Player::getImproveLevel(size_t index) {
    for (auto& currProp : property) {
        if (currProp.buildingIndex == index) {
            return currProp.improveLevel;
        }
    }
    return 0;
}

int Player::getGymNumber() const { return GymNumber; }

int Player::getResidenceNumber() const { return ResidenceNumber; }

// Something can Player do
void Player::setPosition(const size_t pos) {
    if (pos < 0 || pos > BIGGEST_BOARD_INDEX) {
        cout << "your input is invaliid." << endl;
        return;
    }
    position = pos; 
}

void Player::addPosition(const int step) { position = (position + step) % 40; }

void Player::addMoney(const int value) { money += value; }

void Player::buyProperty(size_t index) {
    property.emplace_back(index, 0, -1);
}

void Player::deleteProperty(size_t index) {
    for (auto it = property.begin(); it != property.end(); ) {
        if (it->buildingIndex == index) {
            it = property.erase(it); 
        } else {
            ++it;
        }
    }
}

void Player::improveProperty(size_t index) {
    for (auto& pr : property) {
        if (pr.buildingIndex == index) {
            if (pr.improveLevel >= 5) {
                cout << "This building is reached highest level." << endl;
            } else {
                pr.improveLevel += 1;
            }
            return;
        }
    }
    cout << "You did not own this building yet." << endl;
}

void Player::changeMonopolyValue(size_t index, int monoVal) {
    for (auto& pr : property) {
        if (pr.buildingIndex == index) {
            pr.monopolyValue = monoVal;
        }
    }
}

void Player::setImproveLevel(size_t index, int level) {
    for (auto& currProp : property) {
        if (currProp.buildingIndex == index) {
            currProp.improveLevel = level;
        }
    }
}

void Player::mortgageProperty(size_t index) {
    setImproveLevel(index, -1);
}

void Player::unMortgageProperty(size_t index) {
    setImproveLevel(index, 0);
}

void Player::addGymNumber(int num) { GymNumber += num; }

void Player::addResidenceNumber(int num) { ResidenceNumber += num; }

void Player::addTimsCups(int num) { timsCups += 1; }

void Player::changeWay() { wayToTheJail = !wayToTheJail; }

bool Player::getWay() const { return wayToTheJail; }
int Player::getTurn() const { return jailTurnNumber; }
void Player::changeJailTurn(int num) { jailTurnNumber += num; }

ostream& operator<<(ostream& out, const Player& pl) {
    out << "Player: " << pl.getName() << endl;
    out << "Token: " << pl.getToken() << endl;
    out << "Position: " << pl.getPosition() << endl;
    out << "Money: $" << pl.getMoney() << endl;
    if (pl.property.empty()) {
        out << "This player doesn't have any property." << endl;
    } else {
        out << "Property: " << endl;
        for (auto pr : pl.property) {
            out << pr.buildingIndex << "(improve level: " 
                << pr.improveLevel << ", monopolyValue: " 
                << pr.monopolyValue << ")" << endl;
        }
        out << endl;
    }
    return out;
}
