
#include "header.h"

#define SIZE 30
#define ROWS 10
#define COLS 10
#define MAPSIZE 5

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(2*SIZE*(COLS) - 0.9*SIZE, 2*SIZE*(ROWS)*(sqrt(3) / 2)- 0.4*SIZE), "Hex Map!", sf::Style::Titlebar | sf::Style::Close);

    // make hexmap
	HexMap hexmap(&window, SIZE, MAPSIZE);



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

                    hexmap.mapClicked(mouseClickX, mouseClickY);
                    //hexmap.moveOrthogonal(row, col,3);
                }

                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    hexmap.deselect();
                }
            }
        }



        // clear the window with black color
        window.clear(sf::Color::Blue);

        // draw everything here...
        hexmap.update();

        // end the current frame
        window.display();
    }

    return 0;
}
