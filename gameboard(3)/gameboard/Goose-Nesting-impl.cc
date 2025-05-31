module goose_nesting;
import <iostream>;
import <cstddef>;
import <string>;
import square;
import non_property;
using namespace std;

struct GooseNesting_Info {
    string name;
    size_t blockPos;
};

static const GooseNesting_Info GooseNesting_Property = {"GooseNesting", 20};

GooseNesting::GooseNesting(size_t buildingIndex) : Non_Property{GooseNesting_Property.name, GooseNesting_Property.blockPos, 0} {}

int GooseNesting::advanture(size_t buildingIndex) {return 0;}



