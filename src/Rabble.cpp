#include "Rabble.h"

Rabble::Rabble(Player _player) : Piece(_player, Type::rabble, MoveType::orthogonal, Terrain::none, 1, 1, 1)
{

}

Rabble::~Rabble()
{
    //dtor
}
