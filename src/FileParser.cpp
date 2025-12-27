#include "../include/FileParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

FileParser::FileParser(string firstArgument)
{
    teamName = "";
    tutorialGroup = "";

    if (firstArgument.length() >= 4)
    {
        teamName = firstArgument.substr(0, firstArgument.length() - 4);
        tutorialGroup = firstArgument.substr(firstArgument.length() - 4);
    }
    else
    {
        teamName = firstArgument;
        tutorialGroup = "NONE";
    }

    shipIDs.clear();
    shipTypes.clear();
    shipNames.clear();
    crewIDs.clear();
    crewNames.clear();
    crewRoles.clear();
}

vector<string> FileParser::splitLine(string line, char delimiter)
{
    vector<string> result;
    stringstream ss(line);
    string item;

    while (getline(ss, item, delimiter))
    {
        while (!item.empty() && (item[0] == ' ' || item[0] == '\t'))
        {
            item.erase(0, 1);
        }
        while (!item.empty() && (item.back() == ' ' || item.back() == '\t'))
        {
            item.pop_back();
        }
        result.push_back(item);
    }

    return result;
}

bool FileParser::parseShipsFile(string filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "ERROR: Cannot open ships file: " << filename << endl;
        return false;
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line))
    {
        lineNumber++;
        if (line.empty())
            continue;

        vector<string> parts = splitLine(line, ',');

        if (parts.size() >= 3)
        {
            shipIDs.push_back(parts[0]);
            shipTypes.push_back(parts[1]);
            shipNames.push_back(parts[2]);
        }
        else
        {
            cout << "WARNING: Line " << lineNumber
                 << " has invalid format: " << line << endl;
        }
    }

    file.close();
    cout << "Successfully parsed " << shipIDs.size()
         << " ships from " << filename << endl;
    return true;
}

bool FileParser::parseCrewFile(string filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "ERROR: Cannot open crew file: " << filename << endl;
        return false;
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line))
    {
        lineNumber++;
        if (line.empty())
            continue;

        vector<string> parts = splitLine(line, ',');

        if (parts.size() >= 3)
        {
            crewIDs.push_back(parts[0]);
            crewNames.push_back(parts[1]);
            crewRoles.push_back(parts[2]);
        }
    }

    file.close();
    cout << "Successfully parsed " << crewIDs.size()
         << " crew members from " << filename << endl;
    return true;
}

string FileParser::getFactionFromFilename(string filename) const
{
    string lowerFilename = filename;
    transform(lowerFilename.begin(), lowerFilename.end(), lowerFilename.begin(),
              [](unsigned char c)
              { return tolower(c); });

    if (lowerFilename.find("zships") != string::npos ||
        lowerFilename.find("zcrew") != string::npos)
    {
        return "ZAPEZOID";
    }

    if (lowerFilename.find("rships") != string::npos ||
        lowerFilename.find("rcrew") != string::npos)
    {
        return "ROGOATUSKAN";
    }

    return "UNKNOWN";
}

void FileParser::displayAllShips() const
{
    cout << "\n=== SHIPS LIST ===" << endl;
    cout << "Total ships: " << shipIDs.size() << endl;
    cout << "-------------------" << endl;

    for (int i = 0; i < shipIDs.size(); i++)
    {
        cout << i + 1 << ". ";
        cout << "ID: " << shipIDs[i] << " | ";
        cout << "Type: " << shipTypes[i] << " | ";
        cout << "Name: " << shipNames[i] << endl;
    }
    cout << endl;
}

void FileParser::displayAllCrew() const
{
    cout << "\n=== CREW LIST ===" << endl;
    cout << "Total crew: " << crewIDs.size() << endl;
    cout << "-----------------" << endl;

    for (int i = 0; i < crewIDs.size(); i++)
    {
        cout << i + 1 << ". ";
        cout << "ID: " << crewIDs[i] << " | ";
        cout << "Name: " << crewNames[i] << " | ";
        cout << "Role: " << crewRoles[i] << endl;
    }
    cout << endl;
}

string FileParser::getShipID(int index) const
{
    if (index >= 0 && index < shipIDs.size())
        return shipIDs[index];
    return "INVALID_INDEX";
}

string FileParser::getShipType(int index) const
{
    if (index >= 0 && index < shipTypes.size())
        return shipTypes[index];
    return "INVALID_INDEX";
}

string FileParser::getShipName(int index) const
{
    if (index >= 0 && index < shipNames.size())
        return shipNames[index];
    return "INVALID_INDEX";
}

string FileParser::getShipFaction(string filename) const
{
    return getFactionFromFilename(filename);
}

string FileParser::getCrewID(int index) const
{
    if (index >= 0 && index < crewIDs.size())
        return crewIDs[index];
    return "INVALID_INDEX";
}

string FileParser::getCrewName(int index) const
{
    if (index >= 0 && index < crewNames.size())
        return crewNames[index];
    return "INVALID_INDEX";
}

string FileParser::getCrewRole(int index) const
{
    if (index >= 0 && index < crewRoles.size())
        return crewRoles[index];
    return "INVALID_INDEX";
}

bool FileParser::fileExists(string filename) const
{
    ifstream file(filename);
    bool exists = file.good();
    file.close();
    return exists;
}