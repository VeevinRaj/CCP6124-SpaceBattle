
#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class CrewMember;

class Weapon {
protected:
    std::string weaponID;
    std::string type;
    int attackPower;
    CrewMember* assignedCrew;

public:
    Weapon(std::string weaponType, int power);
    virtual ~Weapon();
    
    // Pure virtual
    virtual bool canShoot() = 0;
    
    // Concrete methods
    void assignCrewMember(CrewMember* crew);
    CrewMember* getAssignedCrew() const { return assignedCrew; }
    int getPower() const { return attackPower; }
    std::string getType() const { return type; }
    
    // Operator
    bool operator>(const Weapon& other) const;
};

#endif