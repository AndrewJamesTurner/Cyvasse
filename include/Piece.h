#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <iostream>

enum class Player{player1, player2};
enum class Type{king,rabble,mountain,spears};
enum class Movement{orthogonal,none,diagonal};

class Piece
{
    public:
        Piece(Player _player, Type _type, Movement _movement, int _range, std::string textureName);
        virtual ~Piece();

        sf::Sprite getSprite(void);

        void setPosition(float _xPos, float _yPos);

        Movement getMoveType(void);
        Player getPlayer(void);
        int getRange(void);

        bool isMoutain(void);

    protected:

        sf::Texture texture;
        sf::Sprite sprite;

        Movement movetype;
        Player player;
        Type type;
        int range;

    private:


};

#endif // PIECE_H
