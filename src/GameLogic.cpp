#include "GameLogic.h"
#include <vector>

GameLogic::GameLogic(sf::RenderWindow *_window, float _hexSize, int _mapHexSize)    {

    window = _window;

    mapHexSize = _mapHexSize;
    width = 2*mapHexSize+1;
    height = 2*mapHexSize+1;

    hexSize =_hexSize;
    hexHeight = 2 * hexSize;
    hexWidth = hexHeight * (sqrt(3) / 2);

    hexMap = new HexMap(width, height, hexSize);

    selectedHex = nullptr;

    hexMap->setPiece(5,5,new Rabble(Player::player1));
    hexMap->setPiece(6,6,new King(Player::player1));
    hexMap->setPiece(5,7,new Spears(Player::player1));
    hexMap->setPiece(3,7,new Mountain(Player::player1));

    hexMap->setPiece(3,2,new Rabble(Player::player2));
    hexMap->setPiece(8,8,new King(Player::player2));
    hexMap->setPiece(8,1,new Spears(Player::player2));
    hexMap->setPiece(7,3,new Mountain(Player::player2));

    resetMap();
}

GameLogic::~GameLogic() {
    delete hexMap;
}


void GameLogic::mapClicked(int xPixel, int yPixel) {

    int x = getX(xPixel, yPixel);
    int y = getY(xPixel, yPixel);

    if(outOfBounds(x,y)) {
        return;
    }

    Hex* hexClicked = hexMap->getHexPnt(x,y);

    resetMap();

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

void GameLogic::deselect(void){

    selectedHex = nullptr;
    resetMap();
}

void GameLogic::showMovements(Hex* hex){

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
            hexMap->setColor(x,y,sf::Color(230,0,0));
    }
}

bool GameLogic::movePiece(Hex* sourceHex, Hex* targetHex){

    std::vector<HexCoordinates> steps;

    if(sourceHex == targetHex)
        return false;

    Movement moveType = sourceHex->getPiece()->getMoveType();

    // if the movement type is orthogonal and the two hexes are orthogonal and in range
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

        if( hexMap->hasPiece((*i).getCartesianX(), (*i).getCartesianY()) ){
            return false;
        }
    }

    // check if the target is clear
    if(!targetHex->hasPiece()){
        hexMap->movePeice(sourceHex, targetHex);
        return true;
    }

    // if target contains opponent
    else if(sourceHex->getPiece()->getPlayer() != targetHex->getPiece()->getPlayer() && !targetHex->getPiece()->isMoutain()){
        hexMap->movePeice(sourceHex, targetHex);
        return true;
    }
    else{
        return false;
    }
}


void GameLogic::resetMap(void) {

    HexCoordinates centerHex(mapHexSize, mapHexSize);

    for(int x = 0; x<width; x++) {
        for(int y = 0; y<height; y++) {

            HexCoordinates currentHex(x, y);

            if(centerHex.isInRange(currentHex, mapHexSize)){
                hexMap->setColor(x,y,sf::Color(17,220,51));
            }
            else {
                hexMap->setColor(x,y,sf::Color(20,20,230));
            }

            hexMap->setBoarderColor(x,y,sf::Color::Black);
        }
    }
}


void GameLogic::update(void) {

    std::vector<Hex> hexes = hexMap->getHexes();

    for(auto i = hexes.begin(); i!=hexes.end(); ++i) {
        (*i).draw(window);
    }
}


int GameLogic::getX(int pixelX, int pixelY) {

    int xPos;

    pixelX = pixelX;

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

int GameLogic::getY(int pixelX, int pixelY) {

    int yPos;

    yPos = (pixelY + (hexSize*0.5))/ (hexHeight*0.75);

    return yPos;
}


bool GameLogic::outOfBounds(int x, int y){

    HexCoordinates current(x,y);
    HexCoordinates center(mapHexSize,mapHexSize);

    if(center.isInRange(current, mapHexSize)){
        return false;
    }
    else{
        return true;
    }
}
