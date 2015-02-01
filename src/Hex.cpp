#include "Hex.h"

Hex::Hex(int _cartesianX, int _cartesianY, int _hexSize, sf::Color color) : HexCoordinates(_cartesianX, _cartesianY){

    hexSize = _hexSize;
    hexHeight = 2 * hexSize;
    hexWidth = hexHeight * (sqrt(3) / 2);

    setPixelX();
    setPixelY();

    shape = sf::CircleShape(hexSize,6);
    shape.setPosition(pixelX, pixelY);
    shape.setOutlineThickness(-1.5);
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color::Black);

    piece = nullptr;
}

Hex::~Hex()
{
    //delete coordinates;
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

void Hex::setBoarderColor(sf::Color color){
    shape.setOutlineColor(color);
}

Piece* Hex::getPiece(void){
    return piece;
}

bool Hex::hasPiece(void){

    if(piece)
        return true;
    else
        return false;
}

void Hex::setPiece(Piece* _piece){

    if(hasPiece())
        delete piece;

    piece = _piece;
    piece->setPosition(pixelX+(hexSize*(sqrt(3) / 2)) + hexSize - hexSize*cos(0.5236),pixelY+hexSize);
}

void Hex::clearPiece(void){

    piece = nullptr;
}

void Hex::deletePiece(void){

    delete piece;
    clearPiece();
}


void Hex::setPixelX(void){

     if(getCartesianY() % 2 == 0)
        pixelX = getCartesianX()*hexWidth - (hexWidth*0.5);
    else
       pixelX = (getCartesianX()*hexWidth);
}

void Hex::setPixelY(void){

    pixelY = getCartesianY()*hexHeight*0.75 - (hexSize*0.5);
}

int Hex::getPixelX(void){
     return pixelX;
}

int Hex::getPixelY(void){
    return pixelY;
}

