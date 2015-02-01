#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Hex.h"
#include "Pieces.h"
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

        bool inRangeAny(int row1, int col1, int row2, int col2, int range);
        bool inRangeAny(int x1, int y1, int z1, int x2, int y2, int z2, int range);

        void clearMap(void);
        void deselect(void);

    protected:

    private:

    sf::RenderWindow *window;

    //std::vector<sf::CircleShape> hex;
    std::vector<Hex> hexes;

    //Pieces pieces;

    float hexSize;
    float hexHeight;
    float hexWidth;

    int width;
    int height;
    int mapHexSize;

    std::random_device rd;

    bool outOfBounds(int x, int y);
    //bool outOfBounds(int x, int y, int z);

    int getIndex(int x, int y);

    Hex* selectedHex;

    bool movePiece(Hex* sourceHex, Hex* targetHex);
    void showMovements(Hex* hex);

    HexMap *hexMap;

};

#endif // GAMELOGIC_H
