module gototims;
import <iostream>;
import <cstddef>;
import <string>;
import square;
import non_property;
using namespace std;

struct GoToTims_Info {
    string name;
    size_t blockPos;
};

static const GoToTims_Info GoToTims_Properties = {"GoToTims", 30};

GoToTims::GoToTims(size_t buildingIndex) :  Non_Property{GoToTims_Properties.name, GoToTims_Properties.blockPos, 0} {}

int GoToTims::advanture(size_t buildingIndex) {
    return 10;  //pos of DC Tims Line
}
