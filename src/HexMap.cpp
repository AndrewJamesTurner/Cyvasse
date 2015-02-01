#include "HexMap.h"

HexMap::HexMap(int _width, int _height, int _hexSize)
{

    width = _width;
    height = _height;
    hexSize = _hexSize;

    for(int x = 0; x<width; x++) {
        for(int y = 0; y<height; y++) {
            hexes.push_back(Hex(x,y, hexSize, sf::Color::White));
        }
    }
}

HexMap::~HexMap()
{
    //dtor
}


void HexMap::setPiece(int x, int y, Piece* piece){

    if(isOffMap(x,y))
        return;

    int index = getIndex(x,y);
    hexes[index].setPiece(piece);
}

Piece* HexMap::getPiece(int x, int y){

    if(isOffMap(x,y))
        return nullptr;

    int index = getIndex(x,y);
    Piece* piece = hexes[index].getPiece();

    return piece;
}

bool HexMap::hasPiece(int x, int y){

    if(isOffMap(x,y))
        return nullptr;

    int index = getIndex(x,y);
    return hexes[index].hasPiece();
}

void HexMap::removePiece(int x, int y){

    if(isOffMap(x,y))
        return;

    int index = getIndex(x,y);
    hexes[index].deletePiece();
}

void HexMap::movePeice(int xStart, int yStart, int xEnd, int yEnd){

    if(isOffMap(xStart,yStart) || isOffMap(xEnd,yEnd))
        return;

    removePiece(xEnd,yEnd);
    Piece* piece = getPiece(xStart,yStart);
    setPiece(xEnd,yEnd, piece);
}


void HexMap::setColor(int x, int y, sf::Color color){

    if(isOffMap(x,y))
        return;

    int index = getIndex(x,y);
    hexes[index].setColor(color);
}



int HexMap::getIndex(int x, int y) {
    return (x*width)+y;
}


bool HexMap::isOffMap(int x, int y){

    if(x < 0 || x >= width)
        return true;
    else if(y < 0 || y >= height)
        return true;
    else
        return false;
}

