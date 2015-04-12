#ifndef PIECE_H
#define PIECE_H

#include <iostream>

enum class Player{player1, player2};
enum class Type{king,rabble,mountain,spears};
enum class Movement{orthogonal,none,diagonal};

class Piece
{
    public:
        Piece(Player _player, Type _type, Movement _movement, int _range);
        virtual ~Piece();

        Movement getMoveType(void);
        Player getPlayer(void);
        int getRange(void);

        bool isMoutain(void);
        Type getType(void) const;

    protected:

        Movement movetype;
        Player player;
        Type type;
        int range;

    private:
};



#endif // PIECE_H
