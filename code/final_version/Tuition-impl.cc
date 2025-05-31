module tuition;
import <iostream>;
import <cstddef>;
import <string>;
import square;
import non_property;
using namespace std;

struct Tuition_Info {
    string name;
    size_t blockPos;
};

static const Tuition_Info Tuition_Property = {"Tuition", 4};

Tuition::Tuition(size_t buildingIndex, int player_balance) : Non_Property{Tuition_Property.name, Tuition_Property.blockPos, 0}, player_balance{player_balance} {}

int Tuition::advanture(size_t buildingIndex) {
    cout << "You landed on Tuition! Choose payment method:\n";
    cout << "1. Pay $300\n";
    cout << "2. Pay 10%/ of your total worth\n" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        return -300;
    } else {
        return 10;
    }
}




