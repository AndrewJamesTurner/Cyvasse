#include "HexMap.h"
#include <vector>

HexMap::HexMap(sf::RenderWindow *_window, float _hexSize, int _mapHexSize) {

    window = _window;

    mapHexSize = _mapHexSize;
    width = 2*mapHexSize + mapHexSize;
    height = 2*mapHexSize + mapHexSize;

    hexSize =_hexSize;
    hexHeight = 2 * hexSize;
    hexWidth = hexHeight * (sqrt(3) / 2);

    selectedHex = nullptr;

    for(int x = 0; x<width; x++) {
        for(int y = 0; y<height; y++) {
            hex.push_back(Hex(x,y, hexSize, sf::Color::White));
        }
    }


    hex[getIndex(5,5)].setPiece(new Piece());

    clearMap();
}

HexMap::~HexMap() {
    //dtor
}


void HexMap::mapClicked(int xPixel, int yPixel) {

    int x = getX(xPixel, yPixel);
    int y = getY(xPixel, yPixel);

    if(outOfBounds(x,y)) {
        return;
    }

    clearMap();

    Hex* HexClicked = &hex[getIndex(x,y)];

    if(!selectedHex && HexClicked->hasPiece()){

        selectedHex = HexClicked;
        selectedHex->setColor(sf::Color::White);
    }

    else if(selectedHex && !HexClicked->hasPiece()){


        if(selectedHex->getPiece()->getMoveType() == movement::orthogonal && selectedHex->isOrthogonal(*HexClicked)){

            HexClicked->setPiece(selectedHex->getPiece());
            selectedHex->clearPiece();
            selectedHex = nullptr;
        }
    }
    else{
        selectedHex = nullptr;
    }

}


int HexMap::getIndex(int x, int y) {
    return (x*width)+y;
}

void HexMap::clearMap(void) {

    HexCoordinates centerHex(mapHexSize, mapHexSize);

    for(int x = 0; x<width; x++) {
        for(int y = 0; y<height; y++) {

            HexCoordinates currentHex(x, y);

            if(centerHex.isInRange(currentHex, mapHexSize)){
                hex[getIndex(x,y)].setColor(sf::Color::Green);
            }
            else {
                hex[getIndex(x,y)].setColor(sf::Color::Blue);
            }
        }
    }
}


void HexMap::update(void) {

    for(auto i = hex.begin(); i!=hex.end(); ++i) {

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

bool HexMap::inRangeAny(int row1, int col1, int row2, int col2, int range) {

    // get cube coordinates
    int x1 = col1 - (row1 - (row1&1))/2;
    int z1 = row1;
    int y1 = 0 - x1 - z1;

    int x2 = col2 - (row2 - (row2&1))/2;
    int z2 = row2;
    int y2 = 0 - x2 - z2;

    return inRangeAny(x1, y1, z1, x2, y2, z2, range);
}

bool HexMap::inRangeAny(int x1, int y1, int z1, int x2, int y2, int z2, int range) {

    int distance = ( abs(x1-x2) + abs(y1-y2) + abs(z1-z2)) / 2;

    if(distance <= range)
        return true;
    else
        return false;
}

void HexMap::changeColour(int row, int col) {

    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(0, 256);

    int red = uniform_dist(e1);
    int green = uniform_dist(e1);
    int blue = uniform_dist(e1);

    changeColour(row,col,red,green,blue);
}

void HexMap::changeColour(int x, int y, int z) {

    int row = z;
    int col = x + (z - (z&1))/2;

    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(0, 256);

    int red = uniform_dist(e1);
    int green = uniform_dist(e1);
    int blue = uniform_dist(e1);

    changeColour(row,col,red,green,blue);
}

void HexMap::changeColour(int x, int y, int red, int green, int blue) {

    if(outOfBounds(x,y)) {
        return;
    }

    hex[getIndex(x,y)].setColor(sf::Color(red,green,blue));
}

void HexMap::changeColour(int x, int y, int z, int red, int green, int blue) {

    int row = z;
    int col = x + (z - (z&1))/2;

    changeColour(row,col, red, green, blue);
}

void HexMap::moveOrthogonal(int row, int col, int range) {

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

    for(int i = -range; i <= range; i++) {

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

void HexMap::moveDiagonal(int row, int col, int range) {

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

    for(int i = -range; i <= range; i++) {

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

void HexMap::moveAny(int row, int col, int range) {

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

    for(int dx = -range; dx <= range; dx++) {
        for(int dy = -range; dy <= range; dy++) {
            for(int dz = -range; dz <= range; dz++) {

                int x = xCentre + dx;
                int y = yCentre + dy;
                int z = zCentre + dz;

                if(x+y+z == 0) {
                    changeColour(x, y, z, red, green, blue);
                }
            }
        }
    }
}


int HexMap::getX(int pixelX, int pixelY) {

    int xPos;

    if(getY(pixelX, pixelY) % 2 == 0) {
        xPos = (pixelX/hexWidth) + 0.5;;
    } else {

        if(pixelX < hexWidth/2) {
            xPos = -1;
        } else {
            xPos = (pixelX/hexWidth);
        }
    }

    return xPos;
}

int HexMap::getY(int pixelX, int pixelY) {

    int yPos;

    yPos = pixelY /(hexHeight*0.75);

    return yPos;
}


bool HexMap::outOfBounds(int x, int y){

    HexCoordinates current(x,y);
    HexCoordinates center(mapHexSize,mapHexSize);

    if(center.isInRange(current, mapHexSize)){
        return false;
    }
    else{
        return true;
    }
}
