#ifndef HEX_H
#define HEX_H

#include <SFML/Graphics.hpp>
#include "Piece.h"

class Hex
{
    public:
        Hex(int _xPos, int _yPos, int hexSize, sf::Color color);
        virtual ~Hex();

        sf::CircleShape getShape(void);

        void setColor(sf::Color color);

        Piece* getPiece(void);
        void setPiece(Piece* _piece);
        void clearPiece(void);

        void draw(sf::RenderWindow *window);

    protected:
    private:

    sf::CircleShape shape;
    Piece* piece;

    float xPos;
    float yPos;
};

#endif // HEX_H
