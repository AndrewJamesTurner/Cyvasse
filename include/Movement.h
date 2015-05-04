#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "HexMap.h"

struct Move{

  int startX;
  int startY;

  int endX;
  int endY;

  Move(int _startX, int _startY, int _endX, int _endY) : startX(_startX), startY(_startY), endX{_endX}, endY{_endY}{}
};

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
};

#endif // MOVEMENT_H
