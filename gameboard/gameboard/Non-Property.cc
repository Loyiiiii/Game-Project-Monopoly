export module non_property;
import <iostream>;
import <cstddef>;
import <string>;
import square;
using namespace std;

export class Non_Property : public Square {
    public:
        Non_Property(const string& name, size_t pos, int purchaseCost);
        virtual ~Non_Property() {};
};


