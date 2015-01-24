#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>

enum class Player{player1, player2};
enum class Type{king};
enum class Movement{orthogonal};

class Piece
{
    public:
        Piece(Player _player, Type _type);
        virtual ~Piece();

        sf::Sprite getSprite(void);

        void setPosition(float _xPos, float _yPos);
        Movement getMoveType(void);

        Player getPlayer(void);

    protected:

    private:

        sf::Texture texture;
        sf::Sprite sprite;

        Movement movetype;
        Player player;
        Type type;
};

#endif // PIECE_H
