#include "Crossbow.h"

Crossbow::Crossbow(Player _player) : Piece(_player, Type::crossbow, MoveType::orthogonal, 3, 1, 1)
{
    //ctor
}

Crossbow::~Crossbow()
{
    //dtor
}
