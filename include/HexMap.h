#ifndef HEXMAP_H
#define HEXMAP_H

#include <random>

#include "Hex.h"

#include "Rabble.h"
#include "King.h"
#include "Spears.h"
#include "Mountain.h"
#include "Crossbow.h"
#include "Dragon.h"

struct Move{

  int startX;
  int startY;

  int endX;
  int endY;

  Move(int _startX, int _startY, int _endX, int _endY) : startX(_startX), startY(_startY), endX{_endX}, endY{_endY}{}
};

enum class InitialBoard{testing,random,fromFile};


class HexMap
{
    public:
        HexMap(int _mapHexSize);

        void setPiece(int x, int y, Piece* piece);
        Piece* getPiece(int x, int y);
        void clearPiece(int x, int y);
        bool hasPiece(int x, int y) const;

        int getNumPieces(void) const;

        void movePeice(int xStart, int yStart, int xEnd, int yEnd);
        void movePeice(Hex start, Hex desination);

        std::vector<Hex> getHexes(void);
        Hex* getHexPnt(int x, int y);
        Hex getHex(int x, int y) const;

        int getHexSize(void) const;

        void populateBoard(InitialBoard initialBoard);

        std::vector<Hex> getPlayerPositions(const Player& player) const;

        bool isOnBoard(int x, int y) const;
        bool isOffBoard(int x, int y) const;

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

        bool isPieceOnBoard(const Player player, const Type type) const;

        bool isBothKingsOnBoard(void) const;

    protected:

        int getIndex(int x, int y) const;
        bool isOffMap(int x, int y) const;

        void testingBoard(void);
        void randomBoard(void);

        void placePieceRandomally(Piece* piece);

    private:

        int width;
        int height;

        int mapHexSize;
        std::vector<Hex> hexes;

        Hex *selectedHex;
        std::vector<Hex> highlightedHexes;


};

#endif // HEXMAP_H
