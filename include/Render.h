#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.hpp>
#include "HexMap.h"
#include <vector>
#include <algorithm>
#include "GameState.h"

#define MAPSIZE 6


class Render
{
    public:
        Render();
        virtual ~Render();

        sf::RenderWindow* getRenderWindow(void);
        void update(HexMap hexMap, GameState2 gameState);

        int getCartesianX(int xPix, int yPix);
        int getCartesianY(int xPix, int yPix);


    protected:
    private:

        int singleHexSize;
        int windowWidth;
        int windowHeight;

        const sf::Color green = sf::Color(17,220,51);
        const sf::Color blue = sf::Color(20,20,230);
        const sf::Color lightBlue = sf::Color(180,180,180);

        int getPixelX(int x, int y);
        int getPixelY(int x, int y);

        int getHexheight(int hexSize);
        int getHexWidth(int hexSize);

        sf::CircleShape getShape(HexMap hexMap, int x, int y, bool selected, bool highlighted, GameState2 gameState);
        sf::Sprite getSprite(int x, int y, Type type, Player player);


        sf::RenderWindow* window;
        HexMap* hexMap;

        sf::Texture spearsTexture;
        sf::Texture kingTexture;
        sf::Texture mountainTexture;
        sf::Texture rabbleTexture;
        sf::Texture crossbowTexture;

};

#endif // RENDER_H
