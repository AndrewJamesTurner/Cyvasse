#include "HexMap.h"
#include <vector>

HexMap::HexMap(sf::RenderWindow *_window, float _hexSize, int _mapHexSize){

    window = _window;

    mapHexSize = _mapHexSize;
    nrows = 2*mapHexSize + mapHexSize;
    ncols = 2*mapHexSize + mapHexSize;

    hexSize =_hexSize;
    hexHeight = 2 * hexSize;
    hexWidth = hexHeight * (sqrt(3) / 2);

    for(int col = 0; col<ncols; col++){
        for(int row = 0; row<nrows; row++){
            hex.push_back(Hex(getXpos(col,row), getYpos(col,row), hexSize, sf::Color::White));
        }
    }

    hex[getIndex(5,5)].setPiece(new Piece());

    clearMap();
}

HexMap::~HexMap(){
    //dtor
}


int HexMap::getIndex(int row, int col){
    return col*ncols+row;
}

void HexMap::clearMap(void){

    for(int col = 0; col<ncols; col++){
        for(int row = 0; row<nrows; row++){

            if(!outOfBounds(row,col)){
                hex[col*ncols+row].setColor(sf::Color::Green);
            }
            else{
                hex[col*ncols+row].setColor(sf::Color::Blue);
            }
        }
    }

}


void HexMap::update(void){

    for(auto i = hex.begin(); i!=hex.end(); ++i){

        (*i).draw(window);
/*
        if((*i).getPiece()){
            Piece *piece = (*i).getPiece();
            sf::Sprite sprite = piece->getSprite();
            window->draw(sprite);
        }
    */
    }
}

bool HexMap::inRangeAny(int row1, int col1, int row2, int col2, int range){

    // get cube coordinates
    int x1 = col1 - (row1 - (row1&1))/2;
    int z1 = row1;
    int y1 = 0 - x1 - z1;

    int x2 = col2 - (row2 - (row2&1))/2;
    int z2 = row2;
    int y2 = 0 - x2 - z2;

    return inRangeAny(x1, y1, z1, x2, y2, z2, range);
}

bool HexMap::inRangeAny(int x1, int y1, int z1, int x2, int y2, int z2, int range){

    int distance = ( abs(x1-x2) + abs(y1-y2) + abs(z1-z2)) / 2;

    if(distance <= range)
        return true;
    else
        return false;
}

void HexMap::changeColour(int row, int col){

    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(0, 256);

    int red = uniform_dist(e1);
    int green = uniform_dist(e1);
    int blue = uniform_dist(e1);

    changeColour(row,col,red,green,blue);
}

void HexMap::changeColour(int x, int y, int z){

    int row = z;
    int col = x + (z - (z&1))/2;

    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(0, 256);

    int red = uniform_dist(e1);
    int green = uniform_dist(e1);
    int blue = uniform_dist(e1);

    changeColour(row,col,red,green,blue);
}

void HexMap::changeColour(int row, int col, int red, int green, int blue){

    if(outOfBounds(row,col)){
        return;
    }

    hex[(col*ncols)+row].setColor(sf::Color(red,green,blue));
}

void HexMap::changeColour(int x, int y, int z, int red, int green, int blue){

    int row = z;
    int col = x + (z - (z&1))/2;

    changeColour(row,col, red, green, blue);
}

void HexMap::moveOrthogonal(int row, int col, int range){

    if(outOfBounds(row,col))
        return;

    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(0, 256);

    int red = uniform_dist(e1);
    int green = uniform_dist(e1);
    int blue = uniform_dist(e1);

    // get cube coordinates
    int xCentre = col - (row - (row&1))/2;
    int zCentre = row;
    int yCentre = 0 - xCentre - zCentre;
    changeColour(zCentre, xCentre + (zCentre - (zCentre&1))/2, red, green, blue);

    for(int i = -range; i <= range; i++){

        int x,y,z;

        // left right
        x = xCentre + i;
        y = yCentre - i;
        z = zCentre;
        changeColour(x, y, z, red, green, blue);

        // diagonal 1
        x = xCentre + i;
        y = yCentre;
        z = zCentre - i;
        changeColour(x, y, z, red, green, blue);

        // diagonal 2
        x = xCentre;
        y = yCentre + i;
        z = zCentre - i;
        changeColour(x, y, z, red, green, blue);
    }
}

