#include "AI.h"

AI::AI()
{
    //ctor
}

AI::~AI()
{
    //dtor
}

void AI::miniMaxMove(HexMap* hexMap, Player player, int depth){

    int alpha = INT_MIN;
    int beta = INT_MAX;

    Player opponent;

    if( player == Player::player1)
        opponent = Player::player2;
    else
        opponent = Player::player1;

    std::vector<Move> possibleMoves = Movement::getPossibleMoves(*hexMap, player);

    int bestScore = INT_MIN;
    Move bestMove = possibleMoves[0];

    for(auto i = possibleMoves.begin(); i<possibleMoves.end(); ++i) {

        HexMap tmpMap = *hexMap;
        tmpMap.movePeice((*i).startX, (*i).startY, (*i).endX, (*i).endY);

        // -1 for the first loop done for player two
        int score = AI::miniMax(tmpMap, depth-1, alpha, beta, player, opponent);

        //alpha = std::max(alpha, score);

        if(score > bestScore){
            bestScore = score;
            bestMove = Move((*i).startX, (*i).startY, (*i).endX, (*i).endY);
        }
    }

    hexMap->movePeice(bestMove.startX, bestMove.startY, bestMove.endX, bestMove.endY);
}



int AI::miniMax(const HexMap& _map, int depth, int alpha, int beta, Player maximizingPlayer, Player player){

    Player opponent;

    if( player == Player::player1)
        opponent = Player::player2;
    else
        opponent = Player::player1;

    if( depth <= 0 || !_map.isBothKingsOnBoard() ){
        return getHeuristicBoardScore(_map, player);
    }

    if(player == maximizingPlayer){

        int score = INT_MIN;
        std::vector<Move> possibleMoves = Movement::getPossibleMoves(_map, player);

        for(auto i = possibleMoves.begin(); i<possibleMoves.end(); ++i) {

            HexMap tmpMap = _map;
            tmpMap.movePeice((*i).startX, (*i).startY, (*i).endX, (*i).endY);

            score = std::max(score, miniMax(tmpMap, depth-1, alpha, beta, maximizingPlayer, opponent));
            //alpha = std::max(alpha, score);

            //if(beta < alpha)
            //    break;
        }

         return score;
    }
    else{

        int score = INT_MAX;
        std::vector<Move> possibleMoves = Movement::getPossibleMoves(_map, player);

        for(auto i = possibleMoves.begin(); i<possibleMoves.end(); ++i){

            HexMap tmpMap = _map;
            tmpMap.movePeice((*i).startX, (*i).startY, (*i).endX, (*i).endY);

            score = std::min(score, miniMax(tmpMap, depth-1, alpha, beta, maximizingPlayer, opponent));
            beta = std::min(beta, score);

            //if(beta < alpha)
            //    break;
        }

         return score;
    }
}

int AI::getHeuristicBoardScore(const HexMap& _map, const Player& player){

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

void AI::randomMove(HexMap* hexMap, Player player){

    std::vector<Move> possibleMoves = Movement::getPossibleMoves(*hexMap, player);

    unsigned int numPossibleMoves = possibleMoves.size();
    unsigned int randMove = rand() % numPossibleMoves;

    Move nextMove(possibleMoves[randMove].startX, possibleMoves[randMove].startY, possibleMoves[randMove].endX, possibleMoves[randMove].endY);

    hexMap->movePeice(nextMove.startX, nextMove.startY, nextMove.endX, nextMove.endY);
}
