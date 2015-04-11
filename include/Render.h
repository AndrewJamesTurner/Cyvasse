#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.hpp>
#include "HexMap.h"

#define SIZE 30


class Render
{
    public:
        Render(sf::RenderWindow *_window);
        virtual ~Render();
        void update(HexMap hexMap);
    protected:
    private:
        int getPixelX(int x, int y);
        int getPixelY(int x, int y);

        int getHexheight(int hexSize);
        int getHexWidth(int hexSize);


    sf::RenderWindow *window;
};

#endif // RENDER_H
