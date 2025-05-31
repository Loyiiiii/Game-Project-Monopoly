export module coop_fee;
import <iostream>;
import <cstddef>;
import <string>;
import square;
import non_property;
using namespace std;

class COOP_Fee: public Non_Property {
    public:
        COOP_Fee(size_t buildingIndex);
        ~COOP_Fee() {};

        int advanture(size_t buildingIndex) override;
};
