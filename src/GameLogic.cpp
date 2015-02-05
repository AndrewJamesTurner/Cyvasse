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

    srand (time(NULL));

    hexMap = new HexMap(width, height, hexSize);

    selectedHex = nullptr;

    populateBoard();

    resetMap();
}

GameLogic::~GameLogic() {
    delete hexMap;
}

void GameLogic::populateBoard(void){

    pieces.push_back(new Rabble(Player::player1));
    hexMap->setPiece(5,5,pieces.back());

    pieces.push_back(new King(Player::player1));
    hexMap->setPiece(6,6,pieces.back());

    pieces.push_back(new Spears(Player::player1));
    hexMap->setPiece(5,7,pieces.back());

    pieces.push_back(new Mountain(Player::player1));
    hexMap->setPiece(3,7,pieces.back());

    pieces.push_back(new Rabble(Player::player2));
    hexMap->setPiece(3,2,pieces.back());

    pieces.push_back(new King(Player::player2));
    hexMap->setPiece(8,8,pieces.back());

    pieces.push_back(new Spears(Player::player2));
    hexMap->setPiece(8,1,pieces.back());

    pieces.push_back(new Mountain(Player::player2));
    hexMap->setPiece(7,3,pieces.back());
}

bool GameLogic::isGameOver(void){

    bool isKingPlayer1 = false;
    bool isKingPlayer2 = false;

    for(auto i = pieces.begin(); i<pieces.end(); ++i) {

        if((*i)->getType() == Type::king && (*i)->getPlayer() == Player::player1)
            isKingPlayer1 = true;

        if((*i)->getType() == Type::king && (*i)->getPlayer() == Player::player2)
            isKingPlayer2 = true;
    }

    if(isKingPlayer1 &&  isKingPlayer2)
        return false;
    else
        return true;
}


void GameLogic::mapClicked(int xPixel, int yPixel) {

    resetMap();

    int x = getX(xPixel, yPixel);
    int y = getY(xPixel, yPixel);

    if(outOfBounds(x,y)) {
        selectedHex = nullptr;
        return;
    }

    Hex* hexClicked = hexMap->getHexPnt(x,y);

    // if nothing selected
    if(!selectedHex){

        // if clicked on an empty space, a mountain or an enemy
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
        else if(canMove(selectedHex, hexClicked)){
            movePiece(selectedHex, hexClicked);
            selectedHex = nullptr;
            enemyMove();
        }

        // if clicked some where cannot be moved
        else{
            selectedHex = nullptr;
        }
    }


    if(isGameOver()){
        exit(0);
    }

}


void GameLogic::enemyMove(void){

    std::vector<HexCoordinates> movements;
    bool moved = false;

    while(!moved){

        int x = rand() % width;
        int y = rand() % height;

        Hex* hex = hexMap->getHexPnt(x,y);

        // if it has a piece && is not a mountain && is other player
        if(hex->hasPiece() && !hex->getPiece()->isMoutain() && hex->getPiece()->getPlayer() == Player::player2){

            if(hex->getPiece()->getMoveType() == Movement::orthogonal){
                movements = hex->getPossibleOrthogonalSteps(hex->getPiece()->getRange());
            }
            else if(hex->getPiece()->getMoveType() == Movement::diagonal){
               movements = hex->getPossibleDiagonalSteps(hex->getPiece()->getRange());
            }
            else{
                exit(0);
            }

            for(auto i = movements.begin(); i<movements.end(); ++i) {

                int xNew = (*i).getCartesianX();
                int yNew = (*i).getCartesianY();

                if(outOfBounds(xNew,yNew))
                    continue;

                if(canMove(hex, hexMap->getHexPnt(xNew,yNew))){
                    movePiece(hex, hexMap->getHexPnt(xNew,yNew));
                    moved = true;
                    break;
                }
            }
        }
    }

    if(isGameOver()){
        exit(0);
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


bool GameLogic::canMove(Hex* sourceHex, Hex* targetHex){

    std::vector<HexCoordinates> steps;

    if(sourceHex == targetHex)
        return false;

    else if(outOfBounds(targetHex->getCartesianX(), targetHex->getCartesianY()))
        return false;

    else if(outOfBounds(sourceHex->getCartesianX(), sourceHex->getCartesianY()))
        return false;

    else if(!sourceHex->hasPiece())
        return false;

    Movement moveType = sourceHex->getPiece()->getMoveType();

    // if the movement type is orthogonal and the two hexes are in orthogonal range
    if(moveType == Movement::orthogonal && sourceHex->isOrthogonalRange(*targetHex, sourceHex->getPiece()->getRange())){
       steps = sourceHex->orthogonalSteps(*targetHex);
    }

    // if the movement type is diagonal and the two hexes are in diagonal range
    else if(moveType == Movement::diagonal && sourceHex->isDiagonalRange(*targetHex, sourceHex->getPiece()->getRange())){
        steps = sourceHex->diagonalSteps(*targetHex);
    }
    else{
        return false;
    }

    // check all the steps to targetHex are clear
    for(auto i = steps.begin(); i!=steps.end()-1; ++i) {

        if(outOfBounds((*i).getCartesianX(), (*i).getCartesianY())){
            return false;
        }
        if( hexMap->hasPiece((*i).getCartesianX(), (*i).getCartesianY()) ){
            return false;
        }
    }

    // check if the target is clear
    if(!targetHex->hasPiece())
        return true;

    // if target contains opponent which is not a moutain
    else if(sourceHex->getPiece()->getPlayer() != targetHex->getPiece()->getPlayer() && !targetHex->getPiece()->isMoutain())
        return true;

    else
        return false;
}

void GameLogic::movePiece(Hex* sourceHex, Hex* targetHex){

    pieces.erase(std::remove(pieces.begin(), pieces.end(), targetHex->getPiece()), pieces.end());
    hexMap->movePeice(sourceHex, targetHex);
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
