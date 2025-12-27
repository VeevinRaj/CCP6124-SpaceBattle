#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <string>
#include <vector>

using namespace std;

class FileParser
{
private:
    // Ship data stored in separate vectors (common C++ approach)
    vector<string> shipIDs;
    vector<string> shipTypes;
    vector<string> shipNames;

    // Crew data stored in separate vectors
    vector<string> crewIDs;
    vector<string> crewNames;
    vector<string> crewRoles;

    // Team information
    string teamName;
    string tutorialGroup;

    // Helper function to split CSV lines
    vector<string> splitLine(string line, char delimiter);

    // Helper to determine faction from filename
    string getFactionFromFilename(string filename);

public:
    // Constructor - extracts team name from first argument
    FileParser(string firstArgument);

    // Main parsing functions
    bool parseShipsFile(string filename);
    bool parseCrewFile(string filename);

    // Display functions
    void displayAllShips() const;
    void displayAllCrew() const;

    // Getters for other team members to use
    int getShipCount() const { return shipIDs.size(); }
    string getShipID(int index) const;
    string getShipType(int index) const;
    string getShipName(int index) const;
    string getShipFaction(string filename) const;

    int getCrewCount() const { return crewIDs.size(); }
    string getCrewID(int index) const;
    string getCrewName(int index) const;
    string getCrewRole(int index) const;

    // Team info getters
    string getTeamName() const { return teamName; }
    string getTutorialGroup() const { return tutorialGroup; }

    // Error checking
    bool fileExists(string filename) const;
};

#endif