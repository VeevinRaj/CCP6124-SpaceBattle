# Fomalhaut TT6L - Space Battle

## Project Structure

- src/ → cpp implementation files
- include/ → header files
- data/ → csv input files
- docs/ → UML diagrams, reports
- test/ → testing files

## How to compile

g++ src/*.cpp -I include -o FomalhautTT6L
./FomalhautTT6L <zShips.csv> <zCrew.csv> <rShips.csv> <rCrew.csv>
