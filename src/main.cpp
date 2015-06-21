
#include <SFML/Graphics.hpp>
#include "math.h"
#include <iostream>

#include "GameLogic.h"
#include "Render.h"

#include "GameState.h"

#include "PlayerControls.h"

#include <stdlib.h>
#include <time.h>

enum class PlayerType{human,AI};


int main()
{
    //PlayerType player1 = PlayerType::AI;
    //PlayerType player2 = PlayerType::human;

    PlayerType player1 = PlayerType::human;
    PlayerType player2 = PlayerType::AI;

    Difficulty AIdifficulty = Difficulty::veryEasy;


    HexMap hexmap(MAPSIZE);
    Render render;
    sf::RenderWindow* window = render.getRenderWindow();
    window->setFramerateLimit(60);

	GameState2 gameState = GameState2::placement;

    // run the program as long as the window is open
    while (window->isOpen())
    {
        //
        if(gameState == GameState2::gameOver){
            std::cout << "\ngame over\n";
            return 0;
        }

        // deal with AI players
        if(gameState == GameState2::player1Turn && player1 == PlayerType::AI){
            AI::AImove(&hexmap, Player::player1, AIdifficulty);
            gameState = GameState2::player2Turn;
        }
        else if(gameState == GameState2::player2Turn && player2 == PlayerType::AI){
            AI::AImove(&hexmap, Player::player2, AIdifficulty);
            gameState = GameState2::player1Turn;
        }

        sf::Event event;

        while (window->pollEvent(event)){

            if (event.type == sf::Event::Closed){
                window->close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int mouseClickX = event.mouseButton.x;
                    int mouseClickY = event.mouseButton.y;

                    int x = render.getCartesianX(mouseClickX, mouseClickY);
                    int y = render.getCartesianY(mouseClickX, mouseClickY);

                    if(gameState == GameState2::placement){

                        if(player1 == PlayerType::human)
                            PlayerControls::playerPlacement(&hexmap, Player::player1, x, y);

                        if(player2 == PlayerType::human)
                            PlayerControls::playerPlacement(&hexmap, Player::player2, x, y);


                    }
                    else if(gameState == GameState2::player1Turn && player1 == PlayerType::human){

                        bool didMove = PlayerControls::playerMove(&hexmap, Player::player1, x, y);

                        if(didMove)
                            gameState = GameState2::player2Turn;

                    }
                    else if(gameState == GameState2::player2Turn && player2 == PlayerType::human){

                        bool didMove = PlayerControls::playerMove(&hexmap, Player::player2, x, y);

                        if(didMove)
                            gameState = GameState2::player1Turn;
                    }
                }

                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    if(gameState == GameState2::placement){
                        gameState = GameState2::player1Turn;
                    }
                    else{
                        hexmap.clearHighlightedHexes();
                        hexmap.setSelectedHex(nullptr);
                    }
                }
            }
        }

        if(gameState == GameState2::placement){

            if(player1 == PlayerType::human)
                render.update(hexmap, gameState, Player::player1);

            if(player2 == PlayerType::human)
                render.update(hexmap, gameState, Player::player2);
        }
        else
            render.update(hexmap, gameState, Player::player1);

        window->display();

        if(!hexmap.isBothKingsOnBoard()){
            gameState = GameState2::gameOver;
        }
    }

    return 0;
}
