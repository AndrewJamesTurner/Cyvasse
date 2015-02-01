#ifndef HEX_H
#define HEX_H

#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "HexCoordinates.h"

class Hex : public HexCoordinates
{
    public:
        Hex(int _cartesianX, int _cartesianY, int _hexSize, sf::Color color);
        virtual ~Hex();



        sf::CircleShape getShape(void);

        void setColor(sf::Color color);
        void setBoarderColor(sf::Color color);

        Piece* getPiece(void);
        bool hasPiece(void);
        void setPiece(Piece* _piece);
        void clearPiece(void);
        void deletePiece(void);

        void draw(sf::RenderWindow *window);



    private:


        sf::CircleShape shape;
        Piece* piece;


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
