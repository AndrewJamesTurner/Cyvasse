#ifndef PIECE_H
#define PIECE_H

#include <iostream>

enum class Player{player1, player2};
enum class Type{king,rabble,mountain,spears,crossbow};
enum class MoveType{orthogonal,none,diagonal};


class Piece
{
    public:
        Piece(Player _player, Type _type, MoveType _movement, int _range, int tier, int value);
        virtual ~Piece();

        MoveType getMoveType(void);
        Player getPlayer(void);
        int getRange(void);

        bool isMoutain(void);
        Type getType(void) const;

        int getTier(void) const;
        int getValue(void) const;

    protected:

        Player player;
        Type type;
        MoveType movetype;
        int range;
        int tier;
        int value;

    private:
};



#endif // PIECE_H
