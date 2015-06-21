#include "Spears.h"

Spears::Spears(Player _player) : Piece(_player, Type::spears, MoveType::diagonal, Terrain::forest, 2, 2, 1)
{

}

Spears::~Spears()
{
    //dtor
}
