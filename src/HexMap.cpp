#include "HexMap.h"

HexMap::HexMap(int _mapHexSize):

    width{2*_mapHexSize+1},
    height{2*_mapHexSize+1},
    mapHexSize{_mapHexSize},
    selectedHex{nullptr}
{

    for(int x = 0; x<width; x++) {
        for(int y = 0; y<height; y++) {
            hexes.push_back(Hex(x,y));
        }
    }

    populateBoard();
}


bool HexMap::isHexSelected(void){

    if(selectedHex)
        return true;
    else
        return false;
}

bool HexMap::isHexSelected(int x, int y){

    if(!isHexSelected()){
        return false;
    }

    else if(x == selectedHex->getCartesianX() && y == selectedHex->getCartesianY()){
        return true;
    }

    else{
        return false;
    }
}



Hex HexMap::getSelectedHex(void){
    return *selectedHex;
}

void HexMap::setSelectedHex(int x, int y){
    selectedHex = getHexPnt(x,y);
}

void HexMap::setSelectedHex(Hex *_hex){
    selectedHex = _hex;
}

std::vector<Hex> HexMap::getHexes(void){
    return hexes;
}

void HexMap::populateBoard(void){

    setPiece(5,8, new Rabble(Player::player1));
    setPiece(6,8, new King(Player::player1));
    setPiece(5,10, new Spears(Player::player1));
    setPiece(3,9, new Mountain(Player::player1));
    setPiece(3,10, new Mountain(Player::player1));

    setPiece(3,2, new Rabble(Player::player2));
    setPiece(8,3, new King(Player::player2));
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
}

Piece* HexMap::getPiece(int x, int y){

    if(isOffMap(x,y))
        return nullptr;

    int index = getIndex(x,y);
    Piece* piece = hexes[index].getPiece();

    return piece;
}

bool HexMap::hasPiece(int x, int y) const{

    if(isOffMap(x,y))
        return nullptr;

    int index = getIndex(x,y);
    return hexes[index].hasPiece();
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


void HexMap::movePeice(Hex start, Hex desination){

    int xStart = start.getCartesianX();
    int yStart = start.getCartesianY();

    int xEnd = desination.getCartesianX();
    int yEnd = desination.getCartesianY();

    movePeice(xStart, yStart, xEnd, yEnd);
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


std::vector<Hex> HexMap::getPlayerPositions(const Player& player) const{

    std::vector<Hex> playerPositions;

    for(auto i = hexes.begin(); i<hexes.end(); ++i) {

        if((*i).hasPiece() && (*i).isPlayer(player) ){

            playerPositions.push_back(Hex((*i)));
        }
    }

    return playerPositions;
}


bool HexMap::isOnBoard(int x, int y){

    HexCoordinates current(x,y);
    HexCoordinates center(mapHexSize,mapHexSize);

    if(center.isInRange(current, mapHexSize)){
        return true;
    }
    else{
        return false;
    }
}

bool HexMap::isOffBoard(int x, int y){
    return !isOnBoard(x,y);
}




void HexMap::clearHighlightedHexes(void){
    highlightedHexes.clear();
}

void HexMap::addHighlightedHexes(Hex hex){
    highlightedHexes.push_back(hex);
}


bool HexMap::isHexHighlighted(Hex hex){

    for(auto i = highlightedHexes.begin(); i<highlightedHexes.end(); ++i) {

        if(hex.getCartesianX() == (*i).getCartesianX() && hex.getCartesianY() == (*i).getCartesianY())
            return true;
    }

    return false;
}

bool HexMap::isInPlayerhalf(Player player, int yPos){

    if(player == Player::player1 && yPos > getHeight()/2)
        return true;
    else if(player == Player::player2 && yPos < 1 + getHeight()/2)
        return true;
    else
        return false;

}



