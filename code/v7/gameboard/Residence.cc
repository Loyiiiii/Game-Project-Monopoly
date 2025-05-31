export module residence;
import <iostream>;
import <cstddef>;
import <string>;
import property;
import square;
using namespace std;

export class Residence : public Property {
    public:
    Residence(size_t buildingIndex);
    ~Residence() {}

    size_t getResidenceIndex(size_t boardIndex);

    virtual int getImprovementTuition(size_t buildingIndex, int diceRoll, int numPropertiesOwned) override;  
};


    