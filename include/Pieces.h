#ifndef PIECES_H
#define PIECES_H

#include <SFML/Graphics.hpp>
#include "Piece.h"


class Pieces
{
    public:
        Pieces();
        virtual ~Pieces();
    protected:
    private:

    std::vector<Piece> pieces;
};

#endif // PIECES_H
