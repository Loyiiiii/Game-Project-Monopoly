export module gototims;
import <iostream>;
import <cstddef>;
import <string>;
import square;
import non_property;
using namespace std;

export class GoToTims: public Non_Property {
    public:
        GoToTims(size_t buildingIndex);
        ~GoToTims() {};

        int advanture(size_t buildingIndex) override;
};
