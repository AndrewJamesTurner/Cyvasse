#include "Render.h"

Render::Render(sf::RenderWindow *_window): window{_window}
{
    //ctor
}

Render::~Render()
{
    //dtor
}

void Render::update(HexMap hexMap){

std::vector<Hex> hexes = hexMap.getHexes();
/*
    for(auto x = 0; x < hexMap.getWidth(); x++){
        for(auto y = 0; y < hexMap.getHeight(); y++){

            sf::CircleShape shape;
            shape = sf::CircleShape(hexSize,6);
            hape.setOutlineThickness(-1.5);
            shape.setFillColor(sf::Color::Blue);
            shape.setOutlineColor(sf::Color::Black);

        }
    }
*/
    for(auto i = hexes.begin(); i!=hexes.end(); ++i) {

        int xPos = (*i).getCartesianX();
        int yPos = (*i).getCartesianY();

        int xPix = getPixelX(xPos, yPos);
        int yPix = getPixelY(xPos, yPos);

        sf::CircleShape shape;
        shape = sf::CircleShape(SIZE,6);
        shape.setOutlineThickness(-1.5);
        shape.setOutlineColor(sf::Color::Black);
        shape.setPosition(xPix, yPix);

        if(hexMap.isOnBoard(xPos,yPos))
           shape.setFillColor(sf::Color::Green);
        else
            shape.setFillColor(sf::Color::Blue);

        window->draw(shape);


    }
}


int Render::getHexheight(int hexSize){
    return 2 * hexSize;
}

int Render::getHexWidth(int hexSize){
    return getHexheight(hexSize) * (sqrt(3) / 2);
}

int Render::getPixelX(int x, int y){

     if(y % 2 == 0)
        return x * getHexWidth(SIZE) - (getHexWidth(SIZE)*0.5);
    else
       return x * getHexWidth(SIZE);
}

int Render::getPixelY(int x, int y){
    return y * getHexheight(SIZE) * 0.75 - (SIZE*0.5);
}


