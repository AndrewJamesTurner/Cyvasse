#include "Movement.h"

Movement::Movement()
{
    //ctor
}

Movement::~Movement()
{
    //dtor
}

std::vector<Hex> Movement::getPossibleMovements(const HexMap& _hexMap, const Hex& hex){

    std::vector<HexCoordinates> movements;
    std::vector<Hex> possibleMovements;

    if(hex.getPiece()->getMoveType() == MoveType::orthogonal){
        movements = hex.getPossibleOrthogonalSteps(hex.getPiece()->getRange());
    }
    else if(hex.getPiece()->getMoveType() == MoveType::diagonal){
       movements = hex.getPossibleDiagonalSteps(hex.getPiece()->getRange());
    }

    for(auto i = movements.begin(); i<movements.end(); ++i) {

        int x = (*i).getCartesianX();
        int y = (*i).getCartesianY();

        if(_hexMap.isOnBoard(x,y))
            possibleMovements.push_back(_hexMap.getHex(x,y));
    }

    return possibleMovements;
}

std::vector<Hex> Movement::getValidMovements(const HexMap& _hexMap, const Hex& hex){

    std::vector<Hex> validMovements;
    std::vector<Hex> possibleMovements = getPossibleMovements(_hexMap, hex);

    for(auto i = possibleMovements.begin(); i<possibleMovements.end(); ++i) {

        if(canMove(_hexMap, hex, (*i)))
            validMovements.push_back((*i));
    }

    return validMovements;
}

std::vector<Move> Movement::getPossibleMoves(const HexMap& _hexMap, const Player& player){

    std::vector<Move> possibleMoves;
    std::vector<Hex> playerPositions = _hexMap.getPlayerPositions(player);

    for(auto i = playerPositions.begin(); i<playerPositions.end(); ++i) {

        std::vector<Hex> validMoves = getValidMovements(_hexMap, (*i));

        for(auto j = validMoves.begin(); j<validMoves.end(); ++j) {
            Move _move((*i).getCartesianX(), (*i).getCartesianY(), (*j).getCartesianX(), (*j).getCartesianY());
            possibleMoves.push_back(_move);
        }
    }

    return possibleMoves;
}


bool Movement::canMove(HexMap _hexmap, Hex sourceHex, Hex targetHex){

    std::vector<HexCoordinates> steps;

    if(sourceHex.getCartesianX() == targetHex.getCartesianX() && sourceHex.getCartesianY() == targetHex.getCartesianY())
        return false;

    else if(_hexmap.isOffBoard(targetHex.getCartesianX(), targetHex.getCartesianY()))
        return false;

    else if(_hexmap.isOffBoard(sourceHex.getCartesianX(), sourceHex.getCartesianY()))
        return false;

    else if(!sourceHex.hasPiece())
        return false;

    MoveType moveType = sourceHex.getPiece()->getMoveType();

    // if the movement type is orthogonal and the two hexes are in orthogonal range
    if(moveType == MoveType::orthogonal && sourceHex.isOrthogonalRange(targetHex, sourceHex.getPiece()->getRange())){
       steps = sourceHex.orthogonalSteps(targetHex);
    }

    // if the movement type is diagonal and the two hexes are in diagonal range
    else if(moveType == MoveType::diagonal && sourceHex.isDiagonalRange(targetHex, sourceHex.getPiece()->getRange())){
        steps = sourceHex.diagonalSteps(targetHex);
    }
    else{
        return false;
    }

    // check all the steps to targetHex are clear
    for(auto i = steps.begin(); i!=steps.end()-1; ++i) {

        if(_hexmap.isOffBoard((*i).getCartesianX(), (*i).getCartesianY())){
            return false;
        }
        if( _hexmap.hasPiece((*i).getCartesianX(), (*i).getCartesianY()) ){
            return false;
        }
    }

    // check if the target is clear
    if(!targetHex.hasPiece())
        return true;

    // if target contains opponent and is not a mountain and is lower/equal tier
    else if(sourceHex.getPiece()->getPlayer() != targetHex.getPiece()->getPlayer() &&
            !targetHex.getPiece()->isMoutain() &&
            sourceHex.getPiece()->getTier() >= targetHex.getPiece()->getTier())
        return true;
    else
        return false;
}
