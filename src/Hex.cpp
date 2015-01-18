#include "Hex.h"

Hex::Hex(int xPos, int yPos, int hexSize, sf::Color color)
{
    shape = sf::CircleShape(hexSize,6);
    shape.setPosition(xPos, yPos);
    shape.setOutlineThickness(5);
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color::Black);
}

Hex::~Hex()
{
    //dtor
}


sf::CircleShape Hex::getShape(void){
    return shape;
}


void Hex::setColor(sf::Color color){
    shape.setFillColor(color);
}
