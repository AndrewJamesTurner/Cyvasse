#include "Render.h"

Render::Render()
{
    singleHexSize = 30;
    windowWidth = 2 * singleHexSize * MAPSIZE * 2 * 0.88;
    windowHeight = 2 * singleHexSize * MAPSIZE * 2 * (sqrt(3) / 2) * 0.93;

    window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Hex Map!", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(30);

    if (!spearsTexture.loadFromFile("Images/Spears.png"))
        exit(0);
    if (!kingTexture.loadFromFile("Images/King.png"))
        exit(0);
    if (!mountainTexture.loadFromFile("Images/Mountain.png"))
        exit(0);
    if (!rabbleTexture.loadFromFile("Images/Rabble.png"))
        exit(0);
    if (!crossbowTexture.loadFromFile("Images/Crossbow.png"))
        exit(0);
}

Render::~Render()
{
    //dtor
}

void Render::update(HexMap hexMap, GameState gameState, Player player){

    window->clear(sf::Color(blue));

    std::vector<Hex> hexes = hexMap.getHexes();

    for(auto i = hexes.begin(); i!=hexes.end(); ++i) {

        int xPos = (*i).getCartesianX();
        int yPos = (*i).getCartesianY();

        window->draw(getShape(hexMap, xPos, yPos, hexMap.isHexSelected(xPos, yPos), hexMap.isHexHighlighted(*i), gameState, player));

        if((*i).hasPiece()){

            if(gameState == GameState::placement && !hexMap.isInPlayerhalf(player, yPos))
                continue;

            window->draw(getSprite(xPos, yPos, (*i).getType(), (*i).getPiece()->getPlayer()));
        }
    }
}


sf::Sprite Render::getSprite(int x, int y, Type type, Player player){

    sf::Sprite sprite;

    switch(type){
        case Type::king:
            sprite.setTexture(kingTexture);
            break;
        case Type::mountain:
            sprite.setTexture(mountainTexture);
            break;
        case Type::rabble:
            sprite.setTexture(rabbleTexture);
            break;
        case Type::spears:
            sprite.setTexture(spearsTexture);
            break;
        case Type::crossbow:
            sprite.setTexture(crossbowTexture);
            break;
    }

    switch(player){
        case Player::player1:
            sprite.setColor(sf::Color::Black);
            break;
        case Player::player2:
            sprite.setColor(sf::Color::White);
            break;
    }

    sf::FloatRect textureRect = sprite.getLocalBounds();
    sprite.setScale(sf::Vector2f(windowWidth/(float)MAPSIZE * 0.005, windowWidth/(float)MAPSIZE * 0.005) );

    sprite.setOrigin(textureRect.left + textureRect.width/2.0f, textureRect.top  + textureRect.height/2.0f);
    sprite.setPosition(getPixelX(x,y)+(singleHexSize*(sqrt(3) / 2)) + singleHexSize - singleHexSize*cos(0.5236),getPixelY(x,y)+singleHexSize);

    return sprite;
}


sf::CircleShape Render::getShape(HexMap hexMap, int x, int y, bool selected, bool highlighted, GameState gameState, Player player){

    Hex hex = hexMap.getHex(x,y);

    sf::CircleShape shape;
    shape = sf::CircleShape(singleHexSize,6);
    shape.setOutlineThickness(-1.5);
    shape.setPosition(getPixelX(x,y), getPixelY(x,y));

    if(selected)
        shape.setOutlineColor(sf::Color::Yellow);
    else
        shape.setOutlineColor(sf::Color::Black);

    if(gameState == GameState::placement && !hexMap.isInPlayerhalf(player, y) && hexMap.isOnBoard(x,y))
        shape.setFillColor(lightBlue);
    else if(highlighted)
        shape.setFillColor(sf::Color::Red);
    else if(hexMap.isOffBoard(x,y))
        shape.setFillColor(blue);
    else if(hex.getTerrain() == Terrain::forest)
        shape.setFillColor(sf::Color(0,100,0));
    else
         shape.setFillColor(green);

    return shape;
}

int Render::getHexheight(int hexSize){
    return 2 * hexSize;
}

int Render::getHexWidth(int hexSize){
    return getHexheight(hexSize) * (sqrt(3) / 2);
}

int Render::getPixelX(int x, int y){

     if(y % 2 == 0)
        return x * getHexWidth(singleHexSize) - (getHexWidth(singleHexSize)*0.5);
    else
       return x * getHexWidth(singleHexSize);
}

int Render::getPixelY(int x, int y){
    return y * getHexheight(singleHexSize) * 0.75 - (singleHexSize*0.5);
}

int Render::getCartesianX(int xPix, int yPix){

    int xPos;
    float hexHeight = 2 * singleHexSize;
    float hexWidth = hexHeight * (sqrt(3) / 2);

    if(getCartesianY(xPix, yPix) % 2 == 0) {
        xPos = (xPix/hexWidth) + 0.5;
    } else {

        if(xPix < hexWidth/2) {
            xPos = -1;
        } else {
            xPos = (xPix/hexWidth);
        }
    }

    return xPos;
}

int Render::getCartesianY(int xPix, int yPix){

    int yPos;
    float hexHeight = 2 * singleHexSize;

    yPos = (yPix + (singleHexSize*0.5))/ (hexHeight*0.75);

    return yPos;
}

sf::RenderWindow* Render::getRenderWindow(void){
    return window;
}
