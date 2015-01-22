#include "Hex.h"

Hex::Hex(int _cartesianX, int _cartesianY, int _hexSize, sf::Color color)
{
    coordinates = new HexCoordinates(_cartesianX,_cartesianY);

    hexSize = _hexSize;
    hexHeight = 2 * hexSize;
    hexWidth = hexHeight * (sqrt(3) / 2);

    setPixelX();
    setPixelY();

    shape = sf::CircleShape(hexSize,6);
    shape.setPosition(pixelX, pixelY);
    shape.setOutlineThickness(-1);
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color::Black);

    piece = nullptr;
}

Hex::~Hex()
{
    //delete coordinates;
}

bool Hex::isOrthogonal(Hex hex){

    return coordinates->isOrthogonal(*hex.coordinates);
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
    piece->setPosition(pixelX+(hexSize*(sqrt(3) / 2)) + hexSize - hexSize*cos(0.5236),pixelY+hexSize);
}

void Hex::clearPiece(void){
    piece = nullptr;
}



void Hex::setPixelX(void){

     if(coordinates->getCartesianY() % 2 == 0)
        pixelX = coordinates->getCartesianX()*hexWidth - (hexWidth*0.5);
    else
       pixelX = (coordinates->getCartesianX()*hexWidth);
}

void Hex::setPixelY(void){

    pixelY = coordinates->getCartesianY()*hexHeight*0.75;
}

int Hex::getPixelX(void){
     return pixelX;
}

int Hex::getPixelY(void){
    return pixelY;
}
