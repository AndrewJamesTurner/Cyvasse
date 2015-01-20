#include "Hex.h"

Hex::Hex(int _xPos, int _yPos, int hexSize, sf::Color color)
{
    xPos = _xPos;
    yPos = _yPos;

    shape = sf::CircleShape(hexSize,6);
    shape.setPosition(xPos, yPos);
    shape.setOutlineThickness(5);
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color::Black);

    piece = nullptr;
}

Hex::~Hex()
{
    //dtor
}

void Hex::draw(sf::RenderWindow *window){

    window->draw(shape);

    if(getPiece()){

        sf::Sprite sprite = piece->getSprite();
        window->draw(sprite);
    }
}

sf::CircleShape Hex::getShape(void){
    return shape;
}


void Hex::setColor(sf::Color color){
    shape.setFillColor(color);
}


Piece* Hex::getPiece(void){
    return piece;
}


void Hex::setPiece(Piece* _piece){
    piece = _piece;
    piece->setPosition(xPos,yPos);
}

void Hex::clearPiece(void){
    piece = nullptr;
}
