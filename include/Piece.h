#ifndef PIECE_H
#define PIECE_H

#include <iostream>

enum class Player{player1, player2};
enum class Type{king,rabble,mountain,spears,crossbow};
enum class MoveType{orthogonal,none,diagonal};
enum class Terrain{hill,forest,grassland,fortresses,none};


class Piece
{
    public:
        Piece(Player _player, Type _type, MoveType _movement, Terrain _terrainBonus, int _range, int tier, int value);
        virtual ~Piece();

        MoveType getMoveType(void);
        Player getPlayer(void);
        Terrain getBonusTerrain(void) const;
        int getRange(void);

        bool isMoutain(void);
        Type getType(void) const;

        int getTier(void) const;
        int getValue(void) const;

    protected:

        Player player;
        Type type;
        MoveType movetype;
        Terrain terrainBonus;
        int range;
        int tier;
        int value;

    private:
};



#endif // PIECE_H
