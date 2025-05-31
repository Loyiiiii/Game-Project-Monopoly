export module tuition;
import <iostream>;
import <cstddef>;
import <string>;
import square;
import non_property;
using namespace std;

export class Tuition: public Non_Property {
        int choice;
        int player_balance;
    public:
        Tuition(size_t buildingIndex, int player_balance);
        ~Tuition() {};

        int advanture(size_t buildingIndex) override;
};




