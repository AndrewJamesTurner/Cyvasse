#include "Hex.h"

Hex::Hex(int _cartesianX, int _cartesianY) : HexCoordinates(_cartesianX, _cartesianY){

    piece = nullptr;
}

bool Hex::isPlayer(Player player) const{

    if(hasPiece()){
        if(piece->getPlayer() == player)
            return true;
        else
            return false;
    }
    else{
        return false;
    }
}

Piece* Hex::getPiece(void) const{
    return piece;
}

Type Hex::getType(void) const {
    return piece->getType();
}

bool Hex::hasPiece(void) const{

    if(piece)
        return true;
    else
        return false;
}

void Hex::setPiece(Piece* _piece){
    piece = _piece;
}

void Hex::clearPiece(void){
    piece = nullptr;
}










