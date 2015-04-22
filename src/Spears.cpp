#include "Spears.h"

Spears::Spears(Player _player) : Piece(_player, Type::spears, Movement::diagonal, 2, 2, 2)
{

}

Spears::~Spears()
{
    //dtor
}
