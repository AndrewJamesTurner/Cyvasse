#ifndef HEXMAP_H
#define HEXMAP_H

#include "header.h"

class HexMap
{
    public:
        HexMap(sf::RenderWindow *_window, float _hexSize, int _nrows, int _ncols);
        virtual ~HexMap();
        void update(void);
        int getRow(int x, int y);
        int getCol(int x, int y);
        int getXpos(int row, int col);
        int getYpos(int row, int col);
    protected:
    private:

    sf::RenderWindow *window;

    std::vector<sf::CircleShape> hex;

    float hexSize;
    float hexHeight;
    float hexWidth;

    int nrows;
    int ncols;

};

#endif // HEXMAP_H
