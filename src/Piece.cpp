#include "Piece.h"

Piece::Piece(Player _player, Type _type, Movement _movement, int _range, std::string _textureName)
{
    player = _player;
    type = _type;
    movetype = _movement;
    range = _range;
    textureName = _textureName;

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

Type Piece::getType(void) const {
    return type;
}

sf::Sprite Piece::getSprite(void){
    return sprite;
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
