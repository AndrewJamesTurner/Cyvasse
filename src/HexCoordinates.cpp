#include "HexCoordinates.h"

HexCoordinates::HexCoordinates(int _cartesianX, int _cartesianY) {
    cartesianX = _cartesianX;
    cartesianY = _cartesianY;

    updateCubeCoordinates();
}

HexCoordinates::HexCoordinates(int _cubeX, int _cubeY, int _cubeZ) {
    cubeX = _cubeX;
    cubeY = _cubeY;
    cubeZ = _cubeZ;

    updateCartesianCoordinates();
}


HexCoordinates::~HexCoordinates() {
    //dtor
}

void HexCoordinates::updateCubeCoordinates(void) {

    cubeX = cartesianX - (cartesianY - (cartesianY&1))/2;
    cubeZ = cartesianY;
    cubeY = 0 - cubeX - cubeZ;
}

void HexCoordinates::updateCartesianCoordinates(void) {

    cartesianX = cubeX + (cubeZ - (cubeZ&1)) / 2;
    cartesianY = cubeZ;
}

bool HexCoordinates::isOrthogonal(HexCoordinates hex){

    if(cubeX == hex.getCubeX() || cubeY == hex.getCubeY() || cubeZ == hex.getCubeZ()){
        return true;
    }
    else{
        return false;
    }
}

bool HexCoordinates::isDiagonal(HexCoordinates hex){

    int cubeXdiff = abs(cubeX - hex.getCubeX());
    int cubeYdiff = abs(cubeY - hex.getCubeY());
    int cubeZdiff = abs(cubeZ - hex.getCubeZ());


    if(cubeXdiff == 2*cubeYdiff && cubeYdiff == cubeZdiff)
        return true;
    else if(cubeYdiff == 2*cubeZdiff && cubeZdiff == cubeXdiff)
        return true;
    else if(cubeZdiff == 2*cubeXdiff && cubeXdiff == cubeYdiff)
        return true;
    else
        return false;
}



bool HexCoordinates::isOrthogonalRange(HexCoordinates hex, int range){

    int distance;

    if(!isOrthogonal(hex))
        return false;

    if(cubeX == hex.getCubeX())
        distance = abs(cubeY - hex.getCubeY());
    else if(cubeY == hex.getCubeY())
        distance = abs(cubeZ - hex.getCubeZ());
    else if(cubeZ == hex.getCubeZ())
        distance = abs(cubeX - hex.getCubeX());
    else
        return false;

    if(distance <= range)
        return true;
    else
        return false;
}

bool HexCoordinates::isDiagonalRange(HexCoordinates hex, int range){

    if(isDiagonal(hex) && isInRange(hex, range*3))
        return true;
    else
        return false;
}

bool HexCoordinates::isAnyRange(HexCoordinates hex, int range){

    int cubeXdiff = abs(cubeX - hex.getCubeX());
    int cubeYdiff = abs(cubeY - hex.getCubeY());
    int cubeZdiff = abs(cubeZ - hex.getCubeZ());

    int distance;

    distance = std::max(cubeXdiff,cubeYdiff);
    distance = std::max(distance,cubeZdiff);

    if(distance <= range)
        return true;
    else
        return false;
}



std::vector<HexCoordinates> HexCoordinates::orthogonalSteps(HexCoordinates hex){

    std::vector<HexCoordinates> steps;

    if(!isOrthogonal(hex))
        return steps;

    if(cubeX == hex.getCubeX()){

        int sign = sgn(hex.getCubeY() - cubeY);
        int distance = getDistance(hex);

        for(int i=1; i <= distance; i++){
            steps.push_back(HexCoordinates(cubeX, cubeY+sign*i, cubeZ-sign*i));
        }
    }

    else if(cubeY == hex.getCubeY()){

        int sign = sgn(hex.getCubeZ() - cubeZ);
        int distance = getDistance(hex);

        for(int i=1; i <= distance; i++){
            steps.push_back(HexCoordinates(cubeX-sign*i, cubeY, cubeZ+sign*i));
        }
    }
    else{
        int sign = sgn(hex.getCubeX() - cubeX);
        int distance = getDistance(hex);

        for(int i=1; i <= distance; i++){
            steps.push_back(HexCoordinates(cubeX+sign*i, cubeY-sign*i, cubeZ));
        }
    }

    return steps;
}


