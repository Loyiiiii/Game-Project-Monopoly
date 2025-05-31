export module nh;
import <iostream>;
import <cstddef>;
import <string>;
import square;
import non_property;
using namespace std;

class NH: public Non_Property {
    public:
        NH(size_t buildingIndex);
        ~NH() {};

        size_t getNHIndex(size_t boardIndex);

        int advanture(size_t buildingIndex) override;
};
