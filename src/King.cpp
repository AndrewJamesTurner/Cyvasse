#include "King.h"

King::King(Player _player) : Piece(_player, Type::king, MoveType::orthogonal, 1, 1, 1000)
{

}

King::~King()
{
    //dtor
}
