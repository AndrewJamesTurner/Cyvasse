#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Hex.h"
#include "HexMap.h"

#include <random>
#include <vector>
#include <climits>

enum class GameState{setUp,player1Turn,player2Turn,player1Won,player2Won};

struct Move{

  int startX;
  int startY;

  int endX;
  int endY;


  Move(int _startX, int _startY, int _endX, int _endY) : startX(_startX), startY(_startY), endX{_endX}, endY{_endY}{}
};


class GameLogic
{
    public:
        GameLogic(int _mapHexSize);
        virtual ~GameLogic();

        GameState getGameState(void);
        void enemyMove(void);

        void mapClicked(int xPixel, int yPixel);
        void update(void);
        void deselect(void);
        void resetMap(void);

        HexMap getHexMap() const;




    protected:

    private:

        Hex* selectedHex;

        int mapHexSize;

        HexMap hexMap;

        GameState gameState;

        std::random_device rd;

        int getX(int pixelX, int pixelY);
        int getY(int pixelX, int pixelY);

        bool playerMove(Hex sourceHex, Hex destinationHex);

        bool inRangeAny(int row1, int col1, int row2, int col2, int range);
        bool inRangeAny(int x1, int y1, int z1, int x2, int y2, int z2, int range);

        bool canMove(HexMap _hexmap, Hex sourceHex, Hex targetHex);

        void populateBoard(void);

        void showMovements(Hex hex);
        std::vector<Hex> getPossibleMovements(const HexMap& _hexMap, const Hex& hex);
        std::vector<Hex> getValidMovements(const HexMap& _hexMap, const Hex& hex);
        std::vector<Move> getPossibleMoves(const HexMap& _hexMap, const Player& player);

        bool isGameOver(const HexMap& _map);

        int getHeuristicBoardScore(const HexMap& _map, const Player& player);

        Move randomMove(const HexMap& _map);
        Move miniMaxMove(const HexMap&, int depth);
        int miniMax(const HexMap& _map, int depth, int alpha, int beta, Player maximizingPlayer);

};

#endif // GAMELOGIC_H
