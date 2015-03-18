#ifndef HEX_H
#define HEX_H

#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "HexCoordinates.h"

class Hex : public HexCoordinates
{
    public:
        Hex(int _cartesianX, int _cartesianY, int _hexSize, sf::Color _color);

        bool operator== (const Hex& a) const;


        sf::CircleShape getShape(void);

        void setColor(sf::Color _color);
        void setBoarderColor(sf::Color _color);

        Piece* getPiece(void) const;
        bool hasPiece(void) const;
        void setPiece(Piece* _piece);
        void clearPiece(void);
        //void deletePiece(void);

        void draw(sf::RenderWindow *window);

        bool isPlayer(Player player) const;

        Type getType(void) const;


    private:

        sf::CircleShape shape;
        Piece* piece;

        float pixelX;
        float pixelY;

        float hexSize;
        float hexHeight;
        float hexWidth;

        sf::Color color;

        int getPixelX(void);
        int getPixelY(void);

        void setPixelX(void);
        void setPixelY(void);
};

#endif // HEX_H
