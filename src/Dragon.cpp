#include "Dragon.h"

Dragon::Dragon(Player _player)  : Piece(_player, Type::dragon, MoveType::any, Terrain::none, 4, 4, 1)
{
    //ctor
}

Dragon::~Dragon()
{
    //dtor
}
