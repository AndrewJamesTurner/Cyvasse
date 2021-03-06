#ifndef HEX_H
#define HEX_H

#include "Piece.h"
#include "HexCoordinates.h"



class Hex : public HexCoordinates
{
    public:
        Hex(int _cartesianX, int _cartesianY);

        Piece* getPiece(void) const;
        bool hasPiece(void) const;
        void setPiece(Piece* _piece);
        void clearPiece(void);

        bool isPlayer(Player player) const;

        int getPieceTier(void) const;


        bool equals(Hex hex);

        Terrain getTerrain(void) const;
        void setTerrain(Terrain _terrain);

    private:
        Piece* piece;
        Terrain terrain;
};

#endif // HEX_H
