export module gyms;
import <iostream>;
import <cstddef>;
import <string>;
import property;
import square;
using namespace std;

export class Gyms : public Property {
    public:
    Gyms(size_t buildingIndex);
    ~Gyms() {};

    size_t getGymIndex(size_t boardIndex);

    virtual int getImprovementTuition(size_t buildingIndex, int diceRoll, int numPropertiesOwned) override;
};
    




