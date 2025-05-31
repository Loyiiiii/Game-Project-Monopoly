module non_property;
import <iostream>;
import <cstddef>;
import <string>;
import square;
using namespace std;

Non_Property::Non_Property(const string& name, size_t pos, int purchaseCost)
    : Square{name, pos, Type::NonProperty} {}

