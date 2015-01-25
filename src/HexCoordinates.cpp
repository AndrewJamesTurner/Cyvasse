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

    int cubeXdiff = abs(cubeX = hex.getCubeX());
    int cubeYdiff = abs(cubeY = hex.getCubeY());
    int cubeZdiff = abs(cubeZ = hex.getCubeZ());

    if(cubeXdiff == 2 && cubeYdiff == 1 && cubeZdiff == 1)
        return true;
    else if(cubeXdiff == 1 && cubeYdiff == 2 && cubeZdiff == 1)
        return true;
    else if(cubeXdiff == 1 && cubeYdiff == 1 && cubeZdiff == 2)
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

    if(isDiagonal(hex) && isInRange(hex, 2*range))
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

    /* NEED FINISHING */





    return steps;
}


std::vector<HexCoordinates> HexCoordinates::getPossibleOrthogonalSteps(int range){

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


bool HexCoordinates::isInRange(HexCoordinates hex, int range){

    int distance = getDistance(hex);

    if(distance <= range)
        return true;
    else
        return false;
}


int HexCoordinates::getDistance(HexCoordinates hex){

    int distance = (abs(cubeX - hex.getCubeX()) + abs(cubeY - hex.getCubeY()) + abs(cubeZ - hex.getCubeZ()))/2;

    return distance;
}



int HexCoordinates::getCartesianX() {
    return cartesianX;
}

int HexCoordinates::getCartesianY() {
    return cartesianY;
}

int HexCoordinates::getCubeX() {
    return cubeX;
}

int HexCoordinates::getCubeY() {
    return cubeY;
}

int HexCoordinates::getCubeZ() {
    return cubeZ;
}



template <typename T> int HexCoordinates::sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

