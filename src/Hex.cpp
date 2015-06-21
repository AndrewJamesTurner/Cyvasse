#include "Hex.h"

Hex::Hex(int _cartesianX, int _cartesianY) : HexCoordinates(_cartesianX, _cartesianY){

    piece = nullptr;
    terrain = Terrain::none;
}

bool Hex::equals(Hex hex){

    if(cartesianX == hex.getCartesianX() && cartesianY == hex.getCartesianY())
        return true;

    return false;
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

Terrain Hex::getTerrain(void) const{
    return terrain;
}


void Hex::setTerrain(Terrain _terrain){
    terrain = _terrain;
}








