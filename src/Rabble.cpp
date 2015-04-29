#include "Rabble.h"

Rabble::Rabble(Player _player) : Piece(_player, Type::rabble, Movement::orthogonal, 1, 1, 1)
{

}

Rabble::~Rabble()
{
    //dtor
}
