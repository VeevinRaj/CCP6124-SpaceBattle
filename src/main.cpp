//  FOMALHAUT TT6L
//  CCP6124 SPACE BATTLE PROJECT (Trimester 2530)
//  Member 4: VRISHAL (Main.cpp & Integration)

#include <iostream>
#include <vector>
#include <string>

#include "../include/FileParser.h"
#include "../include/Ship.h"
#include "../include/CrewMember.h"

using namespace std;

ostream& operator<<(ostream& os, const Ship& s) {
    os << s.getId() << " - " << s.getName()
       << " [" << (s.isFactionZapezoid() ? "Zapezoid" : "Rogoatuskan") 
       << " " << s.getType() << "]\n"
       << "  HP: " << s.getHitPoints() << "/" << s.getMaxHitPoints() << "\n"
       << "  Crew: Pilots " << s.getPilotsAssigned() << "/" << s.getPilotsNeeded()
       << ", Gunners " << s.getGunnersAssigned() << "/" << s.getGunnersNeeded()
       << ", Torpedo Handlers " << s.getTorpedoHandlersAssigned() << "/" << s.getTorpedoHandlersNeeded() << "\n"
       << "  Weapons: " << s.getEffectiveLightCannons() << "/" << s.getLightCannonCount()
       << " light cannons, " << s.getEffectiveTorpedoes() << "/" << s.getTorpedoCount() 
       << " torpedoes\n";
    return os;
}

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        cerr << "Usage: " << argv[0]
             << " <ZShips.csv> <ZCrew.csv> <RShips.csv> <RCrew.csv>\n";
        return 1;
    }

    cout << "\n=== FOMALHAUT SPACE BATTLE SIMULATION ===\n";

    FileParser zParser(argv[1]);
    FileParser rParser(argv[3]);

    if (!zParser.parseShipsFile(argv[1]) || !zParser.parseCrewFile(argv[2]) ||
        !rParser.parseShipsFile(argv[3]) || !rParser.parseCrewFile(argv[4]))
    {
        cerr << "Error parsing input files.\n";
        return 1;
    }

    vector<Ship*> zShips;
    vector<Ship*> rShips;

    for (int i = 0; i < zParser.getShipCount(); i++)
    {
        string id = zParser.getShipID(i);
        string type = zParser.getShipType(i);
        string name = zParser.getShipName(i);

        if (type == "Guerriero")
            zShips.push_back(new Guerriero(id, name));
        else if (type == "Medio")
            zShips.push_back(new Medio(id, name));
        else if (type == "Corazzata")
            zShips.push_back(new Corazzata(id, name));
    }

    for (int i = 0; i < rParser.getShipCount(); i++)
    {
        string id = rParser.getShipID(i);
        string type = rParser.getShipType(i);
        string name = rParser.getShipName(i);

        if (type == "Jager")
            rShips.push_back(new Jager(id, name));
        else if (type == "Kreuzer")
            rShips.push_back(new Kreuzer(id, name));
        else if (type == "Fregatte")
            rShips.push_back(new Fregatte(id, name));
    }

    int zPilots = 0, zGunners = 0, zTH = 0;
    int rPilots = 0, rGunners = 0, rTH = 0;

    for (int i = 0; i < zParser.getCrewCount(); i++)
    {
        string role = zParser.getCrewRole(i);
        if (role == "Pilot") zPilots++;
        else if (role == "Gunner") zGunners++;
        else if (role == "TorpedoHandler") zTH++;
    }

    for (int i = 0; i < rParser.getCrewCount(); i++)
    {
        string role = rParser.getCrewRole(i);
        if (role == "Pilot") rPilots++;
        else if (role == "Gunner") rGunners++;
        else if (role == "TorpedoHandler") rTH++;
    }

    CrewAssigner::assignCrewToShips(zShips, zPilots, zGunners, zTH);
    CrewAssigner::assignCrewToShips(rShips, rPilots, rGunners, rTH);

    cout << "\n=== ZAPEZOID FLEET ===\n";
    for (auto s : zShips) cout << *s << endl;

    cout << "\n=== ROGOATUSKAN FLEET ===\n";
    for (auto s : rShips) cout << *s << endl;

    cout << "\n=== SETUP COMPLETE (Battle logic pending) ===\n";

    for (Ship* s : zShips) delete s;
    for (Ship* s : rShips) delete s;

    cout << "Memory cleaned. Program ended.\n";
    return 0;
}
