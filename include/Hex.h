#ifndef HEX_H
#define HEX_H

#include <SFML/Graphics.hpp>

class Hex
{
    public:
        Hex(int xPos, int yPos, int hexSize, sf::Color color);
        virtual ~Hex();

        sf::CircleShape getShape(void);

        void setColor(sf::Color color);
    protected:
    private:

    sf::CircleShape shape;

};

#endif // HEX_H
