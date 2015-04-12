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

        Type getType(void) const;


    private:
        Piece* piece;
};

#endif // HEX_H
