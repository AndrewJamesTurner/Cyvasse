#include "Render.h"

Render::Render(sf::RenderWindow *_window, HexMap *_hexMap): window{_window}, hexMap{_hexMap}
{
    if (!spearsTexture.loadFromFile("Images/Spears.png"))
        exit(0);
    if (!kingTexture.loadFromFile("Images/King.png"))
        exit(0);
    if (!mountainTexture.loadFromFile("Images/Mountain.png"))
        exit(0);
    if (!rabbleTexture.loadFromFile("Images/Rabble.png"))
        exit(0);
}

Render::~Render()
{
    //dtor
}

void Render::update(HexMap hexMap){

std::vector<Hex> hexes = hexMap.getHexes();

    for(auto i = hexes.begin(); i!=hexes.end(); ++i) {

        int xPos = (*i).getCartesianX();
        int yPos = (*i).getCartesianY();

        //int xPix = getPixelX(xPos, yPos);
        //int yPix = getPixelY(xPos, yPos);

        window->draw(getShape(xPos, yPos, hexMap.isHexSelected(xPos, yPos)));

        if((*i).hasPiece()){
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
    sprite.setScale(sf::Vector2f(0.5f, 0.5f));
    sprite.setOrigin(textureRect.left + textureRect.width/2.0f, textureRect.top  + textureRect.height/2.0f);
    sprite.setPosition(getPixelX(x,y)+(SIZE*(sqrt(3) / 2)) + SIZE - SIZE*cos(0.5236),getPixelY(x,y)+SIZE);

    return sprite;
}



sf::CircleShape Render::getShape(int x, int y, bool selected){

    sf::CircleShape shape;
    shape = sf::CircleShape(SIZE,6);
    shape.setOutlineThickness(-1.5);
    shape.setPosition(getPixelX(x,y), getPixelY(x,y));

    if(selected)
        shape.setOutlineColor(sf::Color::Yellow);
    else
        shape.setOutlineColor(sf::Color::Black);

    if(hexMap->isOnBoard(x,y))
       shape.setFillColor(green);
    else
        shape.setFillColor(blue);

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
        return x * getHexWidth(SIZE) - (getHexWidth(SIZE)*0.5);
    else
       return x * getHexWidth(SIZE);
}

int Render::getPixelY(int x, int y){
    return y * getHexheight(SIZE) * 0.75 - (SIZE*0.5);
}


