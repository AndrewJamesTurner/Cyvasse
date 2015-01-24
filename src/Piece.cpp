#include "Piece.h"

Piece::Piece(Player _player, Type _type)
{
    if (!texture.loadFromFile("Images/King.png")){
        // error...
    }

    player = _player;
    type = _type;
    movetype = Movement::orthogonal;




    sprite.setTexture(texture);
    sf::FloatRect textureRect = sprite.getLocalBounds();
    sprite.setScale(sf::Vector2f(0.5f, 0.5f));

    sprite.setOrigin(textureRect.left + textureRect.width/2.0f, textureRect.top  + textureRect.height/2.0f);

    if(player == Player::player1)
        sprite.setColor(sf::Color::Black);
    else
        sprite.setColor(sf::Color::White);
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

Movement Piece::getMoveType(void){
    return movetype;
}

Player Piece::getPlayer(void){
    return player;
}
