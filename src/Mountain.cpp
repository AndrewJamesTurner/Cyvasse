#include "Mountain.h"

Mountain::Mountain(Player _player) : Piece(_player, Type::mountain, MoveType::none, Terrain::none, -1, 0, 0)
{

}

Mountain::~Mountain()
{
    //dtor
}
