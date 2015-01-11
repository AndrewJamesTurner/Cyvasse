#include <SFML/Graphics.hpp>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	sf::Vector2u size = window.getSize();

	sf::Texture texture;
	
	if (!texture.loadFromFile("mr-happy.jpg"))
	{
    	// error...
	}
	
	texture.setSmooth(true);


	sf::Font font;
	if (!font.loadFromFile("UbuntuMono-BI.ttf"))
	{
		// error...
	}
	
	sf::Text text;
	text.setFont(font); 
	text.setString("Hello world");
	text.setCharacterSize(24);
	text.setColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setPosition(400, 500);

	sf::Sprite sprite;
	sprite.setScale(sf::Vector2f(1.5,1.5)); // absolute scale factor
	sprite.setTexture(texture);
	
	sprite.setColor(sf::Color(255, 255, 255,255)); 

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
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(sprite);
        window.draw(text);

        // end the current frame
        window.display();
    }

    return 0;
}
