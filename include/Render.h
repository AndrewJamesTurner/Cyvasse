#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.hpp>
#include "HexMap.h"

#define SIZE 30


class Render
{
    public:
        Render(sf::RenderWindow *_window, HexMap *_hexMap);
        virtual ~Render();
        void update(HexMap hexMap);
    protected:
    private:


        const sf::Color green = sf::Color(17,220,51);
        const sf::Color blue = sf::Color(20,20,230);

        int getPixelX(int x, int y);
        int getPixelY(int x, int y);

        int getHexheight(int hexSize);
        int getHexWidth(int hexSize);

        sf::CircleShape getShape(int x, int y, bool selected);
        sf::Sprite getSprite(int x, int y, Type type, Player player);


        sf::RenderWindow *window;
        HexMap *hexMap;

        sf::Texture spearsTexture;
        sf::Texture kingTexture;
        sf::Texture mountainTexture;
        sf::Texture rabbleTexture;

};

#endif // RENDER_H
