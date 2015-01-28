
#include "header.h"

#define SIZE 30
#define MAPSIZE 6

#define WIDTH 2*SIZE*(MAPSIZE*2) - 4*SIZE
#define HEIGHT 2*SIZE*(MAPSIZE*2)*(sqrt(3) / 2) - 3*SIZE

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Hex Map!", sf::Style::Titlebar | sf::Style::Close);

    // make hexmap
	GameLogic gameLogic(&window, SIZE, MAPSIZE);



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

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int mouseClickX = event.mouseButton.x;
                    int mouseClickY = event.mouseButton.y;

                    gameLogic.mapClicked(mouseClickX, mouseClickY);
                    //gameLogic.moveOrthogonal(row, col,3);
                }

                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    gameLogic.deselect();
                }
            }
        }



        // clear the window with black color
        window.clear(sf::Color(20,20,230));

        // draw everything here...
        gameLogic.update();

        // end the current frame
        window.display();
    }

    return 0;
}
