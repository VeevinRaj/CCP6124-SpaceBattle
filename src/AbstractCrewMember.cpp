// AbstractCrewMember.cpp - Implementation
// Student: [Devraj][243UC247GJ]
#include "../include/AbstractCrewMember.h"
#include "../include/AbstractShip.h"

AbstractCrewMember::AbstractCrewMember(std::string id, std::string name,
                                       std::string role, float efficiency)
    : memberID(id), memberName(name), role(role),
      assignedShip(nullptr), efficiency(efficiency) {
    if (efficiency < 0.0f) this->efficiency = 0.0f;
    if (efficiency > 1.0f) this->efficiency = 1.0f;
}

AbstractCrewMember::~AbstractCrewMember() {
    if (assignedShip != nullptr) {
        assignedShip->removeCrew(this);
    }
}

void AbstractCrewMember::assignToShip(AbstractShip* ship) {
    if (assignedShip != nullptr) {
        assignedShip->removeCrew(this);
    }
    assignedShip = ship;
    if (ship != nullptr) {
        ship->addCrew(this);
    }
}

void AbstractCrewMember::unassignFromShip() {
    if (assignedShip != nullptr) {
        assignedShip->removeCrew(this);
        assignedShip = nullptr;
    }
}

float AbstractCrewMember::getPenalty() const {
    return 1.0f - efficiency;
}

bool AbstractCrewMember::operator==(const AbstractCrewMember& other) const {
    return this->memberID == other.memberID;
}