module property;
import <iostream>;
import <cstddef>;
import <string>;
using namespace std;

Property::Property(const string& name, size_t pos, int purchaseCost)
: Square{name, pos, Type::Property}, purchaseCost{purchaseCost}, mortgaged{false}, owned{false}, owner{""}, currentLevel{0} {}

int Property::getPurchaseCost(size_t buildingIndex) {
    return purchaseCost;
}

bool Property::canBuy(size_t buildingIndex) {
    return !owned;
};

bool Property::isOwned() const {
    return owned;
};

void Property::setOwner(const string& playerName) {
    if (playerName.empty()) {
        owned = false;
        owner = "";
    } else {
        owned = true;
        owner = playerName;
    }
};

string Property::getOwner() const {
    return owner;
};

bool Property::isMortgaged() const {
    return mortgaged;
}

void Property::setImprovement(int level) {
    if (level >= -1 && level <= 5) {
        currentLevel = level;
    } else {
        cout << "Invalid level. Level must be between -1 and 5." << endl;
    }
}

int Property::getCurrentLevel() {
    return currentLevel;
}

void Property::mortgage() {
    if(owned && !mortgaged){
        mortgaged = true;
        setImprovement(-1);
    }
}

void Property::unmortgage() {
    if(owned && mortgaged){
        mortgaged = false;
        setImprovement(0);
    }
}


