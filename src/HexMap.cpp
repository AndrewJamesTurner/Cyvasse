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

    for(int x = 0; x<ncols; x++){
        for(int y = 0; y<nrows; y++){

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

void HexMap::changeColour(int row, int col){

    if(outOfBounds(row,col)){
        return;
    }

    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(0, 256);

    int red = uniform_dist(e1);
    int green = uniform_dist(e1);
    int blue = uniform_dist(e1);

    int element = (col*ncols)+row;

    hex[element].setFillColor(sf::Color(red,green,blue));
}


void HexMap::changeColour(int row, int col, int r, int g, int b){

    if(outOfBounds(row,col)){
        return;
    }

    hex[(col*ncols)+row].setFillColor(sf::Color(r,g,b));
}


void HexMap::moveOrthogonal(int row, int col, int range){

    if(outOfBounds(row,col)){
        return;
    }

    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(0, 256);

    int red = uniform_dist(e1);
    int green = uniform_dist(e1);
    int blue = uniform_dist(e1);

    // centre
    changeColour(row, col, red, green, blue);

    for(int i=1; i <= range; i++){

        // left right
        changeColour(row, col-i, red, green, blue);
        changeColour(row, col+i, red, green, blue);

        // up down
        changeColour(row-i, col, red, green, blue);
        changeColour(row+i, col, red, green, blue);

        // alternit up downs
        if(row%2 == 0){
            changeColour(row-i, col-i, red, green, blue);
            changeColour(row+i, col-i, red, green, blue);
        }
        else{
            changeColour(row-i, col+i, red, green, blue);
            changeColour(row+i, col+i, red, green, blue);
        }
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


bool HexMap::outOfBounds(int row, int col){

    if(row < 0 || row >= nrows || col < 0 || col >= ncols){
        return true;
    }
    else{
        return false;
    }
}
