#ifndef AI_H
#define AI_H

#include <climits>

#include "HexMap.h"
#include "Movement.h"

class AI
{
    public:
        AI();
        virtual ~AI();

        static Move randomMove(const HexMap& _map);
        static Move miniMaxMove(const HexMap&, int depth);

    protected:



    private:

        static int getHeuristicBoardScore(const HexMap& _map, const Player& player);
        static int miniMax(const HexMap& _map, int depth, int alpha, int beta, Player maximizingPlayer);
};

#endif // AI_H
