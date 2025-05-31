module slc;
import <iostream>;
import <cstddef>;
import <string>;
import square;
import non_property;
using namespace std;

struct SLC_Info {
    string name;
    size_t blockPos;
};

static const SLC_Info SLC_Properties[] = {
    {"SLC", 2},
    {"SLC", 17},
    {"SLC", 33}
};

size_t SLC::getSLCIndex(size_t boardIndex) {
    if (boardIndex == 2) {
        return 0;
    } else if (boardIndex == 17) {
        return 1;
    } else {
        return 2;
    }
}

SLC::SLC(size_t buildingIndex) : Non_Property{SLC_Properties[getSLCIndex(buildingIndex)].name, 
                                 SLC_Properties[getSLCIndex(buildingIndex)].blockPos, 0} {}

int SLC::advanture(size_t buildingIndex) {
    int RimCup = rand() % 100;
    if (RimCup == 0) {
        return 12345;   //special code for rim cup
    } else {
        int card = rand() % 24 + 1;
        if (card >= 1 && card <= 3) {
            return -3;
        } else if (card <= 7) {
            return -2;
        } else if (card <= 11) {
            return -1;
        } else if (card <= 14) {
            return 1;
        } else if (card <= 18) {
            return 2;
        } else if (card <= 22) {
            return 3;
        } else if (card <= 23) {
            return 100; //need to fix in gameboard
        } else {
            return 1000; //need to fix in gameboard
        }
    }
}




