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

string typeToString(Type t) {
    switch (t) {
        case Type::Academic: return "Academic";
        case Type::OSAP: return "OSAP";
        case Type::GooseNesting: return "GooseNesting";
        case Type::Tuition: return "Tuition";
        case Type::SLC: return "SLC";
        case Type::NH: return "NH";
        case Type::Gym: return "Gym";
        case Type::Residence: return "Residence";
        case Type::GoToTims: return "GoToTims";
        case Type::DCTimsLine: return "DCTimsLine";
        case Type::COOPFee: return "COOPFee";
        default: return "Unknown";
    }
}

int main() {
    vector<Square*> buildings;

    buildings.push_back(new OSAP(0));
    buildings.push_back(new Academic(1));
    buildings.push_back(new SLC(2));
    buildings.push_back(new Academic(3));
    buildings.push_back(new Tuition(4, 0));
    buildings.push_back(new Residence(5));
    buildings.push_back(new Academic(6));
    buildings.push_back(new NH(7));
    buildings.push_back(new Academic(8));
    buildings.push_back(new Academic(9));
    buildings.push_back(new DCTimsLine(10));
    buildings.push_back(new Academic(11));
    buildings.push_back(new Gyms(12));
    buildings.push_back(new Academic(13));
    buildings.push_back(new Academic(14));
    buildings.push_back(new Residence(15));
    buildings.push_back(new Academic(16));
    buildings.push_back(new SLC(17));
    buildings.push_back(new Academic(18));
    buildings.push_back(new Academic(19));
    buildings.push_back(new GooseNesting(20));
    buildings.push_back(new Academic(21));
    buildings.push_back(new NH(22));
    buildings.push_back(new Academic(23));
    buildings.push_back(new Academic(24));
    buildings.push_back(new Residence(25));
    buildings.push_back(new Academic(26));
    buildings.push_back(new Academic(27));
    buildings.push_back(new Gyms(28));
    buildings.push_back(new Academic(29));
    buildings.push_back(new GoToTims(30));
    buildings.push_back(new Academic(31));
    buildings.push_back(new Academic(32));
    buildings.push_back(new SLC(33));
    buildings.push_back(new Academic(34));
    buildings.push_back(new Residence(35));
    buildings.push_back(new NH(36));
    buildings.push_back(new Academic(37));
    buildings.push_back(new COOP_Fee(38));
    buildings.push_back(new Academic(39));

    for (auto* sq : buildings) {
        cout << *sq << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        cout << sq->getBuildingName() << " " << sq->getBuildingIndex() << endl;
    }
    cout << "----------------------------------------" << endl;     
    for (auto* sq : buildings) {
        cout << typeToString(sq->getType()) << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        cout << sq->getPaid(sq->getBuildingIndex(), 2, 1) << endl;
    }
    cout << "----------------------------------------" << endl;

    for (auto* sq : buildings) {
        cout << sq->getImprovementCost(sq->getBuildingIndex()) << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        cout << sq->getImprovementTuition(sq->getBuildingIndex(), 2, 1) << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        cout << sq->getCurrentLevel() << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        cout << sq->getBlock() << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        cout << sq->getOwner() << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        cout << sq->isOwned() << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        cout << sq->isMortgaged() << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        cout << sq->getPurchaseCost(sq->getBuildingIndex()) << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        cout << sq->canBuy(sq->getBuildingIndex()) << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        cout << sq->advanture(sq->getBuildingIndex()) << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        sq->LevelImprove();
    }
    for (auto* sq : buildings) {
        cout << sq->getCurrentLevel() << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        sq->LevelDegrade();
    }
    for (auto* sq : buildings) {
        cout << sq->getCurrentLevel() << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        sq->setImprovement(2);
    }
    for (auto* sq : buildings) {
        cout << sq->getCurrentLevel() << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        sq->setImprovement(-1);
    }
    for (auto* sq : buildings) {
        cout << sq->getCurrentLevel() << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        sq->setImprovement(6);
    }
    for (auto* sq : buildings) {
        cout << sq->getCurrentLevel() << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        sq->setOwner("Player1");
    }
    for (auto* sq : buildings) {
        cout << sq->getOwner() << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        sq->mortgage();
    }
    for (auto* sq : buildings) {
        cout << sq->isMortgaged() << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        sq->unmortgage();
    }
    for (auto* sq : buildings) {
        cout << sq->isMortgaged() << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        sq->add_player_to_square('A', 1);
    }
    for (auto* sq : buildings) {
        cout << sq->getBuildingName() << " " << sq->getBuildingIndex() << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        sq->remove_player_to_square(1);
    }
    for (auto* sq : buildings) {
        cout << sq->getBuildingName() << " " << sq->getBuildingIndex() << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        cout << sq->getBuildingName() << " " << sq->getBuildingIndex() << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        cout << typeToString(sq->getType()) << endl;
    }
    cout << "----------------------------------------" << endl;
    for (auto* sq : buildings) {
        cout << sq->getPaid(sq->getBuildingIndex(), 2, 1) << endl;
    }
    cout << "----------------------------------------" << endl;

    
    for (Square* sq : buildings) {
        delete sq;
    }

    return 0;
}
