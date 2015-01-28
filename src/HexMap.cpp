#include "HexMap.h"
#include <vector>

HexMap::HexMap(sf::RenderWindow *_window, float _hexSize, int _mapHexSize) {

    window = _window;

    mapHexSize = _mapHexSize;
    width = 2*mapHexSize + mapHexSize;
    height = 2*mapHexSize + mapHexSize;

    hexSize =_hexSize;
    hexHeight = 2 * hexSize;
    hexWidth = hexHeight * (sqrt(3) / 2);

    selectedHex = nullptr;

    for(int x = 0; x<width; x++) {
        for(int y = 0; y<height; y++) {
            hexes.push_back(Hex(x,y, hexSize, sf::Color::White));
        }
    }


    hexes[getIndex(5,5)].setPiece(new Piece(Player::player1, Type::rabble));
    hexes[getIndex(6,6)].setPiece(new Piece(Player::player1, Type::king));

    hexes[getIndex(2,2)].setPiece(new Piece(Player::player2, Type::rabble));
    hexes[getIndex(8,8)].setPiece(new Piece(Player::player2, Type::king));


    hexes[getIndex(3,7)].setPiece(new Piece(Player::player1, Type::mountain));
    hexes[getIndex(7,3)].setPiece(new Piece(Player::player2, Type::mountain));

    hexes[getIndex(4,7)].setPiece(new Piece(Player::player1, Type::spears));
    hexes[getIndex(7,1)].setPiece(new Piece(Player::player2, Type::spears));


    clearMap();
}

HexMap::~HexMap() {
    //dtor
}


void HexMap::mapClicked(int xPixel, int yPixel) {

    int x = getX(xPixel, yPixel);
    int y = getY(xPixel, yPixel);

    if(outOfBounds(x,y)) {
        return;
    }

    Hex* hexClicked = &hexes[getIndex(x,y)];

    clearMap();

    // if nothing selected
    if(!selectedHex){

        // if clicked on an empty sapce, a moutain or an enemy
        if(!hexClicked->hasPiece() || hexClicked->getPiece()->isMoutain() || hexClicked->getPiece()->getPlayer() != Player::player1){
            selectedHex = nullptr;

        }
        // else if is moveable player unit
        else{
            hexClicked->setBoarderColor(sf::Color::Yellow);
            selectedHex = hexClicked;
        }
    }
    // if something selected
    else{

        // if clicked currently selected
        if(selectedHex == hexClicked){
            hexClicked->setBoarderColor(sf::Color::Yellow);
            showMovements(hexClicked);
        }

        // if can move to place clicked
        else if(movePiece(selectedHex, hexClicked)){
            selectedHex = nullptr;
        }

        // if clicked some where cannot be moved
        else{
            selectedHex = nullptr;
        }
    }
}

void HexMap::deselect(void){

    selectedHex = nullptr;
    clearMap();
}

void HexMap::showMovements(Hex* hex){

    std::vector<HexCoordinates> movements;

    if(hex->getPiece()->getMoveType() == Movement::orthogonal){
        movements = hex->getPossibleOrthogonalSteps(hex->getPiece()->getRange());
    }
    else if(hex->getPiece()->getMoveType() == Movement::diagonal){
       movements = hex->getPossibleDiagonalSteps(hex->getPiece()->getRange());
    }

    for(auto i = movements.begin(); i<movements.end(); ++i) {

        int x = (*i).getCartesianX();
        int y = (*i).getCartesianY();

        if(!outOfBounds(x,y))
            hexes[getIndex(x,y)].setColor(sf::Color(230,0,0));
    }
}

bool HexMap::movePiece(Hex* sourceHex, Hex* targetHex){

    std::vector<HexCoordinates> steps;

    if(sourceHex == targetHex)
        return false;

    Movement moveType = sourceHex->getPiece()->getMoveType();

    // if the movement type is orthogonal and the two hexes are orthogonal
    if(moveType == Movement::orthogonal && sourceHex->isOrthogonalRange(*targetHex, sourceHex->getPiece()->getRange())){
       steps = sourceHex->orthogonalSteps(*targetHex);
    }

    else if(moveType == Movement::diagonal && sourceHex->isDiagonalRange(*targetHex, sourceHex->getPiece()->getRange())){
        steps = sourceHex->diagonalSteps(*targetHex);
    }
    else{
        return false;
    }


    // check all the steps to targetHex are clear
    for(auto i = steps.begin(); i!=steps.end()-1; ++i) {

        if(hexes[getIndex((*i).getCartesianX(),(*i).getCartesianY())].hasPiece()){ std::cout << "here";
            return false;
        }
    }

    // check if the target is clear
    if(!targetHex->hasPiece()){

        targetHex->setPiece(sourceHex->getPiece());
        sourceHex->clearPiece();
        return true;
    }

    // if target contains opponent
    else if(sourceHex->getPiece()->getPlayer() != targetHex->getPiece()->getPlayer() && !targetHex->getPiece()->isMoutain()){

        delete targetHex->getPiece();
        targetHex->setPiece(sourceHex->getPiece());
        sourceHex->clearPiece();
        return true;
    }
    else{
        return false;
    }

}




