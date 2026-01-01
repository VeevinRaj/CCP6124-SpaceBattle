//  FOMALHAUT TT6L
//  CCP6124 SPACE BATTLE PROJECT (Trimester 2530)
//  Member 4: VRISHAL (Main.cpp & Testing)

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Ship;
class Weapon;
class CrewMember;

vector<Ship *> loadShips(string file);
vector<CrewMember *> loadCrew(string file);

void assignCrewToShips(vector<Ship *> &ships, vector<CrewMember *> &crew);
void startBattle(vector<Ship *> &zShips, vector<Ship *> &rShips);

ostream &operator<<(ostream &os, const Ship &s);

int main(int argc, char *argv[])
{

    if (argc != 5)
    {
        cerr << "Usage: " << argv[0]
             << " <ZapezoidShips.csv> <ZapezoidCrew.csv> <RogoatuskanShips.csv> <RogoatuskanCrew.csv>\n";
        return 1;
    }

    string zShipFile = argv[1];
    string zCrewFile = argv[2];
    string rShipFile = argv[3];
    string rCrewFile = argv[4];

    cout << "\n=== FOMALHAUT SPACE BATTLE SIMULATION ===\n";
    cout << "Loading fleet data...\n";

    vector<Ship *> zShips = loadShips(zShipFile);
    vector<CrewMember *> zCrew = loadCrew(zCrewFile);

    vector<Ship *> rShips = loadShips(rShipFile);
    vector<CrewMember *> rCrew = loadCrew(rCrewFile);

    assignCrewToShips(zShips, zCrew);
    assignCrewToShips(rShips, rCrew);

    cout << "\nStarting battle...\n";
    startBattle(zShips, rShips);

    for (auto s : zShips)
        delete s;
    for (auto s : rShips)
        delete s;

    for (auto c : zCrew)
        delete c;
    for (auto c : rCrew)
        delete c;

    cout << "\nMemory released. Program completed.\n";
    return 0;
}

ostream &operator<<(ostream &os, const Ship &s)
{
    return os;
}