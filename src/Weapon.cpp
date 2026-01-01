
#include "../include/Weapon.h"
#include "../include/CrewMember.h"

Weapon::Weapon(std::string weaponType, int power)
    : type(weaponType), attackPower(power), assignedCrew(nullptr) {
    // Simple ID generation
    static int counter = 1;
    weaponID = "W" + std::to_string(counter++);
}

Weapon::~Weapon() {
    // Don't delete crew - just a reference
}

void Weapon::assignCrewMember(CrewMember* crew) {
    assignedCrew = crew;
}

bool Weapon::operator>(const Weapon& other) const {
    return this->attackPower > other.attackPower;
}