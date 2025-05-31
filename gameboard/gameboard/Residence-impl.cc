module residence;
import <iostream>;
import <cstddef>;
import <string>;
import property;
import square;
using namespace std;

struct ResidenceInfo {
    string name;
    size_t blockPos;
};

static const ResidenceInfo ResidenceProperties[] = {
    {"MKV", 5},
    {"UWP", 15},
    {"V1", 25},
    {"REV", 35}
};

size_t Residence::getResidenceIndex(size_t boardIndex) {
    if (boardIndex == 5) {
        return 0;
    } else if (boardIndex == 15) {
        return 1;
    } else if (boardIndex == 25) {
        return 2;
    } else{
        return 3;
    }
}

Residence::Residence(size_t buildingIndex)
    : Property{
        ResidenceProperties[getResidenceIndex(buildingIndex)].name,
        ResidenceProperties[getResidenceIndex(buildingIndex)].blockPos,
        200
    } {}

int Residence::getImprovementTuition(size_t buildingIndex, int diceRoll, int numPropertiesOwned) {
    if (owner.empty()) {
        return 0;
    }
    if (numPropertiesOwned == 1) {
        return 25;
    } else if (numPropertiesOwned == 2) {
        return 50;
    } else if (numPropertiesOwned == 3) {
        return 100;
    } else if (numPropertiesOwned == 4) {
        return 200;
    } else {
        return 0;
    }
}
    





