// AbstractShip.cpp - Implementation
// Student: [Devraj], ID: [243UC247GJ]
#include "../include/AbstractShip.h"
#include "../include/Weapon.h"
#include "../include/AbstractCrewMember.h"
#include <algorithm>

AbstractShip::AbstractShip(std::string id, std::string shipName, int hp,
                           int pilots, int gunners, int handlers,
                           float lightEvade, float torpedoEvade)
    : shipID(id), name(shipName), currentHP(hp), maxHP(hp),
      pilotsNeeded(pilots), gunnersNeeded(gunners),
      torpedoHandlersNeeded(handlers),
      lightCannonEvasion(lightEvade), torpedoEvasion(torpedoEvade),
      isDestroyedFlag(false) {
    pilotCount = gunnerCount = torpedoHandlerCount = 0;
}

AbstractShip::~AbstractShip() {
    for (Weapon* w : weapons) {
        delete w;
    }
}

void AbstractShip::addCrew(AbstractCrewMember* crewMember) {
    if (crewMember != nullptr) {
        crew.push_back(crewMember);
        updateCrewCounts();
    }
}

void AbstractShip::removeCrew(AbstractCrewMember* crewMember) {
    auto it = std::find(crew.begin(), crew.end(), crewMember);
    if (it != crew.end()) {
        crew.erase(it);
        updateCrewCounts();
    }
}

bool AbstractShip::isOperational() const {
    return (pilotCount > 0) && !isDestroyedFlag;
}

bool AbstractShip::operator==(const AbstractShip& other) const {
    return this->shipID == other.shipID;
}

void AbstractShip::updateCrewCounts() {
    pilotCount = gunnerCount = torpedoHandlerCount = 0;
    
    for (AbstractCrewMember* member : crew) {
        std::string role = member->getRole();
        if (role == "Pilot") {
            pilotCount++;
        } else if (role == "Gunner") {
            gunnerCount++;
        } else if (role == "TorpedoHandler") {
            torpedoHandlerCount++;
        }
    }
}