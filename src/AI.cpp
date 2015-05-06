#include "AI.h"

AI::AI()
{
    //ctor
}

AI::~AI()
{
    //dtor
}

Move AI::miniMaxMove(const HexMap& _map, int depth){

    int alpha = INT_MIN;
    int beta = INT_MAX;

    std::vector<Move> possibleMoves = Movement::getPossibleMoves(_map, Player::player2);

    int bestScore = INT_MIN;
    Move bestMove = possibleMoves[0];

    for(auto i = possibleMoves.begin(); i<possibleMoves.end(); ++i) {

        HexMap tmpMap = _map;
        tmpMap.movePeice((*i).startX, (*i).startY, (*i).endX, (*i).endY);

        // -1 for the first loop done for player two
        int score = AI::miniMax(tmpMap, depth-1, alpha, beta, Player::player1);

        alpha = std::max(alpha, score);

        if(score > bestScore){
            bestScore = score;
            bestMove = Move((*i).startX, (*i).startY, (*i).endX, (*i).endY);
        }
    }

    return bestMove;
}



int AI::miniMax(const HexMap& _map, int depth, int alpha, int beta, Player player){

    if( depth <= 0 || _map.isBothKingsOnBoard() ){
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

Move AI::randomMove(const HexMap& _map){

    std::vector<Move> possibleMoves = Movement::getPossibleMoves(_map, Player::player2);

    unsigned int numPossibleMoves = possibleMoves.size();
    unsigned int randMove = rand() % numPossibleMoves;

    Move nextMove(possibleMoves[randMove].startX, possibleMoves[randMove].startY, possibleMoves[randMove].endX, possibleMoves[randMove].endY);

    return nextMove;
}
