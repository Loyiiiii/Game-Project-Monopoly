module square;
import <iostream>;
import <cstddef>;
using namespace std;

Square::Square(const string name, const size_t pos, Type type)
: buildingName{name}, buildingIndex{pos}, type{type} {
    init_squareInfo();
}

string Square::getBuildingName() { 
    return buildingName;
}

size_t Square::getBuildingIndex() { 
    return buildingIndex;
}

Type Square::getType() {
    return type; 
}

void Square::init_squareInfo() {
    for (int i = 0; i < 7; i++) {
        squareInfo[i] = ' ';
    }
}

void Square::add_player_to_square(char player_char, int player_index) {
    if (player_index >= 0 && player_index <= 6) {
        squareInfo[player_index] = player_char;
    }
}

void Square::remove_player_to_square(int player_index) {
    if (player_index >= 0 && player_index <= 6) {
        squareInfo[player_index] = ' ';
    }
}

void Square::get_square() const{
    for (int i = 0; i < 7; i++) {
        cout << squareInfo[i];
    }
}

int Square::getPaid(size_t buildingIndex, int diceRoll, int numPropertiesOwned) { //must be properties
    if (!isOwned()) {
        return 0;
    } else {
        if (
            buildingIndex == 1 ||
            buildingIndex == 3 ||
            buildingIndex == 6 ||  
            buildingIndex == 8 ||
            buildingIndex == 9 ||
            buildingIndex == 11 ||
            buildingIndex == 13 ||
            buildingIndex == 14 ||
            buildingIndex == 16 ||
            buildingIndex == 18 ||
            buildingIndex == 19 ||
            buildingIndex == 21 ||
            buildingIndex == 23 ||
            buildingIndex == 24 ||
            buildingIndex == 26 ||
            buildingIndex == 27 ||
            buildingIndex == 29 ||
            buildingIndex == 31 ||
            buildingIndex == 32 ||
            buildingIndex == 34 ||
            buildingIndex == 37 ||
            buildingIndex == 39
        ) {
            return getImprovementTuition(buildingIndex, diceRoll, numPropertiesOwned);
        } else if (buildingIndex == 12 || buildingIndex == 28) {
            return getImprovementTuition(buildingIndex, diceRoll, numPropertiesOwned);
        } else if (
            buildingIndex == 5 ||
            buildingIndex == 15 ||
            buildingIndex == 25 ||
            buildingIndex == 35
        ) {
            return getImprovementTuition(buildingIndex, diceRoll, numPropertiesOwned);
        } else {
            return 0;
        }
    }
}

ostream& operator<<(ostream& out, const Square& sq) {
    out << sq.buildingName << ' ' << sq.buildingIndex << ' ';
    if (sq.type == Type::Property) {
        out << "Property" << endl;
    } else {
        out << "NonProperty" << endl;
    }
    return out;
}

void Square::setOwner(const string& playerName) {}
bool Square::isOwned() const {return true;}
string Square::getOwner() const {return "a";}              
bool Square::isMortgaged() const {return true;}                      
void Square::mortgage() {}                     
void Square::unmortgage() {}                             
int Square::getPurchaseCost(size_t buildingIndex) {return 0;}        
int Square::getImprovementCost(size_t buildingIndex) {return 0;}      
int Square::getImprovementTuition(size_t buildingIndex, int diceRoll, int numPropertiesOwned) {return 0;}
bool Square::canBuy(size_t buildingIndex) {return true;}
void Square::LevelImprove() {}                
void Square::LevelDegrade() {}                            
int Square::getCurrentLevel() {return 1;}                     
string Square::getBlock() const {return "a";}
void Square::setImprovement(int level) {}

int Square::advanture(size_t buildingIndex) {return 1;}

/*
        buildingIndex == 0 ||
        buildingIndex == 2 ||
        buildingIndex == 4 ||
        buildingIndex == 7 ||
        buildingIndex == 10 ||
        buildingIndex == 17 ||
        buildingIndex == 20 ||
        buildingIndex == 22 ||
        buildingIndex == 30 ||
        buildingIndex == 33 ||
        buildingIndex == 36 ||
        buildingIndex == 38
*/


