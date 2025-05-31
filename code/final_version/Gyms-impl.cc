module gyms;
import <iostream>;
import <cstddef>;
import <string>;
import property;
import square;
using namespace std;

struct GymsInfo {
    string name;
    size_t blockPos;
};

static const GymsInfo GymsProperties[] = {
    {"PAC", 12},
    {"CIF", 28}
};

size_t Gyms::getGymIndex(size_t boardIndex) {
    return (boardIndex == 12) ? 0 : 1;
}

Gyms::Gyms(size_t buildingIndex)
    : Property{
        GymsProperties[getGymIndex(buildingIndex)].name,
        GymsProperties[getGymIndex(buildingIndex)].blockPos,
        150
    } {}
    

int Gyms::getImprovementTuition(size_t buildingIndex, int diceRoll, int numPropertiesOwned) {
    if (numPropertiesOwned == 1) {
        return diceRoll * 4;
    } else if (numPropertiesOwned >= 2) {
        return diceRoll * 10;
    } else {
        return 0;
    }
}



