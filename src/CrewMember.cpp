#include "CrewMember.h"
#include "Ship.h"
#include <iostream>
#include <algorithm>

void CrewAssigner::assignCrewToShips(std::vector<Ship *> &ships,
                                     int availablePilots,
                                     int availableGunners,
                                     int availableTorpedoHandlers)
{

    std::cout << "=== CREW ASSIGNMENT ===" << std::endl;
    std::cout << "Available: " << availablePilots << " pilots, "
              << availableGunners << " gunners, "
              << availableTorpedoHandlers << " torpedo handlers" << std::endl;
    std::cout << "Number of ships: " << ships.size() << std::endl;

    for (Ship *ship : ships)
    {
        ship->assignCrew(-ship->getPilotsAssigned(),
                         -ship->getGunnersAssigned(),
                         -ship->getTorpedoHandlersAssigned());
    }

    int pilots = availablePilots;
    assignRole(ships, pilots, "pilots");

    int gunners = availableGunners;
    assignRole(ships, gunners, "gunners");

    int torpedoHandlers = availableTorpedoHandlers;
    assignRole(ships, torpedoHandlers, "torpedo handlers");

    displayShipStatus(ships);
}

void CrewAssigner::assignRole(std::vector<Ship *> &ships,
                              int &availableCount,
                              const std::string &roleName)
{

    bool assignedAny;
    do
    {
        assignedAny = false;

        for (Ship *ship : ships)
        {
            if (availableCount <= 0)
                break;

            bool needsCrew = false;
            int current = 0, needed = 0;

            if (roleName == "pilots")
            {
                current = ship->getPilotsAssigned();
                needed = ship->getPilotsNeeded();
                needsCrew = (current < needed);
            }
            else if (roleName == "gunners")
            {
                current = ship->getGunnersAssigned();
                needed = ship->getGunnersNeeded();
                needsCrew = (current < needed);
            }
            else if (roleName == "torpedo handlers")
            {
                current = ship->getTorpedoHandlersAssigned();
                needed = ship->getTorpedoHandlersNeeded();
                needsCrew = (current < needed);
            }

            if (needsCrew)
            {
                if (roleName == "pilots")
                {
                    ship->assignCrew(1, 0, 0);
                }
                else if (roleName == "gunners")
                {
                    ship->assignCrew(0, 1, 0);
                }
                else if (roleName == "torpedo handlers")
                {
                    ship->assignCrew(0, 0, 1);
                }
                availableCount--;
                assignedAny = true;
                break;
            }
        }
    } while (assignedAny && availableCount > 0);

    std::cout << "Assigned " << roleName << ". Remaining: " << availableCount << std::endl;
}

void CrewAssigner::displayShipStatus(const std::vector<Ship *> &ships)
{
    std::cout << "\n=== SHIP STATUS AFTER CREW ASSIGNMENT ===" << std::endl;

    int readyShips = 0;
    int underCrewedShips = 0;

    for (Ship *ship : ships)
    {
        bool ready = ship->canFight();
        bool underCrewed = (ship->getPilotsNeeded() == 2 && ship->getPilotsAssigned() == 1);

        std::cout << ship->getId() << " - " << ship->getName()
                  << " [" << ship->getFaction() << " " << ship->getType() << "]" << std::endl
                  << "  Pilots: " << ship->getPilotsAssigned() << "/" << ship->getPilotsNeeded()
                  << ", Gunners: " << ship->getGunnersAssigned() << "/" << ship->getGunnersNeeded()
                  << ", TH: " << ship->getTorpedoHandlersAssigned() << "/" << ship->getTorpedoHandlersNeeded() << std::endl
                  << "  Weapons: " << ship->getEffectiveLightCannons() << "/" << ship->getLightCannonCount()
                  << " light cannons, " << ship->getEffectiveTorpedoes() << "/" << ship->getTorpedoCount() << " torpedoes" << std::endl
                  << "  Status: " << (ready ? "READY" : "NOT READY");

        if (underCrewed)
        {
            std::cout << " [UNDER-CREWED: +25% hit chance penalty]";
            underCrewedShips++;
        }

        if (ready)
            readyShips++;

        std::cout << std::endl
                  << std::endl;
    }

    std::cout << "=== SUMMARY ===" << std::endl;
    std::cout << "Ready ships: " << readyShips << "/" << ships.size() << std::endl;
    std::cout << "Under-crewed ships: " << underCrewedShips << std::endl;
    std::cout << "=== END CREW ASSIGNMENT ===\n"
              << std::endl;
}