int HexMap::getIndex(int x, int y) {
    return (x*width)+y;
}

void HexMap::clearMap(void) {

    HexCoordinates centerHex(mapHexSize, mapHexSize);

    for(int x = 0; x<width; x++) {
        for(int y = 0; y<height; y++) {

            HexCoordinates currentHex(x, y);

            if(centerHex.isInRange(currentHex, mapHexSize)){
                hexes[getIndex(x,y)].setColor(sf::Color(17,220,51));
            }
            else {
                hexes[getIndex(x,y)].setColor(sf::Color(20,20,230));
            }

            hexes[getIndex(x,y)].setBoarderColor(sf::Color::Black);
        }
    }
}


void HexMap::update(void) {

    for(auto i = hexes.begin(); i!=hexes.end(); ++i) {

        (*i).draw(window);
        /*
                if((*i).getPiece()){
                    Piece *piece = (*i).getPiece();
                    sf::Sprite sprite = piece->getSprite();
                    window->draw(sprite);
                }
            */
    }
}




/*


void HexMap::moveDiagonal(int row, int col, int range) {

    if(outOfBounds(row,col))
        return;

    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(0, 256);

    int red = uniform_dist(e1);
    int green = uniform_dist(e1);
    int blue = uniform_dist(e1);

    // get cube coordinates
    int xCentre = col - (row - (row&1))/2;
    int zCentre = row;
    int yCentre = 0 - xCentre - zCentre;
    changeColour(zCentre, xCentre + (zCentre - (zCentre&1))/2, red, green, blue);

    for(int i = -range; i <= range; i++) {

        int x,y,z;

        // left right
        x = xCentre + 2*i;
        y = yCentre - i;
        z = zCentre - i;
        changeColour(x, y, z, red, green, blue);

        // diagonal 1
        x = xCentre - i;
        y = yCentre + 2*i;
        z = zCentre - i;
        changeColour(x, y, z, red, green, blue);

        // diagonal 2
        x = xCentre - i;
        y = yCentre - i;
        z = zCentre + 2*i;
        changeColour(x, y, z, red, green, blue);
    }
}

void HexMap::moveAny(int row, int col, int range) {

    if(outOfBounds(row,col))
        return;

    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(0, 256);

    int red = uniform_dist(e1);
    int green = uniform_dist(e1);
    int blue = uniform_dist(e1);

    // get cube coordinates
    int xCentre = col - (row - (row&1))/2;
    int zCentre = row;
    int yCentre = 0 - xCentre - zCentre;

    for(int dx = -range; dx <= range; dx++) {
        for(int dy = -range; dy <= range; dy++) {
            for(int dz = -range; dz <= range; dz++) {

                int x = xCentre + dx;
                int y = yCentre + dy;
                int z = zCentre + dz;

                if(x+y+z == 0) {
                    changeColour(x, y, z, red, green, blue);
                }
            }
        }
    }
}
*/

int HexMap::getX(int pixelX, int pixelY) {

    int xPos;

    if(getY(pixelX, pixelY) % 2 == 0) {
        xPos = (pixelX/hexWidth) + 0.5;
    } else {

        if(pixelX < hexWidth/2) {
            xPos = -1;
        } else {
            xPos = (pixelX/hexWidth);
        }
    }

    return xPos;
}

int HexMap::getY(int pixelX, int pixelY) {

    int yPos;

    yPos = pixelY /(hexHeight*0.75);

    return yPos;
}


bool HexMap::outOfBounds(int x, int y){

    HexCoordinates current(x,y);
    HexCoordinates center(mapHexSize,mapHexSize);

    if(center.isInRange(current, mapHexSize)){
        return false;
    }
    else{
        return true;
    }
}