std::vector<HexCoordinates> HexCoordinates::diagonalSteps(HexCoordinates hex){

    std::vector<HexCoordinates> steps;

    if(!isDiagonal(hex))
        return steps;

    int distance = getDistance(hex)/2;

    int xDiff = cubeX - hex.getCubeX();
    int yDiff = cubeY - hex.getCubeY();
    int zDiff = cubeZ - hex.getCubeZ();

    if(xDiff == yDiff){

        int sign = sgn(cubeZ - hex.getCubeZ());

        for(int i=1; i <= distance; i++){
            steps.push_back(HexCoordinates(cubeX+sign*i, cubeY+sign*i, cubeZ-sign*2*i));
        }
    }
    else if(yDiff == zDiff){

        int sign = sgn(cubeX - hex.getCubeX());

        for(int i=1; i <= distance; i++){
            steps.push_back(HexCoordinates(cubeX-sign*2*i, cubeY+sign*i, cubeZ+sign*i));
        }
    }
    else if(zDiff == xDiff){

        int sign = sgn(cubeY - hex.getCubeY());

        for(int i=1; i <= distance; i++){
            steps.push_back(HexCoordinates(cubeX+sign*i, cubeY-sign*2*i, cubeZ+sign*i));
        }
    }

    return steps;
}


std::vector<HexCoordinates> HexCoordinates::anySteps(HexCoordinates hex){

    std::vector<HexCoordinates> steps;

    steps.push_back(HexCoordinates(hex.cubeX, hex.cubeY, hex.cubeZ));

    return steps;
}


std::vector<HexCoordinates> HexCoordinates::getPossibleOrthogonalSteps(int range) const {

    std::vector<HexCoordinates> steps;

    for(int i = -range; i <= range; i++){

        if(i==0)
            continue;

        steps.push_back(HexCoordinates(cubeX, cubeY+i, cubeZ-i));
        steps.push_back(HexCoordinates(cubeX-i, cubeY, cubeZ+i));
        steps.push_back(HexCoordinates(cubeX+i, cubeY-i, cubeZ));
    }

    return steps;
}

std::vector<HexCoordinates> HexCoordinates::getPossibleAnySteps(int range) const{

    std::vector<HexCoordinates> steps;

    for(int x = -range; x <= range; x++){
        for(int y = -range; y <= range; y++){
            for(int z = -range; z <= range; z++){

                int xMove = cubeX + x;
                int yMove = cubeY + y;
                int zMove = cubeZ + z;

                if((xMove + yMove + zMove) == 0)
                    steps.push_back(HexCoordinates(xMove, yMove, zMove));
            }
        }
    }

    return steps;
}




std::vector<HexCoordinates> HexCoordinates::getPossibleDiagonalSteps(int range) const {

    std::vector<HexCoordinates> steps;

    for(int i = -range; i <= range; i++){

        if(i==0)
            continue;

        steps.push_back(HexCoordinates(cubeX+i, cubeY+i, cubeZ-2*i));
        steps.push_back(HexCoordinates(cubeX+i, cubeY-2*i, cubeZ+i));
        steps.push_back(HexCoordinates(cubeX-2*i, cubeY+i, cubeZ+i));
    }

    return steps;
}



bool HexCoordinates::isInRange(HexCoordinates hex, int range){

    int distance = getDistance(hex);

    if(distance < range)
        return true;
    else
        return false;
}


int HexCoordinates::getDistance(HexCoordinates hex){

    int distance = (abs(cubeX - hex.getCubeX()) + abs(cubeY - hex.getCubeY()) + abs(cubeZ - hex.getCubeZ()))/2;

    return distance;
}


int HexCoordinates::getCartesianX() const{
    return cartesianX;
}

int HexCoordinates::getCartesianY() const{
    return cartesianY;
}

int HexCoordinates::getCubeX() const{
    return cubeX;
}

int HexCoordinates::getCubeY() const{
    return cubeY;
}

int HexCoordinates::getCubeZ() const{
    return cubeZ;
}



template <typename T> int HexCoordinates::sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

