#include "GameLogic.h"

GameLogic::GameLogic(int _mapHexSize): hexMap{HexMap(_mapHexSize)}
{
    srand (time(NULL));
    gameState = GameState::player1Turn;
    gameState = GameState::placement;
}

GameLogic::~GameLogic() {
    //delete hexMap;
}

GameState GameLogic::getGameState(void){
    return gameState;
}

HexMap GameLogic::getHexMap() const{
    return hexMap;
}

void GameLogic::mapClicked(int x, int y) {

    int depth;

    if(hexMap.getNumPieces() < 12)
        depth = 2;
    else
        depth = 2;

    if(gameState == GameState::player1Turn){
        //player1Move(x, y);
        AI::miniMaxMove(&hexMap, Player::player1, depth);
        gameState = GameState::player2Turn;
    }
    else if(gameState == GameState::placement)
        player1placement(x, y);
    else if(gameState == GameState::player2Turn){
        AI::miniMaxMove(&hexMap, Player::player2, depth);
        gameState = GameState::player1Turn;
        //enemyMove();
    }

}

void GameLogic::player1placement(int x, int y){

    if(hexMap.isOffBoard(x,y) || !hexMap.isInPlayerhalf(Player::player1, y)) {
        hexMap.setSelectedHex(nullptr);
        return;
    }

    Hex* hexClicked = hexMap.getHexPnt(x,y);

    // if nothing selected
    if(!hexMap.isHexSelected()){

        // if clicked on an empty space
        if(!hexClicked->hasPiece()){
            hexMap.setSelectedHex(nullptr);
        }
        // else if is moveable player unit
        else{
            hexMap.setSelectedHex(hexClicked->getCartesianX(), hexClicked->getCartesianY());
        }
    }
    // if something is already selected
    else{

        if(!hexClicked->hasPiece()){
            hexMap.movePeice(hexMap.getSelectedHex(), *hexClicked);
        }

        hexMap.setSelectedHex(nullptr);
    }
}

void GameLogic::endPlacement(void){
    gameState = GameState::player1Turn;
    hexMap.placeTerrain();
}


void GameLogic::player1Move(int x, int y){
/*
    Move _move = AI::miniMaxMove(hexMap, 3);
    hexMap.movePeice(_move.startX, _move.startY, _move.endX, _move.endY);

    gameState = GameState::player2Turn;

    return;
*/
    resetMap();

    if(hexMap.isOffBoard(x,y)) {
        hexMap.setSelectedHex(nullptr);
        return;
    }

    Hex* hexClicked = hexMap.getHexPnt(x,y);

    // if nothing selected
    if(!hexMap.isHexSelected()){
    //if(!selectedHex){

        // if clicked on an empty space, a mountain or an enemy
        if(!hexClicked->hasPiece() || hexClicked->getPiece()->isMoutain() || hexClicked->getPiece()->getPlayer() != Player::player1){
            hexMap.setSelectedHex(nullptr);
        }
        // else if is moveable player unit
        else{
            hexMap.setSelectedHex(hexClicked->getCartesianX(), hexClicked->getCartesianY());
        }
    }
    // if something is already selected
    else{

        // if clicked currently selected
        if(hexMap.getSelectedHex().equals(*hexClicked)){

            showMovements(*hexClicked);
        }
        else{

            bool playerMoved = playerMove(hexMap.getSelectedHex(), *hexClicked);

            if(playerMoved){
                gameState = GameState::player2Turn;
            }

            hexMap.setSelectedHex(nullptr);

        }
    }
}





bool GameLogic::playerMove(Hex sourceHex, Hex destinationHex){

    bool PlayerMoved;

    if(Movement::canMove(hexMap, sourceHex, destinationHex)){
        hexMap.movePeice(sourceHex, destinationHex);
        PlayerMoved = true;
    }
    else{
        PlayerMoved = false;
    }

    return PlayerMoved;
}

void GameLogic::enemyMove(void){

    //Move _move = AI::randomMove(hexMap);
    AI::miniMaxMove(&hexMap, Player::player2, 3);


    gameState = GameState::player1Turn;
}


void GameLogic::deselect(void){
    hexMap.setSelectedHex(nullptr);
    resetMap();
}


void GameLogic::showMovements(Hex hex){

    //std::vector<Hex> movements = getPossibleMovements(hexMap, hex);
    std::vector<Hex> movements = Movement::getValidMovements(hexMap, hex);

    for(auto i = movements.begin(); i<movements.end(); ++i) {
          hexMap.addHighlightedHexes((*i));
    }
}




void GameLogic::resetMap(void) {
    hexMap.clearHighlightedHexes();
}


int GameLogic::getX(int pixelX, int pixelY) {

    int xPos;
    int hexSize = 30;
    double hexHeight = 2 * hexSize;
    double hexWidth = hexHeight * (sqrt(3) / 2);


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
    int hexSize = 30;
    double hexHeight = 2 * hexSize;

    yPos = (pixelY + (hexSize*0.5))/ (hexHeight*0.75);

    return yPos;
}
