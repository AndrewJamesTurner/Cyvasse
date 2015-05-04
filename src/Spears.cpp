#include "Spears.h"

Spears::Spears(Player _player) : Piece(_player, Type::spears, MoveType::diagonal, 2, 1, 2)
{

}

Spears::~Spears()
{
    //dtor
}
