export module osap;
import <iostream>;
import <cstddef>;
import <string>;
import square;
import non_property;
using namespace std;

export class OSAP: public Non_Property {
    public:
        OSAP(size_t buildingIndex);
        ~OSAP() {};

        int advanture(size_t buildingIndex) override;
};
