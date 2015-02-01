#include "Rabble.h"

Rabble::Rabble(Player _player) : Piece(_player, Type::rabble, Movement::orthogonal, 3, std::string("Images/Rabble.png"))
{

}

Rabble::~Rabble()
{
    //dtor
}
