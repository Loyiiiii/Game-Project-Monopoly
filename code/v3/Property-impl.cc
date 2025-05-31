module property;
import <iostream>;
import <cstddef>;
import <string>;
using namespace std;

Property::Property(const string& name, size_t pos, int purchaseCost)
: Square{name, pos, Type::Property}, purchaseCost{purchaseCost}, mortgaged{false}, owned{false}, owner{""} {}

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
    owned = true;
    owner = playerName;
};

string Property::getOwner() const {
    return owner;
};

bool Property::isMortgaged() const {
    return mortgaged;
}

void Property::mortgage() {
    if(owned && !mortgaged){
        mortgaged = true;
        // 根据我们gameboard里面来配合
    }
}

void Property::unmortgage() {
    if(owned && mortgaged){
        mortgaged = false;
        // 根据我们gameboard里面来配合
    }
}
