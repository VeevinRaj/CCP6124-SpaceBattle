//  FOMALHAUT TT6L
//  CCP6124 SPACE BATTLE PROJECT (Trimester 2530)
//  Member 4: VRISHAL (Main.cpp & Testing)

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Ship;               
class Weapon;             
class CrewMember;         

vector<Ship*> loadShips(string file);      
vector<CrewMember*> loadCrew(string file); 

void assignCrewToShips(vector<Ship*>& ships, vector<CrewMember*>& crew); 
void startBattle(vector<Ship*>& zShips, vector<Ship*>& rShips);          

ostream& operator<<(ostream& os, const Ship& s);