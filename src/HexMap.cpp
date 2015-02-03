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

HexMap::HexMap(const HexMap &other)/* : hexes(other.hexes.size())*/{

    width = other.width;
    height = other.height;
    hexSize = other.hexSize;
    hexes = other.hexes;

/*
    for (std::size_t i = 0; i < other.hexes.size(); ++i)
        hexes[i] = new Hex(other.hexes[i]);
*/
/*
    std::cout << "\nhere\n";
*/
/*
    for(std::size_t i = 0; i < hexes.size(); i++){
        hexes.push_back(Hex(other.hexes[i]));
        //std::cout << "\nhere\n";
    }

*/



}


HexMap::~HexMap()
{
    //dtor
}


std::vector<Hex> HexMap::getHexes(void){

    return hexes;
}

Hex* HexMap::getHexPnt(int x, int y){

    if(isOffMap(x,y))
        return nullptr;

    int index = getIndex(x,y);

    return &hexes[index];
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

void HexMap::clearPiece(int x, int y){

    if(isOffMap(x,y))
        return;

    int index = getIndex(x,y);
    hexes[index].clearPiece();
}

void HexMap::movePeice(int xStart, int yStart, int xEnd, int yEnd){

    if(isOffMap(xStart,yStart) || isOffMap(xEnd,yEnd))
        return;

    clearPiece(xEnd,yEnd);
    Piece* piece = getPiece(xStart,yStart);
    setPiece(xEnd,yEnd, piece);
    clearPiece(xStart,yStart);
}



void HexMap::movePeice(Hex* start, Hex* desination){

    int xStart = start->getCartesianX();
    int yStart = start->getCartesianY();

    int xEnd = desination->getCartesianX();
    int yEnd = desination->getCartesianY();

    movePeice(xStart, yStart, xEnd, yEnd);
}



void HexMap::setColor(int x, int y, sf::Color color){

    if(isOffMap(x,y))
        return;

    int index = getIndex(x,y);
    hexes[index].setColor(color);
}


void HexMap::setBoarderColor(int x, int y, sf::Color color){

    if(isOffMap(x,y))
        return;

    int index = getIndex(x,y);
    hexes[index].setBoarderColor(color);
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

