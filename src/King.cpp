#include "King.h"

King::King(Player _player) : Piece(_player, Type::king, Movement::orthogonal, 1, std::string("Images/King.png"))
{

}

King::~King()
{
    //dtor
}
