import <iostream>;
import <cstddef>;
import <string>;
import <vector>;
import square;
import property;
import non_property;
import academic;
import gyms;
import residence;
import osap;
import goose_nesting;
import tuition;
import coop_fee;
import slc;
import nh;
import gototims;
import dctimsline;
using namespace std;

int main() {
    vector<Square*> board;

    board.push_back(new Square::Property("Property1", 0, 200));
    board.push_back(new Square::Property("Property2", 1, 300));
    board.push_back(new Square::Property("Property3", 2, 400));
    board.push_back(new Square::Property::Academic(11));
    board.push_back(new Square::Property::Gyms(0)); // PAC
    board.push_back(new Square::Property::Residence(0)); // MKV
    board.push_back(new Square::Non_Property::OSAP(0));
    board.push_back(new Square::Non_Property::GooseNesting(20));
    board.push_back(new Square::Non_Property::Tuition(4, 1000));
    board.push_back(new Square::Non_Property::COOP_Fee(38));
    board.push_back(new Square::Non_Property::SLC(8));
    board.push_back(new Square::Non_Property::NH(7));
    board.push_back(new Square::Non_Property::GoToTims(30));
    board.push_back(new Square::Non_Property::DCTimsLine(10));

    for (Square* square : board) {
        delete square;
    }

    return 0;
}
