#ifndef HEXMAP_H
#define HEXMAP_H

#include "Hex.h"

#include "Rabble.h"
#include "King.h"
#include "Spears.h"
#include "Mountain.h"

class HexMap
{
    public:
        HexMap(int _hexSize, int _mapHexSize);

        void setPiece(int x, int y, Piece* piece);
        Piece* getPiece(int x, int y);
        void clearPiece(int x, int y);
        bool hasPiece(int x, int y) const;

        void movePeice(int xStart, int yStart, int xEnd, int yEnd);
        void movePeice(Hex start, Hex desination);

        void setColor(int x, int y, sf::Color color);
        void setBoarderColor(int x, int y, sf::Color color);

        std::vector<Hex> getHexes(void);
        Hex* getHexPnt(int x, int y);
        Hex getHex(int x, int y) const;


        void populateBoard(void);

        std::vector<Hex> getPlayerPositions(const Player& player) const;

        bool isOnBoard(int x, int y);
        bool isOffBoard(int x, int y);

        int getWidth(void) const {return width;}
        int getHeight(void) const {return height;}


    protected:

        int getIndex(int x, int y) const;
        bool isOffMap(int x, int y) const;

    private:

        int width;
        int height;
        int hexSize;
        int mapHexSize;
        std::vector<Hex> hexes;
};

#endif // HEXMAP_H
