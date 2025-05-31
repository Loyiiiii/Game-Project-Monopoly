export module slc;
import <iostream>;
import <cstddef>;
import <string>;
import square;
import non_property;
using namespace std;

class SLC: public Non_Property {
    public:
        SLC(size_t buildingIndex);
        ~SLC() {};

        size_t getSLCIndex(size_t boardIndex);

        int advanture(size_t buildingIndex) override;
};
