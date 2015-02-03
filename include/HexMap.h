#ifndef HEXMAP_H
#define HEXMAP_H

#include "Hex.h"

class HexMap
{
    public:
        HexMap(int _width, int _height, int _hexSize);
        HexMap(const HexMap &other);
        virtual ~HexMap();

        void setPiece(int x, int y, Piece* piece);
        Piece* getPiece(int x, int y);
        void removePiece(int x, int y);
        void clearPiece(int x, int y);
        bool hasPiece(int x, int y);

        void movePeice(int xStart, int yStart, int xEnd, int yEnd);
        void movePeice(Hex* start, Hex* desination);

        void setColor(int x, int y, sf::Color color);
        void setBoarderColor(int x, int y, sf::Color color);

        std::vector<Hex> getHexes(void);
        Hex* getHexPnt(int x, int y);

    protected:
    private:

        int width;
        int height;
        int hexSize;
        std::vector<Hex> hexes;


        int getIndex(int x, int y);
        bool isOffMap(int x, int y);

};

#endif // HEXMAP_H
