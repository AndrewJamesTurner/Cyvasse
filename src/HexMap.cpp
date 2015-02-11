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

    populateBoard();
}


HexMap::~HexMap()
{
    //dtor
}


std::vector<Hex> HexMap::getHexes(void){
    return hexes;
}

void HexMap::populateBoard(void){

    pieces.push_back(new Rabble(Player::player1));
    setPiece(5,5, pieces.back());

    pieces.push_back(new King(Player::player1));
    setPiece(6,6, pieces.back());

    pieces.push_back(new Spears(Player::player1));
    setPiece(5,7, pieces.back());

    pieces.push_back(new Mountain(Player::player1));
    setPiece(3,7, pieces.back());

    pieces.push_back(new Rabble(Player::player2));
    setPiece(3,2, pieces.back());

    pieces.push_back(new King(Player::player2));
    setPiece(8,8, pieces.back());

    pieces.push_back(new Spears(Player::player2));
    setPiece(8,1, pieces.back());

    pieces.push_back(new Mountain(Player::player2));
    setPiece(7,3, pieces.back());
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

