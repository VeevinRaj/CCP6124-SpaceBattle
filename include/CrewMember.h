#ifndef CREWMEMBER_H
#define CREWMEMBER_H

#include <vector>
#include <iostream>
#include <string>

class Ship;

class CrewAssigner
{
public:
    static void assignCrewToShips(std::vector<Ship *> &ships,
                                  int availablePilots,
                                  int availableGunners,
                                  int availableTorpedoHandlers);

    static void displayShipStatus(const std::vector<Ship *> &ships);

private:
    static void assignRole(std::vector<Ship *> &ships,
                           int &availableCount,
                           const std::string &roleName);
};

#endif