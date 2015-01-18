#ifndef HEXMAP_H
#define HEXMAP_H

#include "Hex.h"
#include <SFML/Graphics.hpp>
#include <random>

class HexMap
{
    public:
        HexMap(sf::RenderWindow *_window, float _hexSize, int _nrows, int _ncols);
        HexMap(sf::RenderWindow *_window, float _hexSize, int _mapHexSize);
        virtual ~HexMap();

        void update(void);

        int getRow(int x, int y);
        int getCol(int x, int y);

        int getXpos(int row, int col);
        int getYpos(int row, int col);

        int getCubeX(int x, int y);
        int getCubeY(int x, int y);
        int getCubeZ(int x, int y);

        void changeColour(int row, int col);
        void changeColour(int x, int y, int z);
        void changeColour(int row, int col, int red, int greed, int blue);
        void changeColour(int x, int y, int z, int red, int greed, int blue);

        void moveOrthogonal(int row, int col, int range);
        void moveDiagonal(int row, int col, int range);
        void moveAny(int row, int col, int range);

        bool inRangeAny(int row1, int col1, int row2, int col2, int range);
        bool inRangeAny(int x1, int y1, int z1, int x2, int y2, int z2, int range);

    protected:

    private:

    sf::RenderWindow *window;

    //std::vector<sf::CircleShape> hex;
    std::vector<Hex> hex;

    float hexSize;
    float hexHeight;
    float hexWidth;

    int nrows;
    int ncols;
    int mapHexSize;

    std::random_device rd;

    bool outOfBounds(int row, int col);
    bool outOfBounds(int x, int y, int z);



};

#endif // HEXMAP_H
