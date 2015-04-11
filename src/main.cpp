
#include <SFML/Graphics.hpp>
#include "math.h"
#include <iostream>

#include "GameLogic.h"
#include "Render.h"

#include <stdlib.h>
#include <time.h>

#define SIZE 30
#define MAPSIZE 6

#define WIDTH 2*SIZE*(MAPSIZE*2) * 0.88
#define HEIGHT 2*SIZE*(MAPSIZE*2)*(sqrt(3) / 2) * 0.93

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Hex Map!", sf::Style::Titlebar | sf::Style::Close);
    sf::RenderWindow windowTmp(sf::VideoMode(WIDTH, HEIGHT), "Hex Map!", sf::Style::Titlebar | sf::Style::Close);

    //
    HexMap hexMap(SIZE,MAPSIZE);

    // set the frame rate
    window.setFramerateLimit(30);

    // make hexmap
	GameLogic gameLogic(&window, SIZE, MAPSIZE);

    //
    Render render(&windowTmp, &hexMap);

    // run the program as long as the window is open
    while (window.isOpen())
    {

        if(gameLogic.getGameState() == GameState::player2Turn){
            gameLogic.enemyMove();
        }
        else if(gameLogic.getGameState() == GameState::player1Turn){

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
                    }

                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        gameLogic.deselect();
                    }
                }
            }
        }

        // clear the window with blue
        window.clear(sf::Color(20,20,230));
        windowTmp.clear(sf::Color(20,20,230));

        // draw everything here...
        gameLogic.update();

        //
        render.update(gameLogic.getHexMap());

        // end the current frame
        window.display();
        windowTmp.display();
    }

    return 0;
}
