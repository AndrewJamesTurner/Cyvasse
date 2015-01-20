#include "Piece.h"

Piece::Piece()
{
    if (!texture.loadFromFile("Images/King.png")){
        // error...
    }

    sprite.setTexture(texture);
}

Piece::~Piece()
{
    //dtor
}


sf::Sprite Piece::getSprite(void){
    return sprite;
}


void Piece::setPosition(float xPos, float yPos){
   sprite.setPosition(xPos,yPos);
}

