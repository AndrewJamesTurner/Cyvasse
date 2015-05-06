#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Hex.h"
#include "HexMap.h"
#include "Movement.h"
#include "AI.h"

#include <random>
#include <vector>
#include <climits>

class GameLogic
{
    public:
        GameLogic(int _mapHexSize);
        virtual ~GameLogic();

        GameState getGameState(void);
        void enemyMove(void);

        void mapClicked(int x, int y);

        void deselect(void);
        void resetMap(void);
        void endPlacement(void);

        HexMap getHexMap() const;

    protected:

    private:

        HexMap hexMap;
        GameState gameState;

        std::random_device rd;

        void player1placement(int x, int y);
        void player1Move(int x, int y);

        int getX(int pixelX, int pixelY);
        int getY(int pixelX, int pixelY);

        bool playerMove(Hex sourceHex, Hex destinationHex);

        void showMovements(Hex hex);
};

#endif // GAMELOGIC_H
