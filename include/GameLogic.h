#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Hex.h"
#include "HexMap.h"

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <climits>

enum class GameState{setUp,player1Turn,player2Turn,player1Won,player2Won};


struct Move{

  Hex* sourceHex;
  Hex* destinationHex;

  int score;

  Move(Hex* _sourceHex, Hex* _destinationHex) : sourceHex(_sourceHex), destinationHex(_destinationHex){}
};


class GameLogic
{
    public:
        GameLogic(sf::RenderWindow *_window, float _hexSize, int _mapHexSize);
        virtual ~GameLogic();

        GameState getGameState(void);
        void enemyMove(void);


        void mapClicked(int xPixel, int yPixel);
        void update(void);
        void deselect(void);
        void resetMap(void);

    protected:

    private:

        sf::RenderWindow *window;
        HexMap* hexMap;
        Hex* selectedHex;

        float hexSize;
        float hexHeight;
        float hexWidth;

        int width;
        int height;
        int mapHexSize;

        GameState gameState;

        std::random_device rd;

        int getX(int pixelX, int pixelY);
        int getY(int pixelX, int pixelY);


        bool playerMove(Hex* sourceHex, Hex* destinationHex);


        bool inRangeAny(int row1, int col1, int row2, int col2, int range);
        bool inRangeAny(int x1, int y1, int z1, int x2, int y2, int z2, int range);

        bool outOfBounds(int x, int y);
        bool canMove(HexMap _hexmap, Hex sourceHex, Hex targetHex);

        void populateBoard(void);

        void showMovements(Hex* hex);
        std::vector<Hex> getPossibleMovements(HexMap _hexMap, Hex hex);
        std::vector<Hex> getValidMovements(HexMap _hexMap, Hex hex);
        std::vector<Move> getPossibleMoves(const HexMap& _hexMap, Player player);

        Move miniMax(HexMap _map, unsigned int depth, int alpha, int beta, Player maximizingPlayer);

        int getHeuristicBoardScore(HexMap _map, Player player);


        Move randomMove(const HexMap& _map, Player player);


};

#endif // GAMELOGIC_H
