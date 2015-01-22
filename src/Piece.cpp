#include "Piece.h"

Piece::Piece()
{
    if (!texture.loadFromFile("Images/King.png")){
        // error...
    }

    movetype = movement::orthogonal;

    sprite.setTexture(texture);
    sf::FloatRect textureRect = sprite.getLocalBounds();
    sprite.setScale(sf::Vector2f(0.5f, 0.5f));

    sprite.setOrigin(textureRect.left + textureRect.width/2.0f, textureRect.top  + textureRect.height/2.0f);


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

movement Piece::getMoveType(void){
    return movetype;
}
