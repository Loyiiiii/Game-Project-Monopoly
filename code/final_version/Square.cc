export module square;
import <iostream>;
import <cstddef>;
using namespace std;

export enum class Type {
        Property, 
        NonProperty,
        Academic,
        OSAP,
        GooseNesting,
        Tuition,
        SLC,
        NH,
        Gym,
        Residence,
        GoToTims,
        DCTimsLine,
        COOPFee
};

export class Square {
        string buildingName;
        size_t buildingIndex;
        Type type;
        char squareInfo[7];
//  need      char player_char; 
//  need      int player_index;
//  need      int player_balance;(for tuition)
//  need      string player_name;

    public:
        Square(const string name, const size_t pos, Type type);
        virtual ~Square() {};

        friend ostream& operator<<(ostream& out, const Square& sq);

        string getBuildingName();
        size_t getBuildingIndex();
        void init_squareInfo();
        void add_player_to_square(char player_char, int player_index);
        void remove_player_to_square(int player_index);
        void get_square() const;
        Type getType();
        
        // Property method
        virtual void setOwner(const string& playerName);       //Property
        virtual bool isOwned() const;                          //Property
        virtual string getOwner() const;                       //Property
        virtual bool isMortgaged() const;                      //Property
        virtual void mortgage();                               //Property
        virtual void unmortgage();                             //Property
        virtual int getPurchaseCost(size_t buildingIndex);          //Property
        virtual int getImprovementCost(size_t buildingIndex);       //Allthree
        virtual int getImprovementTuition(size_t buildingIndex, int diceRoll, int numPropertiesOwned);    //Allthree
        virtual bool canBuy(size_t buildingIndex);                  //Property
        virtual void LevelImprove();                                //Academic
        virtual void LevelDegrade();                                //Academic
        virtual int getCurrentLevel();                        //Academic
        virtual string getBlock() const;                               //Academic
        virtual void setImprovement(int level);                     //Academic

        int getPaid(size_t buildingIndex, int diceRoll, int numPropertiesOwned);

        // Non-Property Method
        virtual int advanture(size_t buildingIndex);
};

export ostream& operator<<(ostream& out, const Square& sq);




