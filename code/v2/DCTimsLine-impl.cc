module dctimsline;
import <iostream>;
import <cstddef>;
import <string>;
import square;
import non_property;
using namespace std;

struct DCTimsLine_Info {
    string name;
    size_t blockPos;
};

static const DCTimsLine_Info DCTimsLine_Properties = {"DCTimsLine", 10};

DCTimsLine::DCTimsLine(size_t buildingIndex) :  Non_Property{DCTimsLine_Properties.name, DCTimsLine_Properties.blockPos, 0} {}

int DCTimsLine::advanture(size_t buildingIndex) {
    return 0;
}
