// AbstractCrewMember.h - Abstract base for crew
// Student: [Devraj], ID: [243UC247GJ]
#ifndef ABSTRACTCREWMEMBER_H
#define ABSTRACTCREWMEMBER_H

#include <string>

class AbstractShip;

class AbstractCrewMember {
protected:
    std::string memberID;
    std::string memberName;
    std::string role;
    AbstractShip* assignedShip;
    float efficiency;

public:
    AbstractCrewMember(std::string id, std::string name,
                       std::string role, float efficiency = 1.0f);
    virtual ~AbstractCrewMember();
    
    virtual void performDuty() = 0;
    
    void assignToShip(AbstractShip* ship);
    void unassignFromShip();
    
    std::string getID() const { return memberID; }
    std::string getName() const { return memberName; }
    std::string getRole() const { return role; }
    AbstractShip* getAssignedShip() const { return assignedShip; }
    float getEfficiency() const { return efficiency; }
    
    float getPenalty() const;
    
    bool operator==(const AbstractCrewMember& other) const;
};

#endif