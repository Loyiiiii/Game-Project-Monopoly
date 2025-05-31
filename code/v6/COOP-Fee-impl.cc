module coop_fee;
import <iostream>;
import <cstddef>;
import <string>;
import square;
import non_property;
using namespace std;

struct COOP_Fee_Info {
    string name;
    size_t blockPos;
};

static const COOP_Fee_Info COOP_Fee_Property = {"COOP_Fee", 38};

COOP_Fee::COOP_Fee(size_t buildingIndex) : Non_Property{COOP_Fee_Property.name, COOP_Fee_Property.blockPos, 0} {}

int COOP_Fee::advanture(size_t buildingIndex) {
    return -150;
}
