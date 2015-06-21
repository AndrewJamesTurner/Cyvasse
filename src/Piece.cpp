#include "Piece.h"

Piece::Piece(Player _player, Type _type, MoveType _movement, Terrain _terrainBonus, int _range, int _tier, int _value) : player{_player}, type{_type}, movetype{_movement}, terrainBonus{_terrainBonus}, range{_range}, tier{_tier}, value{_value}
{

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



MoveType Piece::getMoveType(void){
    return movetype;
}

Player Piece::getPlayer(void){
    return player;
}

Terrain Piece::getBonusTerrain(void) const{
    return terrainBonus;
}


 int Piece::getRange(void){
    return range;
 }


int Piece::getValue(void) const{
    return value;
}

int Piece::getTier(void) const{
    return tier;
}
