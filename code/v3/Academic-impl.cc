module academic;
import <iostream>;
import <cstddef>;
import <string>;
import property;
import square;
using namespace std;

//有一个问题，这里实现具体的是否应该在gameboard传入grpah里之前就有这些信息？
struct AcademicInfo {
    string name;
    string monopolyBlock;
    size_t blockPos;
    int purchaseCost;
    int improvementCost;
    int tuition[6];
};

static const AcademicInfo academicProperties[] = {
    {},
    {"AL", "Arts1", 1, 40, 50, {2, 10, 30, 90, 160, 250}},
    {},
    {"ML", "Arts1", 3, 60, 50, {4, 20, 60, 180, 320, 450}},
    {},
    {},
    {"ECH", "Arts2", 6, 100, 50, {6, 30, 90, 270, 400, 550}},
    {},
    {"PAS", "Arts2", 8, 100, 50, {6, 30, 90, 270, 400, 550}},
    {"HH", "Arts2", 9, 120, 50, {8, 40, 100, 300, 450, 600}},
    {},
    {"RCH", "Eng", 11, 140, 100, {10, 50, 150, 450, 625, 750}},
    {},
    {"DWE", "Eng", 13, 140, 100, {10, 50, 150, 450, 625, 750}},
    {"CPH", "Eng", 14, 160, 100, {12, 60, 180, 500, 700, 900}},
    {},
    {"LHI", "Health", 16, 180, 100, {14, 70, 200, 550, 750, 950}},
    {},
    {"BMH", "Health", 18, 180, 100, {14, 70, 200, 550, 750, 950}},
    {"OPT", "Health", 19, 200, 100, {16, 80, 220, 600, 800, 1000}},
    {},
    {"EV1", "Env", 21, 220, 150, {18, 90, 250, 700, 875, 1050}},
    {},
    {"EV2", "Env", 23, 220, 150, {18, 90, 250, 700, 875, 1050}},
    {"EV3", "Env", 24, 240, 150, {20, 100, 300, 750, 925, 1100}},
    {},
    {"PHYS", "Sci1", 26, 260, 150, {22, 110, 330, 800, 975, 1150}},
    {"B1", "Sci1", 27, 260, 150, {22, 110, 330, 800, 975, 1150}},
    {},
    {"B2", "Sci1", 29, 280, 150, {24, 120, 360, 850, 1025, 1200}},
    {},
    {"EIT", "Sci2", 31, 300, 200, {26, 130, 390, 900, 1100, 1275}},
    {"ESC", "Sci2", 32, 300, 200, {26, 130, 390, 900, 1100, 1275}},
    {},
    {"C2", "Sci2", 34, 320, 200, {28, 150, 450, 1000, 1200, 1400}},
    {},
    {},
    {"MC", "Math", 37, 350, 200, {35, 175, 500, 1100, 1300, 1500}},
    {},
    {"DC", "Math", 39, 400, 200, {50, 200, 600, 1400, 1700, 2000}}
};

Academic::Academic(size_t buildingIndex)
    : Property{
        academicProperties[buildingIndex].name,
        academicProperties[buildingIndex].blockPos,
        academicProperties[buildingIndex].purchaseCost
        },
      improvementCost{academicProperties[buildingIndex].improvementCost},
      currentLevel{0},
      monopolyBlock{academicProperties[buildingIndex].monopolyBlock} {
    for (int i = 0; i < 6; ++i) {
        tuition[i] = academicProperties[buildingIndex].tuition[i];
    }
}

/*
Academic::Academic(const string &name, size_t pos, int cost, int impCost, const int tuitions[6], const string &blockName)
    : Property{name, pos, cost}, 
      improvementCost{impCost}, 
      currentLevel{0}, 
      monopolyBlock{blockName} {
    for (int i = 0; i < 6; ++i) {
        tuition[i] = tuitions[i];
    }
}
*/

int Academic::getImprovementCost(size_t buildingIndex) {
    return improvementCost;
}

int Academic::getImprovementTuition(size_t buildingIndex, int diceRoll, int numPropertiesOwned) {
    return tuition[currentLevel];
}

void Academic::LevelImprove() {
    if (currentLevel < 5) {
        currentLevel++;
    }
}

void Academic::LevelDegrade() {
    if (currentLevel > 0) {
        currentLevel--;
    }
}

int Academic::getCurrentLevel() const {
    return currentLevel;
}

string Academic::getBlock() const {
    return monopolyBlock;
}
