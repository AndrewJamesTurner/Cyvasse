#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include "HexMap.h"

class PlayerControls
{
    public:
        PlayerControls();
        virtual ~PlayerControls();

        static void player1placement(HexMap* hexmap, int x, int y);


    protected:
    private:
};

#endif // PLAYERCONTROLS_H
