#include <SFML/Graphics.hpp>
#include "math.h"

const unsigned int WIDTH = 400;
const unsigned int HEIGHT = 400;

const unsigned int HEXRADIUS = 40;
const unsigned int HEXHEIGHT = 2*HEXRADIUS;
const unsigned int HEXWIDTH = (unsigned int)((float)HEXHEIGHT * 0.866); // * cos(30)




int main()
{
	
	
    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Hex Map!");
		
		
	sf::CircleShape shape(HEXWIDTH,6);	
	shape.setPosition(HEXWIDTH, 0);
	shape.setOutlineThickness(-5);
	shape.setFillColor(sf::Color(0,255,0));
	shape.setOutlineColor(sf::Color(0, 0, 0));
	
	sf::CircleShape shape2(HEXWIDTH,6);	
	shape2.setPosition(HEXWIDTH*2, 0);
	shape2.setOutlineThickness(-5);
	shape2.setFillColor(sf::Color(0,255,0));
	shape2.setOutlineColor(sf::Color(0, 0, 0));
	
	sf::CircleShape shape3(HEXWIDTH,6);	
	shape3.setPosition(HEXWIDTH*1.75,HEXHEIGHT*1.25);
	shape3.setOutlineThickness(-5);
	shape3.setFillColor(sf::Color(0,255,0));
	shape3.setOutlineColor(sf::Color(0, 0, 0));
	
	
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::White);

        // draw everything here...
        window.draw(shape);
        window.draw(shape2);
		//window.draw(shape3);
        
            
        
        
        // end the current frame
        window.display();
    }

    return 0;
}
