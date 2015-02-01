#include "Spears.h"

Spears::Spears(Player _player) : Piece(_player, Type::spears, Movement::diagonal, 2, std::string("Images/Spears.png"))
{

}

Spears::~Spears()
{
    //dtor
}
