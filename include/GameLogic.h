#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Hex.h"
#include "HexMap.h"

#include <SFML/Graphics.hpp>
#include <random>

class GameLogic
{
    public:
        GameLogic(sf::RenderWindow *_window, float _hexSize, int _mapHexSize);
        virtual ~GameLogic();

        void update(void);

        void mapClicked(int xPixel, int yPixel);

        int getX(int pixelX, int pixelY);
        int getY(int pixelX, int pixelY);

        void changeColour(int row, int col);
        void changeColour(int x, int y, int z);
        void changeColour(int x, int y, int red, int greed, int blue);
        void changeColour(int x, int y, int z, int red, int greed, int blue);

        void moveOrthogonal(int row, int col, int range);
        void moveDiagonal(int row, int col, int range);
        void moveAny(int row, int col, int range);

        void enemyMove(void);

        bool inRangeAny(int row1, int col1, int row2, int col2, int range);
        bool inRangeAny(int x1, int y1, int z1, int x2, int y2, int z2, int range);

        void resetMap(void);
        void deselect(void);

    protected:

    private:

        sf::RenderWindow *window;
        HexMap* hexMap;
        Hex* selectedHex;

        float hexSize;
        float hexHeight;
        float hexWidth;

        int width;
        int height;
        int mapHexSize;

        std::random_device rd;

        bool outOfBounds(int x, int y);
        void movePiece(Hex* sourceHex, Hex* targetHex);
        bool canMove(Hex* sourceHex, Hex* targetHex);
        void showMovements(Hex* hex);
        void populateBoard(void);
};

#endif // GAMELOGIC_H
