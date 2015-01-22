#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>

enum class movement{orthogonal};

class Piece
{
    public:
        Piece();
        virtual ~Piece();

        sf::Sprite getSprite(void);

        void setPosition(float _xPos, float _yPos);
        movement getMoveType(void);

    protected:

    private:

        sf::Texture texture;
        sf::Sprite sprite;
        movement movetype;
};

#endif // PIECE_H
