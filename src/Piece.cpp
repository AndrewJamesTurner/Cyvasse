#include "Piece.h"

Piece::Piece(Player _player, Type _type, Movement _movement, int _range)
{
    player = _player;
    type = _type;
    movetype = _movement;
    range = _range;
}



Piece::~Piece()
{
    //dtor
}

bool Piece::isMoutain(void){

    if(type == Type::mountain)
        return true;
    else
        return false;
}

Type Piece::getType(void) const {
    return type;
}



Movement Piece::getMoveType(void){
    return movetype;
}

Player Piece::getPlayer(void){
    return player;
}

 int Piece::getRange(void){
    return range;
 }
