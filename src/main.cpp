
#include "header.h"

#define SIZE 30
#define ROWS 5
#define COLS 5

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(2*SIZE*COLS, 2*SIZE*COLS*(sqrt(3) / 2)), "Hex Map!");

    // make hexmap
	HexMap hexmap(&window, SIZE, ROWS, COLS);

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
        hexmap.update();

        // end the current frame
        window.display();
    }

    return 0;
}
