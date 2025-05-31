module osap;
import <iostream>;
import <cstddef>;
import <string>;
import square;
import non_property;
using namespace std;

struct OSAPInfo {
    string name;
    size_t blockPos;
};

static const OSAPInfo OSAPProperty = {"COLLECT OSAP", 0};

OSAP::OSAP(size_t buildingIndex) : Non_Property{OSAPProperty.name, OSAPProperty.blockPos, 0}{}

int OSAP::advanture(size_t buildingIndex) {
    return 200;
}


