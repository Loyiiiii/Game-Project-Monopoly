export module dctimsline;
import <iostream>;
import <cstddef>;
import <string>;
import square;
import non_property;
using namespace std;

class DCTimsLine: public Non_Property {
    public:
        DCTimsLine(size_t buildingIndex);
        ~DCTimsLine() {};

        int advanture(size_t buildingIndex) override;
};
