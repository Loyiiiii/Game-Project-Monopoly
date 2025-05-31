export module academic;
import <iostream>;
import <cstddef>;
import <string>;
import property;
import square;
using namespace std;

export class Academic : public Property {
    private:
        int improvementCost;
        int currentLevel;
        int tuition[6];
        string monopolyBlock;
    
    public:
        Academic(size_t buildingIndex);
        ~Academic() {};
    
        virtual int getImprovementCost(size_t buildingIndex) override;
        virtual int getImprovementTuition(size_t buildingIndex, int diceRoll, int numPropertiesOwned) override;

        virtual void LevelImprove() override;
        virtual void LevelDegrade() override;
        virtual int getCurrentLevel() const override;
        virtual string getBlock() const override;

};
    
