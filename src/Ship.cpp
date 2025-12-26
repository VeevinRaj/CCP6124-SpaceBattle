#include "Ship.h"
#include <algorithm>
#include <string>

Ship::Ship(std::string id, std::string name, int hp,
           int pilots, int gunners, int torpedoHandlers,
           int lcPower, int tpPower, int lcCount, int tpCount,
           double lcHitChance, double tpHitChance, bool isZap)

    : id(id), name(name), hitPoints(hp), maxHitPoints(hp),
      pilotsNeeded(pilots), gunnersNeeded(gunners),
      torpedoHandlersNeeded(torpedoHandlers),
      pilotsAssigned(0), gunnersAssigned(0), torpedoHandlersAssigned(0),
      lightCannonPower(lcPower), torpedoPower(tpPower),
      lightCannonCount(lcCount), torpedoCount(tpCount),
      lightCannonHitChance(lcHitChance), torpedoHitChance(tpHitChance),
      isZapezoid(isZap)
{
}

bool Ship::isDestroyed() const
{
    return hitPoints <= 0;
}
void Ship::takeDamage(int damage)
{
    hitPoints -= damage;
    if (hitPoints < 0)
        hitPoints = 0;
}

void Ship::assignCrew(int pilots, int gunners, int torpedoHandlers)
{
    pilotsAssigned += pilots;
    gunnersAssigned += gunners;
    torpedoHandlersAssigned += torpedoHandlers;

    if (pilotsAssigned > pilotsNeeded)
        pilotsAssigned = pilotsNeeded;
    if (gunnersAssigned > gunnersNeeded)
        gunnersAssigned = gunnersNeeded;
    if (torpedoHandlersAssigned > torpedoHandlersNeeded)
        torpedoHandlersAssigned = torpedoHandlersNeeded;
}

bool Ship::canFight() const
{
    return pilotsAssigned >= 1 && !isDestroyed();
}

double Ship::getAdjustedLightCannonHitChance() const
{
    double penalty = 1.0;
    if (pilotsNeeded == 2 && pilotsAssigned == 1)
    {
        penalty = 1.25;
    }
    return lightCannonHitChance * penalty;
}

double Ship::getAdjustedTorpedoHitChance() const
{
    double penalty = 1.0;
    if (pilotsNeeded == 2 && pilotsAssigned == 1)
    {
        penalty = 1.25;
    }
    return torpedoHitChance * penalty;
}

int Ship::getHitPoints() const { return hitPoints; }
int Ship::getMaxHitPoints() const { return maxHitPoints; }
int Ship::getLightCannonPower() const { return lightCannonPower; }
int Ship::getTorpedoPower() const { return torpedoPower; }
int Ship::getLightCannonCount() const { return lightCannonCount; }
int Ship::getTorpedoCount() const { return torpedoCount; }
int Ship::getPilotsAssigned() const { return pilotsAssigned; }
int Ship::getGunnersAssigned() const { return gunnersAssigned; }
int Ship::getTorpedoHandlersAssigned() const { return torpedoHandlersAssigned; }
int Ship::getPilotsNeeded() const { return pilotsNeeded; }
int Ship::getGunnersNeeded() const { return gunnersNeeded; }
int Ship::getTorpedoHandlersNeeded() const { return torpedoHandlersNeeded; }
std::string Ship::getId() const { return id; }
std::string Ship::getName() const { return name; }
bool Ship::isFactionZapezoid() const { return isZapezoid; }

int Ship::getEffectiveLightCannons() const
{
    return std::min(gunnersAssigned, lightCannonCount);
}

int Ship::getEffectiveTorpedoes() const
{
    return std::min(torpedoHandlersAssigned, torpedoCount);
}

void Ship::reset()
{
    hitPoints = maxHitPoints;
}

ZapezoidShip::ZapezoidShip(std::string id, std::string name, int hp,
                           int pilots, int gunners, int torpedoHandlers,
                           int lcPower, int tpPower, int lcCount, int tpCount,
                           double lcHitChance, double tpHitChance)
    : Ship(id, name, hp, pilots, gunners, torpedoHandlers,
           lcPower, tpPower, lcCount, tpCount,
           lcHitChance, tpHitChance, true) {}

std::string ZapezoidShip::getFaction() const
{
    return "Zapezoid";
}

Guerriero::Guerriero(std::string id, std::string name)
    : ZapezoidShip(id, name,
                   123,
                   1,
                   1,
                   0,
                   96,
                   0,
                   1,
                   0,
                   0.26,
                   0.06) {}

std::string Guerriero::getType() const
{
    return "Guerriero";
}

Medio::Medio(std::string id, std::string name)
    : ZapezoidShip(id, name,
                   214,
                   1,
                   2,
                   0,
                   134,
                   0,
                   2,
                   0,
                   0.31,
                   0.11) {}

std::string Medio::getType() const
{
    return "Medio";
}

Corazzata::Corazzata(std::string id, std::string name)
    : ZapezoidShip(id, name,
                   1031,
                   2,
                   10,
                   4,
                   164,
                   293,
                   10,
                   4,
                   0.50,
                   0.25) {}

std::string Corazzata::getType() const
{
    return "Corazzata";
}

RogoatuskanShip::RogoatuskanShip(std::string id, std::string name, int hp,
                                 int pilots, int gunners, int torpedoHandlers,
                                 int lcPower, int tpPower, int lcCount, int tpCount,
                                 double lcHitChance, double tpHitChance)
    : Ship(id, name, hp, pilots, gunners, torpedoHandlers,
           lcPower, tpPower, lcCount, tpCount,
           lcHitChance, tpHitChance, false) {}

std::string RogoatuskanShip::getFaction() const
{
    return "Rogoatuskan";
}

Jager::Jager(std::string id, std::string name)
    : RogoatuskanShip(id, name,
                      112,
                      1,
                      1,
                      0,
                      101,
                      0,
                      1,
                      0,
                      0.24,
                      0.05) {}

std::string Jager::getType() const
{
    return "Jager";
}

Kreuzer::Kreuzer(std::string id, std::string name)
    : RogoatuskanShip(id, name,
                      212,
                      1,
                      2,
                      0,
                      132,
                      0,
                      2,
                      0,
                      0.29,
                      0.10) {}

std::string Kreuzer::getType() const
{
    return "Kreuzer";
}

Fregatte::Fregatte(std::string id, std::string name)
    : RogoatuskanShip(id, name,
                      1143,
                      2,
                      11,
                      5,
                      159,
                      282,
                      11,
                      5,
                      0.60,
                      0.30) {}

std::string Fregatte::getType() const
{
    return "Fregatte";
}