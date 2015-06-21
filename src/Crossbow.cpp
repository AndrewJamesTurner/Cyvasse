#include "Crossbow.h"

Crossbow::Crossbow(Player _player) : Piece(_player, Type::crossbow, MoveType::orthogonal, Terrain::hill, 3, 2, 1)
{
    //ctor
}

Crossbow::~Crossbow()
{
    //dtor
}
