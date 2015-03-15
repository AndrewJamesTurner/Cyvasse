#include "Hex.h"

Hex::Hex(int _cartesianX, int _cartesianY, int _hexSize, sf::Color _color) : HexCoordinates(_cartesianX, _cartesianY){

    hexSize = _hexSize;
    hexHeight = 2 * hexSize;
    hexWidth = hexHeight * (sqrt(3) / 2);
    color = _color;

    setPixelX();
    setPixelY();

    shape = sf::CircleShape(hexSize,6);
    shape.setPosition(pixelX, pixelY);
    shape.setOutlineThickness(-1.5);
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color::Black);

    piece = nullptr;
}

Hex::Hex(const Hex &obj) : HexCoordinates(obj.cartesianX, obj.cartesianY){

    shape = obj.shape;
    pixelX  = obj.pixelX;
    pixelY  = obj.pixelY;
    hexSize  = obj.hexSize;
    hexHeight  = obj.hexHeight;
    color  = obj.color;

    if(obj.piece == nullptr)
        piece = nullptr;
    else
        piece  = new Piece(*obj.piece);
}



Hex::~Hex()
{
    if(piece != nullptr)
        delete piece;
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


void Hex::setColor(sf::Color _color){
    shape.setFillColor(_color);
}

void Hex::setBoarderColor(sf::Color _color){
    shape.setOutlineColor(_color);
}

bool Hex::isPlayer(Player player) const{

    if(hasPiece()){
        if(piece->getPlayer() == player)
            return true;
        else
            return false;
    }
    else{
        return false;
    }
}

Piece* Hex::getPiece(void) const{
    return piece;
}

Type Hex::getType(void) const {
    return piece->getType();
}

bool Hex::hasPiece(void) const{

    if(piece)
        return true;
    else
        return false;
}

void Hex::setPiece(Piece* _piece){

    piece = _piece;
    piece->setPosition(pixelX+(hexSize*(sqrt(3) / 2)) + hexSize - hexSize*cos(0.5236),pixelY+hexSize);
}

void Hex::clearPiece(void){
    piece = nullptr;
}


void Hex::setPixelX(void){

     if(getCartesianY() % 2 == 0)
        pixelX = getCartesianX() * hexWidth - (hexWidth*0.5);
    else
       pixelX = (getCartesianX() * hexWidth);
}

void Hex::setPixelY(void){
    pixelY = getCartesianY() * hexHeight * 0.75 - (hexSize*0.5);
}

int Hex::getPixelX(void){
     return pixelX;
}

int Hex::getPixelY(void){
    return pixelY;
}

