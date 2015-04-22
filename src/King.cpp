#include "King.h"

King::King(Player _player) : Piece(_player, Type::king, Movement::orthogonal, 1, 1, 1000000)
{

}

King::~King()
{
    //dtor
}
