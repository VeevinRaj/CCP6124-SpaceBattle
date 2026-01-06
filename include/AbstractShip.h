// AbstractShip.h - Abstract base class for spaceships
// Student: [Devraj], ID: [243UC247GJ]
#ifndef ABSTRACTSHIP_H
#define ABSTRACTSHIP_H

#include <string>
#include <vector>

class Weapon;
class AbstractCrewMember;

class AbstractShip {
protected:
    std::string shipID;
    std::string name;
    int currentHP;
    int maxHP;
    
    int pilotsNeeded;
    int gunnersNeeded;
    int torpedoHandlersNeeded;
    
    int pilotCount;
    int gunnerCount;
    int torpedoHandlerCount;
    
    float lightCannonEvasion;
    float torpedoEvasion;
    
    std::vector<Weapon*> weapons;
    std::vector<AbstractCrewMember*> crew;
    
    bool isDestroyedFlag;

public:
    AbstractShip(std::string id, std::string shipName, int hp,
                 int pilots, int gunners, int handlers,
                 float lightEvade, float torpedoEvade);
    
    virtual ~AbstractShip();
    
    virtual void takeDamage(int damage) = 0;
    virtual bool canFire() = 0;
    virtual void attack(AbstractShip* target) = 0;
    virtual float calculatePenalty() = 0;
    
    void addCrew(AbstractCrewMember* crewMember);
    void removeCrew(AbstractCrewMember* crewMember);
    bool isOperational() const;
    
    std::string getID() const { return shipID; }
    std::string getName() const { return name; }
    int getHP() const { return currentHP; }
    bool isDestroyed() const { return isDestroyedFlag; }
    float getLightEvasion() const { return lightCannonEvasion; }
    float getTorpedoEvasion() const { return torpedoEvasion; }
    
    int getPilotCount() const { return pilotCount; }
    int getGunnerCount() const { return gunnerCount; }
    int getTorpedoHandlerCount() const { return torpedoHandlerCount; }
    
    bool operator==(const AbstractShip& other) const;
    
private:
    void updateCrewCounts();
};

#endif