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

    populateBoard(InitialBoard::testing);
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

void HexMap::populateBoard(InitialBoard initialBoard){

    switch(initialBoard){

    case InitialBoard::testing:
        testingBoard();
        break;

    case InitialBoard::random:
        break;

    case InitialBoard::fromFile:
        std::cout << "Error InitialBoard::fromFile not implemented.\n";
        exit(0);
        break;
    }

    placeTerrain();
}


void HexMap::testingBoard(void){

    setPiece(6,8, new King(Player::player1));

    setPiece(5,8, new Rabble(Player::player1));
    setPiece(5,11, new Rabble(Player::player1));

    setPiece(5,10, new Spears(Player::player1));
    setPiece(6,11, new Spears(Player::player1));

    setPiece(4,10, new Crossbow(Player::player1));
    setPiece(7,11, new Crossbow(Player::player1));

    setPiece(3,9, new Mountain(Player::player1));
    setPiece(3,10, new Mountain(Player::player1));


    setPiece(3,2, new Rabble(Player::player2));
    setPiece(8,3, new King(Player::player2));
    setPiece(8,1, new Spears(Player::player2));
    setPiece(7,3, new Mountain(Player::player2));
    setPiece(4,3, new Crossbow(Player::player2));


}


void HexMap::placeTerrain(void){

    for(auto i = hexes.begin(); i<hexes.end(); ++i){

        if((*i).hasPiece()){

            switch((*i).getPiece()->getType()){

            case Type::king:
                break;
            case Type::rabble:
                break;
            case Type::crossbow:
                (*i).setTerrain(Terrain::hill);
                break;
            case Type::spears:
                (*i).setTerrain(Terrain::forest);
                break;
            case Type::mountain:
                break;
            }
        }
        else{
            (*i).setTerrain(Terrain::none);
        }
    }
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


bool HexMap::isOnBoard(int x, int y) const {

    HexCoordinates current(x,y);
    HexCoordinates center(mapHexSize,mapHexSize);

    if(center.isInRange(current, mapHexSize)){
        return true;
    }
    else{
        return false;
    }
}

bool HexMap::isOffBoard(int x, int y) const {
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

bool HexMap::isPieceOnBoard(const Player player, const Type type) const {

    bool onBoard = false;

    std::vector<Hex> playerPositions = getPlayerPositions(player);

    for(auto i = playerPositions.begin(); i<playerPositions.end(); ++i) {

        if( (*i).getPiece()->getType() == type){
            onBoard = true;
            break;
        }
    }

    return onBoard;
}


int HexMap::getNumPieces(void) const{

    std::vector<Hex> player1Positions = getPlayerPositions(Player::player1);
    std::vector<Hex> player2Positions = getPlayerPositions(Player::player2);

    return player1Positions.size() + player2Positions.size();
}

bool HexMap::isBothKingsOnBoard(void) const{
    return isPieceOnBoard(Player::player1, Type::king) && isPieceOnBoard(Player::player2, Type::king);
}



