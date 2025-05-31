export module player;
import <iostream>;
import <string>;
import <vector>;
import <cstddef>;
import propertyinfo;
using namespace std;

export class Player {
    string name;
    char token;
    size_t position;
    int money;
    vector<PropertyInfo> property;
    int timsCups;
    int jailTurnNumber;
    bool wayToTheJail;
    int GymNumber;
    int ResidenceNumber;
public:
    // Basic information of Player
    Player(string name, char token);
    Player(string name, char token, size_t position, 
           int money, int timsCups, int jailTurnNumber, 
           bool wayToTheJail, int GymNumber, int ResidenceNumber);
    string getName() const;
    char getToken() const;
    size_t getPosition() const;
    int getMoney() const;
    vector<PropertyInfo> getProperty() const;
    int getTimsCups() const;
    int getTurn() const;
    bool checkProperty(size_t index);
    int getImproveLevel(size_t index);
    int getGymNumber() const;
    int getResidenceNumber() const;

    // Something can Player do
    void setPosition(const size_t pos);
    void addPosition(const int step);
    void addMoney(const int value);
    void buyProperty(size_t index);
    void deleteProperty(size_t index);
    void improveProperty(size_t index);
    void changeMonopolyValue(size_t index, int monoVal);
    void setImproveLevel(size_t index, int level);
    void mortgageProperty(size_t index);
    void unMortgageProperty(size_t index);
    void addGymNumber(int num);
    void addResidenceNumber(int num);
    void addTimsCups(int num);
    void changeWay();
    void changeJailTurn(int num);

    // Outputs the Player
    friend ostream& operator<<(ostream& out, const Player& pl);
};

ostream& operator<<(ostream& out, const Player& pl);
