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
        void update(HexMap hexMap, GameState gameState, Player player);

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
        const sf::Color forestGreen = sf::Color(0,75,36);
        const sf::Color hillOrange = sf::Color(179,66,24);
        const sf::Color grassGreen = sf::Color(102,149,47);

        const double spriteScaleFactor = 0.004;
        const double tierTextScaleFactor = 0.3;

        int getPixelX(int x, int y);
        int getPixelY(int x, int y);

        double getHexheight(int hexSize);
        double getHexWidth(int hexSize);

        sf::CircleShape getShape(HexMap hexMap, int x, int y, bool selected, bool highlighted, GameState gameState, Player player);
        sf::Sprite getPieceSprite(int x, int y, Type type, Player player);
        sf::Text getPieceRankText(int x, int y, Hex hex);


        sf::RenderWindow* window;
        HexMap* hexMap;

        sf::Texture spearsTexture;
        sf::Texture kingTexture;
        sf::Texture mountainTexture;
        sf::Texture rabbleTexture;
        sf::Texture crossbowTexture;

        sf::Font pieceRankFont;

};

#endif // RENDER_H
