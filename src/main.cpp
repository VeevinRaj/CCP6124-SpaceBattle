//  FOMALHAUT TT6L
//  CCP6124 SPACE BATTLE PROJECT (Trimester 2530)
//  Member 4: VRISHAL (Main.cpp & Integration)

#include <iostream>
#include <vector>
#include <string>

#include "../include/FileParser.h"
#include "../include/Ship.h"
#include "../include/CrewMember.h"
#include "../include/Weapon.h"

using namespace std;

// -----------------------------
// Operator Overloads
// -----------------------------
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

ostream& operator<<(ostream& os, const CrewMember& c) {
    os << c.getName() << " [" << c.getRole() << "]\n";
    return os;
}

ostream& operator<<(ostream& os, const Weapon& w) {
    os << w.getType() << " (Power: " << w.getPower() << ")\n";
    return os;
}

// -----------------------------
// Main
// -----------------------------
int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        cerr << "Usage: " << argv[0]
             << " <ZShips.csv> <ZCrew.csv> <RShips.csv> <RCrew.csv>\n";
        return 1;
    }

    cout << "\n=== FOMALHAUT SPACE BATTLE SIMULATION ===\n";

    // -----------------------------
    // Parse files
    // -----------------------------
    FileParser zParser(argv[1]);
    FileParser rParser(argv[3]);

    if (!zParser.parseShipsFile(argv[1]) || !zParser.parseCrewFile(argv[2]) ||
        !rParser.parseShipsFile(argv[3]) || !rParser.parseCrewFile(argv[4]))
    {
        cerr << "Error parsing input files.\n";
        return 1;
    }

    // -----------------------------
    // Create ships
    // -----------------------------
    vector<Ship*> zShips;
    vector<Ship*> rShips;

    for (int i = 0; i < zParser.getShipCount(); i++) {
        string id = zParser.getShipID(i);
        string type = zParser.getShipType(i);
        string name = zParser.getShipName(i);

        if (type == "Guerriero") zShips.push_back(new Guerriero(id, name));
        else if (type == "Medio") zShips.push_back(new Medio(id, name));
        else if (type == "Corazzata") zShips.push_back(new Corazzata(id, name));
    }

    for (int i = 0; i < rParser.getShipCount(); i++) {
        string id = rParser.getShipID(i);
        string type = rParser.getShipType(i);
        string name = rParser.getShipName(i);

        if (type == "Jager") rShips.push_back(new Jager(id, name));
        else if (type == "Kreuzer") rShips.push_back(new Kreuzer(id, name));
        else if (type == "Fregatte") rShips.push_back(new Fregatte(id, name));
    }

    // -----------------------------
    // Create crew dynamically
    // -----------------------------
    vector<CrewMember*> zCrew;
    vector<CrewMember*> rCrew;

    for (int i = 0; i < zParser.getCrewCount(); i++) {
        zCrew.push_back(new CrewMember(zParser.getCrewName(i), zParser.getCrewRole(i)));
    }

    for (int i = 0; i < rParser.getCrewCount(); i++) {
        rCrew.push_back(new CrewMember(rParser.getCrewName(i), rParser.getCrewRole(i)));
    }

    // -----------------------------
    // Count crew roles
    // -----------------------------
    int zPilots = 0, zGunners = 0, zTH = 0;
    int rPilots = 0, rGunners = 0, rTH = 0;

    for (CrewMember* c : zCrew) {
        if (c->getRole() == "Pilot") zPilots++;
        else if (c->getRole() == "Gunner") zGunners++;
        else if (c->getRole() == "TorpedoHandler") zTH++;
    }

    for (CrewMember* c : rCrew) {
        if (c->getRole() == "Pilot") rPilots++;
        else if (c->getRole() == "Gunner") rGunners++;
        else if (c->getRole() == "TorpedoHandler") rTH++;
    }

    // -----------------------------
    // Assign crew to ships
    // -----------------------------
    CrewAssigner::assignCrewToShips(zShips, zPilots, zGunners, zTH);
    CrewAssigner::assignCrewToShips(rShips, rPilots, rGunners, rTH);

    // -----------------------------
    // Create weapons dynamically and assign to ships
    // -----------------------------
    vector<Weapon*> zWeapons;
    vector<Weapon*> rWeapons;

    for (Ship* s : zShips) {
        Weapon* w = new Weapon("LightCannon", s->getLightCannonPower());
        s->addWeapon(w);
        zWeapons.push_back(w);
    }

    for (Ship* s : rShips) {
        Weapon* w = new Weapon("LightCannon", s->getLightCannonPower());
        s->addWeapon(w);
        rWeapons.push_back(w);
    }

    // -----------------------------
    // Print fleets
    // -----------------------------
    cout << "\n=== ZAPEZOID FLEET ===\n";
    for (Ship* s : zShips) cout << *s << endl;

    cout << "\n=== ROGOATUSKAN FLEET ===\n";
    for (Ship* s : rShips) cout << *s << endl;

    cout << "\n=== CREW ===\n";
    cout << "--- ZAPEZOID CREW ---\n";
    for (CrewMember* c : zCrew) cout << *c;
    cout << "--- ROGOATUSKAN CREW ---\n";
    for (CrewMember* c : rCrew) cout << *c;

    cout << "\n=== WEAPONS ===\n";
    cout << "--- ZAPEZOID WEAPONS ---\n";
    for (Weapon* w : zWeapons) cout << *w;
    cout << "--- ROGOATUSKAN WEAPONS ---\n";
    for (Weapon* w : rWeapons) cout << *w;

    cout << "\n=== SETUP COMPLETE (Battle logic pending) ===\n";

    // -----------------------------
    // Cleanup
    // -----------------------------
    for (Ship* s : zShips) delete s;
    for (Ship* s : rShips) delete s;

    for (CrewMember* c : zCrew) delete c;
    for (CrewMember* c : rCrew) delete c;

    for (Weapon* w : zWeapons) delete w;
    for (Weapon* w : rWeapons) delete w;

    cout << "Memory cleaned. Program ended.\n";
    return 0;
}