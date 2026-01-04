#include <iostream>
#include "../include/FileParser.h"

int main()
{
    std::cout << "=== TEST START ===\n";
    FileParser parser("XyloTT9L");
    std::cout << "Team: " << parser.getTeamName() << "\n";
    std::cout << "TG: " << parser.getTutorialGroup() << "\n";
    std::cout << "=== TEST END ===\n";
    return 0;
}