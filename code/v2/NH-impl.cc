module nh;
import <iostream>;
import <cstddef>;
import <string>;
import square;
import non_property;
using namespace std;

struct NH_Info {
    string name;
    size_t blockPos;
};

static const NH_Info NH_Properties[] = {
    {"NH", 7},
    {"NH", 22},
    {"NH", 36}
};

size_t NH::getNHIndex(size_t boardIndex) {
    if (boardIndex == 7) {
        return 0;
    } else if (boardIndex == 22) {
        return 1;
    } else {
        return 2;
    }
}

NH::NH(size_t buildingIndex) : Non_Property{NH_Properties[buildingIndex].name, NH_Properties[buildingIndex].blockPos, 0} {}

int NH::advanture(size_t buildingIndex) {
    int RimCup = rand() % 100;
    if (RimCup == 0) {
        return 12345;   //special code for rim cup
    } else {
        int card = rand() % 18 + 1;
        if (card == 1) {
            return -200;
        } else if (card <= 3) {
            return -100;
        } else if (card <= 6) {
            return -50;
        } else if (card <= 12) {
            return 25;
        } else if (card <= 15) {
            return 50;
        } else if (card <= 17) {
            return 100;
        } else {
            return 200;
        }
    }
}
