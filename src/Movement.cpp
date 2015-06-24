#include "Movement.h"

std::default_random_engine Movement::engine = std::default_random_engine{};

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

    switch(hex.getPiece()->getMoveType()){

    case MoveType::orthogonal:
        movements = hex.getPossibleOrthogonalSteps(hex.getPiece()->getRange());
        break;
    case MoveType::diagonal:
        movements = hex.getPossibleDiagonalSteps(hex.getPiece()->getRange());
        break;
    case MoveType::any:
        movements = hex.getPossibleAnySteps(hex.getPiece()->getRange());
        break;
    case MoveType::none:
        break;
    }

    for(auto i = movements.begin(); i<movements.end(); ++i) {

        int x = (*i).getCartesianX();
        int y = (*i).getCartesianY();

        if(_hexMap.isOnBoard(x,y))
            possibleMovements.push_back(_hexMap.getHex(x,y));
    }

    std::shuffle(std::begin(possibleMovements), std::end(possibleMovements), engine);

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

    std::shuffle(std::begin(possibleMoves), std::end(possibleMoves), engine);

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

    // if the movement type is any and..
    else if(moveType == MoveType::any && sourceHex.isAnyRange(targetHex, sourceHex.getPiece()->getRange())){
        steps = sourceHex.anySteps(targetHex);
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
            sourceHex.getPiece()->getTier() + isOnTerrainBonus(sourceHex)  >= targetHex.getPiece()->getTier() + isOnTerrainBonus(targetHex) )
        return true;
    else
        return false;
}


int Movement::isOnTerrainBonus(const Hex hex){

    if(hex.getTerrain() != Terrain::none && hex.getTerrain() == hex.getPiece()->getBonusTerrain())
        return 1;
    else
        return 0;
}


