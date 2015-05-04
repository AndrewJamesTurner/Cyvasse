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

    if(gameState == GameState::player1Turn)
        player1Move(x, y);
    else if(gameState == GameState::placement)
        player1placement(x, y);
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

    //Move _move = randomMove(hexMap);
    Move _move = miniMaxMove(hexMap, 3);
    hexMap.movePeice(_move.startX, _move.startY, _move.endX, _move.endY);

    gameState = GameState::player1Turn;
}

Move GameLogic::randomMove(const HexMap& _map){

    std::vector<Move> possibleMoves = Movement::getPossibleMoves(_map, Player::player2);

    unsigned int numPossibleMoves = possibleMoves.size();
    unsigned int randMove = rand() % numPossibleMoves;

    Move nextMove(possibleMoves[randMove].startX, possibleMoves[randMove].startY, possibleMoves[randMove].endX, possibleMoves[randMove].endY);

    return nextMove;
}

Move GameLogic::miniMaxMove(const HexMap& _map, int depth){

    int alpha = INT_MIN;
    int beta = INT_MAX;

    std::vector<Move> possibleMoves = Movement::getPossibleMoves(_map, Player::player2);

    int bestScore = INT_MIN;
    Move bestMove = possibleMoves[0];

    for(auto i = possibleMoves.begin(); i<possibleMoves.end(); ++i) {

        HexMap tmpMap = _map;
        tmpMap.movePeice((*i).startX, (*i).startY, (*i).endX, (*i).endY);

        // -1 for the first loop done for player two
        int score = miniMax(tmpMap, depth-1, alpha, beta, Player::player1);

        alpha = std::max(alpha, score);

        if(score > bestScore){
            bestScore = score;
            bestMove = Move((*i).startX, (*i).startY, (*i).endX, (*i).endY);
        }
    }

    return bestMove;
}

int GameLogic::miniMax(const HexMap& _map, int depth, int alpha, int beta, Player player){

    if(depth <= 0 || isGameOver(_map)){
        return getHeuristicBoardScore(_map, Player::player2);
    }

    if(player == Player::player2){

        int score = INT_MIN;
        std::vector<Move> possibleMoves = Movement::getPossibleMoves(_map, player);

        for(auto i = possibleMoves.begin(); i<possibleMoves.end(); ++i) {

            HexMap tmpMap = _map;
            tmpMap.movePeice((*i).startX, (*i).startY, (*i).endX, (*i).endY);

            score = std::max(score, miniMax(tmpMap, depth-1, alpha, beta, Player::player1));
            alpha = std::max(alpha, score);

            if(beta < alpha)
                break;
        }

         return score;
    }
    else{

        int score = INT_MAX;
        std::vector<Move> possibleMoves = Movement::getPossibleMoves(_map, player);

        for(auto i = possibleMoves.begin(); i<possibleMoves.end(); ++i){

            HexMap tmpMap = _map;
            tmpMap.movePeice((*i).startX, (*i).startY, (*i).endX, (*i).endY);

            score = std::min(score, miniMax(tmpMap, depth-1, alpha, beta, Player::player2));
            beta = std::min(beta, score);

            if(beta < alpha)
                break;
        }

         return score;
    }
}


int GameLogic::getHeuristicBoardScore(const HexMap& _map, const Player& player){

    std::vector<Hex> player1Positions = _map.getPlayerPositions(Player::player1);
    std::vector<Hex> player2Positions = _map.getPlayerPositions(Player::player2);

    int player1Score = 0;
    int player2Score = 0;

    for(auto i = player1Positions.begin(); i<player1Positions.end(); ++i){
        player1Score += (*i).getPiece()->getValue();
    }

    for(auto i = player2Positions.begin(); i<player2Positions.end(); ++i){
        player2Score += (*i).getPiece()->getValue();
    }

    if(player == Player::player1){
        return player1Score - player2Score;
    }
    else{
        return player2Score - player1Score;
    }
}

bool GameLogic::isGameOver(const HexMap& _map){

    bool player1King = false;
    bool player2King = false;

    std::vector<Hex> player1Positions = _map.getPlayerPositions(Player::player1);
    std::vector<Hex> player2Positions = _map.getPlayerPositions(Player::player2);

    for(auto i = player1Positions.begin(); i<player1Positions.end(); ++i) {

        if( (*i).getType() == Type::king){
            player1King = true;
            break;
        }
    }

    for(auto i = player2Positions.begin(); i<player2Positions.end(); ++i) {

        if( (*i).getType() == Type::king){
            player2King = true;
            break;
        }
    }

    if(player1King == false || player2King == false){
        return true;
    }
    else{
        return false;
    }
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
