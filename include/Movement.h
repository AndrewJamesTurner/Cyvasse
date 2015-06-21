#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <algorithm>
#include <random>

#include "HexMap.h"

class Movement
{
    public:
        Movement();
        virtual ~Movement();
        static std::vector<Hex> getPossibleMovements(const HexMap& _hexMap, const Hex& hex);
        static std::vector<Hex> getValidMovements(const HexMap& _hexMap, const Hex& hex);
        static std::vector<Move> getPossibleMoves(const HexMap& _hexMap, const Player& player);
        static bool canMove(HexMap _hexmap, Hex sourceHex, Hex targetHex);
    protected:


    private:

        static std::default_random_engine engine;
        static int isOnTerrainBonus(const Hex hex);

};

#endif // MOVEMENT_H
