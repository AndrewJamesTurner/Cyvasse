#include "Piece.h"

Piece::Piece(Player _player, Type _type, Movement _movement, int _range, std::string textureName)
{

    player = _player;
    type = _type;
    movetype = _movement;
    range = _range;

     if (!texture.loadFromFile(textureName))
        exit(0);

    sprite.setTexture(texture);
    sf::FloatRect textureRect = sprite.getLocalBounds();
    sprite.setScale(sf::Vector2f(0.5f, 0.5f));

    sprite.setOrigin(textureRect.left + textureRect.width/2.0f, textureRect.top  + textureRect.height/2.0f);

    if(player == Player::player1)
        sprite.setColor(sf::Color::Black);
    else
        sprite.setColor(sf::Color::White);
}

/*
    I think this is wrong.
*/
Piece::Piece(const Piece &other){

    texture = other.texture;//sf::Texture(other.texture);
    sprite = other.sprite;//sf::Sprite(other.sprite);
    movetype = other.movetype;
    player = other.player;
    type = other.type;
    range = other.range;
}

Piece::~Piece()
{
    //dtor
}

bool Piece::isMoutain(void){

    if(type == Type::mountain)
        return true;
    else
        return false;
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

 int Piece::getRange(void){
    return range;
 }
