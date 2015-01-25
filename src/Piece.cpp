#include "Piece.h"

Piece::Piece(Player _player, Type _type)
{

    player = _player;
    type = _type;

    switch(type){

        case Type::rabble:
            if (!texture.loadFromFile("Images/Rabble.png"))
                exit(0);
            movetype = Movement::orthogonal;
            range = 3;
            break;
        case Type::king:
            if (!texture.loadFromFile("Images/King.png"))
                exit(0);
            movetype = Movement::orthogonal;
            range = 1;
            break;
        case Type::mountain:
            if (!texture.loadFromFile("Images/Mountain.png"))
                exit(0);
            movetype = Movement::none;
            range = 0;
            break;
        case Type::spears:
            if (!texture.loadFromFile("Images/Spears.png"))
                exit(0);
            movetype = Movement::diagonal;
            range = 2;
            break;
        default:
            std::cerr << "Piece type not known...\n";
            exit(0);
    }




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
