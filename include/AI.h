#ifndef AI_H
#define AI_H

#include <climits>

#include "HexMap.h"
#include "Movement.h"

enum class Difficulty{veryEasy,easy,medium,hard};


class AI
{
    public:
        AI();
        virtual ~AI();

        static void AImove(HexMap* hexMap, Player player, Difficulty difficulty);


    protected:

    private:

        static void randomMove(HexMap* hexMap, Player player);
        static void miniMaxMove(HexMap* hexMap, Player player, int depth);

        static int getHeuristicBoardScore(const HexMap& _map, const Player& player);
        static int miniMax(const HexMap& _map, int depth, int alpha, int beta, Player maximizingPlayer, Player player);
};

#endif // AI_H
