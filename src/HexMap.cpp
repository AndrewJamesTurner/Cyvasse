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
            hex.back().setPosition(getXpos(x,y), getYpos(x,y));
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

    int row;

    row = y /(hexHeight*0.75);

    if(row < 0 || row >= nrows){
        row = -1;
    }

    return row;
}

int HexMap::getCol(int x, int y){

    int col;

    if(getRow(x, y) % 2 == 0){
        col = x/hexWidth;
    }
    else{

        if(x < hexWidth/2){
            col = -1;
        }
        else{
            col = (x/hexWidth) - 0.5;
        }
    }

    if(col < 0 || col >= ncols){
        col = -1;
    }

    return col;
}

int HexMap::getXpos(int row, int col){

     if(col % 2 == 0)
        return row*hexWidth;
    else
       return (row*hexWidth) + (hexWidth*0.5);
}

int HexMap::getYpos(int row, int col){

    return col*hexHeight*0.75;
}
