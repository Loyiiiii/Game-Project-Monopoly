export module goose_nesting;
import <iostream>;
import <cstddef>;
import <string>;
import square;
import non_property;
using namespace std;

class GooseNesting: public Non_Property {
    public:
        GooseNesting(size_t buildingIndex);
        ~GooseNesting() {};

        int advanture(size_t buildingIndex) override;
};