void HexMap::moveDiagonal(int row, int col, int range){

    if(outOfBounds(row,col))
        return;

    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(0, 256);

    int red = uniform_dist(e1);
    int green = uniform_dist(e1);
    int blue = uniform_dist(e1);

    // get cube coordinates
    int xCentre = col - (row - (row&1))/2;
    int zCentre = row;
    int yCentre = 0 - xCentre - zCentre;
    changeColour(zCentre, xCentre + (zCentre - (zCentre&1))/2, red, green, blue);

    for(int i = -range; i <= range; i++){

        int x,y,z;

        // left right
        x = xCentre + 2*i;
        y = yCentre - i;
        z = zCentre - i;
        changeColour(x, y, z, red, green, blue);

        // diagonal 1
        x = xCentre - i;
        y = yCentre + 2*i;
        z = zCentre - i;
        changeColour(x, y, z, red, green, blue);

        // diagonal 2
        x = xCentre - i;
        y = yCentre - i;
        z = zCentre + 2*i;
        changeColour(x, y, z, red, green, blue);
    }
}

void HexMap::moveAny(int row, int col, int range){

    if(outOfBounds(row,col))
        return;

    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(0, 256);

    int red = uniform_dist(e1);
    int green = uniform_dist(e1);
    int blue = uniform_dist(e1);

    // get cube coordinates
    int xCentre = col - (row - (row&1))/2;
    int zCentre = row;
    int yCentre = 0 - xCentre - zCentre;

    for(int dx = -range; dx <= range; dx++){
        for(int dy = -range; dy <= range; dy++){
            for(int dz = -range; dz <= range; dz++){

                int x = xCentre + dx;
                int y = yCentre + dy;
                int z = zCentre + dz;

                if(x+y+z == 0){
                    changeColour(x, y, z, red, green, blue);
                }
            }
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
        col = (x/hexWidth) + 0.5;;
    }
    else{

        if(x < hexWidth/2){
            col = -1;
        }
        else{
            col = (x/hexWidth);
        }
    }

    if(col < 0 || col >= ncols){
        col = -1;
    }

    return col;
}

int HexMap::getCubeX(int x, int y){

    int row = getRow(x,y);
    int col = getCol(x,y);

    int cubeX = col - (row - (row&1))/2;

    return cubeX;
}

int HexMap::getCubeY(int x, int y){

    int row = getRow(x,y);
    int col = getCol(x,y);

    int cubeX = col - (row - (row&1))/2;
    int cubeZ = row;
    int cubeY = 0 - cubeX - cubeZ;

    return cubeY;
}

int HexMap::getCubeZ(int x, int y){

    int row = getRow(x,y);
    int cubeZ = row;

    return cubeZ;
}

int HexMap::getXpos(int row, int col){

     if(col % 2 == 0)
        return row*hexWidth - (hexWidth*0.5);
    else
       return (row*hexWidth);
}

int HexMap::getYpos(int row, int col){

    return col*hexHeight*0.75;
}

bool HexMap::outOfBounds(int row, int col){

    int x = col - (row - (row&1))/2;
    int z = row;
    int y = 0 - x - z;

    return outOfBounds(x,y,z);
}

bool HexMap::outOfBounds(int x, int y, int z){

    int xCenter = mapHexSize - (mapHexSize - (mapHexSize&1))/2;
    int zCenter = mapHexSize;
    int yCenter = 0 - xCenter - zCenter;

    if(inRangeAny(xCenter, yCenter, zCenter, x, y, z, mapHexSize))
        return false;
    else
        return true;
}
