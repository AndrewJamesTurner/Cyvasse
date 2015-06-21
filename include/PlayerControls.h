#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include "HexMap.h"
#include "Movement.h"

class PlayerControls
{
    public:
        PlayerControls();
        virtual ~PlayerControls();

        static void playerPlacement(HexMap* hexmap, Player player, int x, int y);

        static bool playerMove(HexMap* hexmap, Player player, int x, int y);

        static void showMovements(HexMap* hexmap, Hex hex);

        static bool movePiece(HexMap* hexmap, Hex sourceHex, Hex destinationHex);




    protected:
    private:
};

#endif // PLAYERCONTROLS_H
