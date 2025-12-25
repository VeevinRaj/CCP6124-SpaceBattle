// =============================================================
//  FOMALHAUT TT6L
//  CCP6124 SPACE BATTLE PROJECT (Trimester 2530)
//  Member 4: YOU (Main.cpp, Operator Overloading, Memory Mgmt & Testing)
//
//  This file is the MAIN CONTROLLER that connects all modules.
//  It will be compiled using:
//      g++ FomalhautTT6L.cpp -o FomalhautTT6L
// =============================================================

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// =============================
//   Forward declarations
//   (Actual class definitions implemented by Members 1 & 2)
// =============================
class Ship;               // Base abstract ship class (Member 1)
class Weapon;             // Abstract weapon (Member 1)
class CrewMember;         // Abstract crew member (Member 1)

vector<Ship*> loadShips(string file);      // Member 3 implements
vector<CrewMember*> loadCrew(string file); // Member 3 implements