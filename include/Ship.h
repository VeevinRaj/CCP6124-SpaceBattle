#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <vector>

class Ship
{
private:
    std::string id;
    std::string name;
    int hitPoints;
    int maxHitPoints;
    int pilotsNeeded;
    int gunnersNeeded;
    int torpedoHandlersNeeded;
    int pilotsAssigned;
    int gunnersAssigned;
    int torpedoHandlersAssigned;
    int lightCannonPower;
    int torpedoPower;
    int lightCannonCount;
    int torpedoCount;
    double lightCannonHitChance;
    double torpedoHitChance;
    bool isZapezoid;

public:
    Ship(std::string id, std::string name, int hp,
         int pilots, int gunners, int torpedoHandlers,
         int lcPower, int tpPower, int lcCount, int tpCount,
         double lcHitChance, double tpHitChance, bool isZap);

    virtual ~Ship() = default;

    virtual std::string getFaction() const = 0;
    virtual std::string getType() const = 0;

    bool isDestroyed() const;
    void takeDamage(int damage);
    void assignCrew(int pilots, int gunners, int torpedoHandlers);
    bool canFight() const;

    double getAdjustedLightCannonHitChance() const;
    double getAdjustedTorpedoHitChance() const;

    int getHitPoints() const;
    int getMaxHitPoints() const;
    int getLightCannonPower() const;
    int getTorpedoPower() const;
    int getLightCannonCount() const;
    int getTorpedoCount() const;
    int getPilotsAssigned() const;
    int getGunnersAssigned() const;
    int getTorpedoHandlersAssigned() const;
    int getPilotsNeeded() const;
    int getGunnersNeeded() const;
    int getTorpedoHandlersNeeded() const;
    std::string getId() const;
    std::string getName() const;
    bool isFactionZapezoid() const;

    int getEffectiveLightCannons() const;
    int getEffectiveTorpedoes() const;

    void reset();
};

class ZapezoidShip : public Ship
{
protected:
    ZapezoidShip(std::string id, std::string name, int hp,
                 int pilots, int gunners, int torpedoHandlers,
                 int lcPower, int tpPower, int lcCount, int tpCount,
                 double lcHitChance, double tpHitChance);

public:
    std::string getFaction() const override;
};

class Guerriero : public ZapezoidShip
{
public:
    Guerriero(std::string id, std::string name);
    std::string getType() const override;
};

class Medio : public ZapezoidShip
{
public:
    Medio(std::string id, std::string name);
    std::string getType() const override;
};

class Corazzata : public ZapezoidShip
{
public:
    Corazzata(std::string id, std::string name);
    std::string getType() const override;
};

class RogoatuskanShip : public Ship
{
protected:
    RogoatuskanShip(std::string id, std::string name, int hp,
                    int pilots, int gunners, int torpedoHandlers,
                    int lcPower, int tpPower, int lcCount, int tpCount,
                    double lcHitChance, double tpHitChance);

public:
    std::string getFaction() const override;
};

class Jager : public RogoatuskanShip
{
public:
    Jager(std::string id, std::string name);
    std::string getType() const override;
};

class Kreuzer : public RogoatuskanShip
{
public:
    Kreuzer(std::string id, std::string name);
    std::string getType() const override;
};

class Fregatte : public RogoatuskanShip
{
public:
    Fregatte(std::string id, std::string name);
    std::string getType() const override;
};

#endif