export module property;
import <iostream>;
import <cstddef>;
import <string>;
import square;
using namespace std;

export class Property : public Square {
    protected:
        int purchaseCost;
        bool mortgaged;
        bool owned;
        string owner;
        int level;
        int currentLevel;  
    
    public:
        Property(const string& name, size_t pos, int purchaseCost);
        virtual ~Property() {};

        virtual int getPurchaseCost(size_t buildingIndex) override;
        virtual bool canBuy(size_t buildingIndex) override;
        virtual void setOwner(const string& playerName) override;
        
        virtual bool isOwned() const override;
        virtual string getOwner() const override;
        virtual bool isMortgaged() const override;
        virtual void mortgage() override;
        virtual void unmortgage() override;
        virtual void setImprovement(int level) override;
        virtual int getCurrentLevel() override;
};
    



