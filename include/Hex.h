#ifndef HEX_H
#define HEX_H

#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "HexCoordinates.h"

class Hex
{
    public:
        Hex(int _cartesianX, int _cartesianY, int _hexSize, sf::Color color);
        virtual ~Hex();



        sf::CircleShape getShape(void);

        void setColor(sf::Color color);

        Piece* getPiece(void);
        bool hasPiece(void);
        void setPiece(Piece* _piece);
        void clearPiece(void);

        void draw(sf::RenderWindow *window);

        bool isOrthogonal(Hex hex);

        HexCoordinates* getCoordinates(void);

    private:


        sf::CircleShape shape;
        Piece* piece;
        HexCoordinates* coordinates;

        float pixelX;
        float pixelY;

        float hexSize;
        float hexHeight;
        float hexWidth;



        int getPixelX(void);
        int getPixelY(void);

        void setPixelX(void);
        void setPixelY(void);
};

#endif // HEX_H
