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

bool HexCoordinates::isOrthogonal(HexCoordinates hexCoordinates){

    if(cubeX == hexCoordinates.getCubeX() || cubeY == hexCoordinates.getCubeY() || cubeZ == hexCoordinates.getCubeZ()){
        return true;
    }
    else{
        return false;
    }
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
