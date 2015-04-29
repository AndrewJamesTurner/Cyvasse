#ifndef HEXMAP_H
#define HEXMAP_H

#include "Hex.h"

#include "Rabble.h"
#include "King.h"
#include "Spears.h"
#include "Mountain.h"
#include "Crossbow.h"

enum class GameState{placement,player1Turn,player2Turn,player1Won,player2Won};


class HexMap
{
    public:
        HexMap(int _mapHexSize);

        void setPiece(int x, int y, Piece* piece);
        Piece* getPiece(int x, int y);
        void clearPiece(int x, int y);
        bool hasPiece(int x, int y) const;

        void movePeice(int xStart, int yStart, int xEnd, int yEnd);
        void movePeice(Hex start, Hex desination);

        std::vector<Hex> getHexes(void);
        Hex* getHexPnt(int x, int y);
        Hex getHex(int x, int y) const;

        void populateBoard(void);

        std::vector<Hex> getPlayerPositions(const Player& player) const;

        bool isOnBoard(int x, int y);
        bool isOffBoard(int x, int y);

        int getWidth(void) const {return width;}
        int getHeight(void) const {return height;}

        bool isHexSelected(void);
        bool isHexSelected(int x, int y);

        Hex getSelectedHex(void);
        void setSelectedHex(int x, int y);
        void setSelectedHex(Hex *_hex);

        void clearHighlightedHexes(void);
        void addHighlightedHexes(Hex hexPnt);
        bool isHexHighlighted(Hex hex);

        bool isInPlayerhalf(Player player, int yPos);

        void placeTerrain(void);

    protected:

        int getIndex(int x, int y) const;
        bool isOffMap(int x, int y) const;


    private:

        int width;
        int height;

        int mapHexSize;
        std::vector<Hex> hexes;

        Hex *selectedHex;
        std::vector<Hex> highlightedHexes;
};

#endif // HEXMAP_H
