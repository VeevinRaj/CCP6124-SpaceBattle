#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <string>
#include <vector>

using namespace std;

class FileParser
{
private:
    vector<string> shipIDs;
    vector<string> shipTypes;
    vector<string> shipNames;

    vector<string> crewIDs;
    vector<string> crewNames;
    vector<string> crewRoles;

    string teamName;
    string tutorialGroup;

    vector<string> splitLine(string line, char delimiter);
    string getFactionFromFilename(string filename) const; // ADDED const here

public:
    FileParser(string firstArgument);

    bool parseShipsFile(string filename);
    bool parseCrewFile(string filename);

    void displayAllShips() const;
    void displayAllCrew() const;

    int getShipCount() const { return shipIDs.size(); }
    string getShipID(int index) const;
    string getShipType(int index) const;
    string getShipName(int index) const;
    string getShipFaction(string filename) const;

    int getCrewCount() const { return crewIDs.size(); }
    string getCrewID(int index) const;
    string getCrewName(int index) const;
    string getCrewRole(int index) const;

    string getTeamName() const { return teamName; }
    string getTutorialGroup() const { return tutorialGroup; }

    bool fileExists(string filename) const;
};

#endif