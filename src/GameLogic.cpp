#include "GameLogic.h"

GameLogic::GameLogic(sf::RenderWindow *_window, double _hexSize, int _mapHexSize):
    window{_window},
    hexSize{_hexSize},
    width{2*_mapHexSize+1},
    height{2*_mapHexSize+1},
    mapHexSize{_mapHexSize},
    hexMap{HexMap(hexSize,mapHexSize)},
    hexHeight{2 * hexSize},
    hexWidth{hexHeight * (sqrt(3) / 2)}{

    srand (time(NULL));

    selectedHex = nullptr;

    resetMap();

    gameState = GameState::player1Turn;
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

void GameLogic::mapClicked(int xPixel, int yPixel) {

    resetMap();

    int x = getX(xPixel, yPixel);
    int y = getY(xPixel, yPixel);

    if(hexMap.isOffBoard(x,y)) {
        selectedHex = nullptr;
        return;
    }

    Hex* hexClicked = hexMap.getHexPnt(x,y);

    // if nothing selected
    if(!selectedHex){

        // if clicked on an empty space, a mountain or an enemy
        if(!hexClicked->hasPiece() || hexClicked->getPiece()->isMoutain() || hexClicked->getPiece()->getPlayer() != Player::player1){
            selectedHex = nullptr;
            hexMap.setSelectedHex(nullptr);
        }
        // else if is moveable player unit
        else{
            hexClicked->setBoarderColor(sf::Color::Yellow);
            selectedHex = hexClicked;
            hexMap.setSelectedHex(hexClicked->getCartesianX(), hexClicked->getCartesianY());
        }
    }
    // if something is already selected
    else{

        // if clicked currently selected
        if(selectedHex == hexClicked){
            hexClicked->setBoarderColor(sf::Color::Yellow);
            showMovements(*hexClicked);
        }
        else{

            bool playerMoved = playerMove(*selectedHex, *hexClicked);

            if(playerMoved){
                gameState = GameState::player2Turn;
            }

            selectedHex = nullptr;
            hexMap.setSelectedHex(nullptr);
        }
    }
}


std::vector<Move> GameLogic::getPossibleMoves(const HexMap& _hexMap, const Player& player){

    std::vector<Move> possibleMoves;
    std::vector<Hex> playerPositions = _hexMap.getPlayerPositions(player);

    for(auto i = playerPositions.begin(); i<playerPositions.end(); ++i) {

        std::vector<Hex> validMoves = getValidMovements(_hexMap, (*i));

        for(auto j = validMoves.begin(); j<validMoves.end(); ++j) {
            Move _move((*i).getCartesianX(), (*i).getCartesianY(), (*j).getCartesianX(), (*j).getCartesianY());
            possibleMoves.push_back(_move);
        }
    }

    return possibleMoves;
}


bool GameLogic::playerMove(Hex sourceHex, Hex destinationHex){

    bool PlayerMoved;

    if(canMove(hexMap, sourceHex, destinationHex)){
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

    std::vector<Move> possibleMoves = getPossibleMoves(_map, Player::player2);

    unsigned int numPossibleMoves = possibleMoves.size();
    unsigned int randMove = rand() % numPossibleMoves;

    Move nextMove(possibleMoves[randMove].startX, possibleMoves[randMove].startY, possibleMoves[randMove].endX, possibleMoves[randMove].endY);

    return nextMove;
}

Move GameLogic::miniMaxMove(const HexMap& _map, int depth){

    int alpha = INT_MIN;
    int beta = INT_MAX;

    std::vector<Move> possibleMoves = getPossibleMoves(_map, Player::player2);

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
        std::vector<Move> possibleMoves = getPossibleMoves(_map, player);

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
        std::vector<Move> possibleMoves = getPossibleMoves(_map, player);

        for(auto i = possibleMoves.begin(); i<possibleMoves.end(); ++i) {

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

    int numPlayer1 = player1Positions.size();
    int numPlayer2 = player2Positions.size();

    if(player == Player::player1){
        return numPlayer1 - numPlayer2;
    }
    else{
        return numPlayer2 - numPlayer1;
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
    selectedHex = nullptr;
    hexMap.setSelectedHex(nullptr);
    resetMap();
}

std::vector<Hex> GameLogic::getPossibleMovements(const HexMap& _hexMap, const Hex& hex){

    std::vector<HexCoordinates> movements;
    std::vector<Hex> possibleMovements;

    if(hex.getPiece()->getMoveType() == Movement::orthogonal){
        movements = hex.getPossibleOrthogonalSteps(hex.getPiece()->getRange());
    }
    else if(hex.getPiece()->getMoveType() == Movement::diagonal){
       movements = hex.getPossibleDiagonalSteps(hex.getPiece()->getRange());
    }

    for(auto i = movements.begin(); i<movements.end(); ++i) {

        int x = (*i).getCartesianX();
        int y = (*i).getCartesianY();

        if(hexMap.isOnBoard(x,y))
            possibleMovements.push_back(_hexMap.getHex(x,y));
    }

    return possibleMovements;
}

std::vector<Hex> GameLogic::getValidMovements(const HexMap& _hexMap, const Hex& hex){

    std::vector<Hex> validMovements;
    std::vector<Hex> possibleMovements = getPossibleMovements(_hexMap, hex);

    for(auto i = possibleMovements.begin(); i<possibleMovements.end(); ++i) {

        if(canMove(_hexMap, hex, (*i)))
            validMovements.push_back((*i));
    }

    return validMovements;
}


void GameLogic::showMovements(Hex hex){

    std::vector<Hex> movements = getPossibleMovements(hexMap, hex);

    for(auto i = movements.begin(); i<movements.end(); ++i) {
        hexMap.setColor((*i).getCartesianX(),(*i).getCartesianY(),sf::Color(230,0,0));
    }
}


bool GameLogic::canMove(HexMap _hexmap, Hex sourceHex, Hex targetHex){

    std::vector<HexCoordinates> steps;

    if(sourceHex.getCartesianX() == targetHex.getCartesianX() && sourceHex.getCartesianY() == targetHex.getCartesianY())
        return false;

    else if(hexMap.isOffBoard(targetHex.getCartesianX(), targetHex.getCartesianY()))
        return false;

    else if(hexMap.isOffBoard(sourceHex.getCartesianX(), sourceHex.getCartesianY()))
        return false;

    else if(!sourceHex.hasPiece())
        return false;

    Movement moveType = sourceHex.getPiece()->getMoveType();

    // if the movement type is orthogonal and the two hexes are in orthogonal range
    if(moveType == Movement::orthogonal && sourceHex.isOrthogonalRange(targetHex, sourceHex.getPiece()->getRange())){
       steps = sourceHex.orthogonalSteps(targetHex);
    }

    // if the movement type is diagonal and the two hexes are in diagonal range
    else if(moveType == Movement::diagonal && sourceHex.isDiagonalRange(targetHex, sourceHex.getPiece()->getRange())){
        steps = sourceHex.diagonalSteps(targetHex);
    }
    else{
        return false;
    }

    // check all the steps to targetHex are clear
    for(auto i = steps.begin(); i!=steps.end()-1; ++i) {

        if(hexMap.isOffBoard((*i).getCartesianX(), (*i).getCartesianY())){
            return false;
        }
        if( _hexmap.hasPiece((*i).getCartesianX(), (*i).getCartesianY()) ){
            return false;
        }
    }

    // check if the target is clear
    if(!targetHex.hasPiece())
        return true;

    // if target contains opponent which is not a mountain
    else if(sourceHex.getPiece()->getPlayer() != targetHex.getPiece()->getPlayer() && !targetHex.getPiece()->isMoutain())
        return true;

    else
        return false;
}

void GameLogic::resetMap(void) {

    HexCoordinates centerHex(mapHexSize, mapHexSize);

    for(int x = 0; x<width; x++) {
        for(int y = 0; y<height; y++) {

            HexCoordinates currentHex(x, y);

            if(centerHex.isInRange(currentHex, mapHexSize)){
                hexMap.setColor(x,y,sf::Color(17,220,51));
            }
            else {
                hexMap.setColor(x,y,sf::Color(20,20,230));
            }

            hexMap.setBoarderColor(x,y,sf::Color::Black);
        }
    }
}


void GameLogic::update(void) {

    std::vector<Hex> hexes = hexMap.getHexes();

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


