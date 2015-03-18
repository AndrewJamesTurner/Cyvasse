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

    setPiece(5,5, new Rabble(Player::player1));
    setPiece(6,6, new King(Player::player1));
    setPiece(5,7, new Spears(Player::player1));
    setPiece(3,7, new Mountain(Player::player1));

    setPiece(3,2, new Rabble(Player::player2));
    setPiece(8,8, new King(Player::player2));
    setPiece(8,1, new Spears(Player::player2));
    setPiece(7,3, new Mountain(Player::player2));
}


Hex* HexMap::getHexPnt(int x, int y){

    if(isOffMap(x,y))
        return nullptr;

    int index = getIndex(x,y);

    return &hexes[index];
}


Hex HexMap::getHex(int x, int y) const{

    if(isOffMap(x,y))
        std::cerr << "ERROR: in getHex of HexMap";

    int index = getIndex(x,y);

    Hex returnedHex(hexes[index]);

    return returnedHex;
}


void HexMap::setPiece(int x, int y, Piece* piece){

    if(isOffMap(x,y))
        return;

    int index = getIndex(x,y);
    hexes[index].setPiece(piece);

    //playerPositions.push_back(Hex(hexes[index]));
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


void HexMap::clearPiece(int x, int y){

    if(isOffMap(x,y))
        return;

    int index = getIndex(x,y);

    //playerPositions.erase(std::remove(playerPositions.begin(), playerPositions.end(), hexes[index]), playerPositions.end());

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


void HexMap::movePeice(Hex start, Hex desination){

    int xStart = start.getCartesianX();
    int yStart = start.getCartesianY();

    int xEnd = desination.getCartesianX();
    int yEnd = desination.getCartesianY();

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


int HexMap::getIndex(int x, int y) const {
    return (x*width)+y;
}


bool HexMap::isOffMap(int x, int y) const {

    if(x < 0 || x >= width)
        return true;
    else if(y < 0 || y >= height)
        return true;
    else
        return false;
}


std::vector<Hex> HexMap::getPlayerPositions(Player player) const{

    std::vector<Hex> playerPositions123;

    for(auto i = hexes.begin(); i<hexes.end(); ++i) {

        if((*i).hasPiece() && (*i).isPlayer(player) ){

            playerPositions123.push_back(Hex((*i)));
        }
    }

    return playerPositions123;
}
