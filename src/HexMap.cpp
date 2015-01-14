#include "HexMap.h"
#include <vector>

HexMap::HexMap(sf::RenderWindow *_window, float _hexSize, int _nrows, int _ncols)
{
    window = _window;

    nrows =_nrows;
    ncols = _ncols;

    hexSize =_hexSize;
    hexHeight = 2 * hexSize;
    hexWidth = hexHeight * (sqrt(3) / 2);

    for(int x = 0; x<nrows; x++){
        for(int y = 0; y<ncols; y++){

            hex.push_back(sf::CircleShape(hexSize,6));

            if(y % 2 == 0)
                hex.back().setPosition(x*hexWidth, y*hexHeight*0.75);
            else
                hex.back().setPosition((x*hexWidth) + (hexWidth*0.5), y*hexHeight*0.75);

            hex.back().setFillColor(sf::Color(0,255,0));
            hex.back().setOutlineThickness(-5);
            hex.back().setOutlineColor(sf::Color(0, 0, 0));
        }
    }
}

HexMap::~HexMap()
{
    //dtor
}

void HexMap::update(void){

    for(auto i = hex.begin(); i!=hex.end(); ++i){
        window->draw(*i);

    }
}

int HexMap::getRow(int x, int y){

}

int HexMap::getCol(int x, int y){

}
