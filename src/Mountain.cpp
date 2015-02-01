#include "Mountain.h"

Mountain::Mountain(Player _player) : Piece(_player, Type::mountain, Movement::none, -1, std::string("Images/Mountain.png"))
{

}

Mountain::~Mountain()
{
    //dtor
}
