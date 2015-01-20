#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>

class Piece
{
    public:
        Piece();
        virtual ~Piece();

        sf::Sprite getSprite(void);

        void setPosition(float _xPos, float _yPos);

    protected:

    private:

        sf::Texture texture;
        sf::Sprite sprite;
};

#endif // PIECE_H
