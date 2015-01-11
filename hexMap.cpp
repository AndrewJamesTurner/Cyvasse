#include <SFML/Graphics.hpp>



const unsigned int ROWS = 10;
const unsigned int COLS = 10;

const unsigned int HEXWIDTH=40;

const unsigned int WIDTH = COLS*HEXWIDTH*2;
const unsigned int HEIGHT = ROWS*HEXWIDTH*2;


const unsigned int DRAWWIDTH = (unsigned int)(0.9*WIDTH);
const unsigned int DRAWHEIGHT = (unsigned int)(0.9*HEIGHT);

const unsigned int OFFSETWIDTH = (unsigned int)(0.1*WIDTH);
const unsigned int OFFSETHEIGHT = (unsigned int)(0.1*HEIGHT);

unsigned int getHexPosX(unsigned int row, unsigned int col){
	
	if(row % 2)
		return (col * HEXWIDTH * 2) + HEXWIDTH;
	else
		return col * HEXWIDTH * 2;
	
}

unsigned int getHexPosY(unsigned int row, unsigned int col){
	
	return row * HEXWIDTH * 2;
}


int main()
{
	int i,j;
	
    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Hex Map!");
		
	std::vector<sf::CircleShape> shapes(100);	
	
	for(i=0; i<ROWS; i++){
		for(j=0; j<COLS; j++){
			
			shapes[i*ROWS + j] = sf::CircleShape(HEXWIDTH,6);
			shapes[i*ROWS + j].setOrigin(HEXWIDTH, HEXWIDTH);
			shapes[i*ROWS + j].setFillColor(sf::Color(255*((float)i/ROWS), 255*((float)j/COLS), 255*(((float)i*j)/(ROWS*COLS))));
			shapes[i*ROWS + j].setPosition(getHexPosX(i,j), getHexPosY(i,j));
			shapes[i*ROWS + j].setOutlineThickness(-5);
			shapes[i*ROWS + j].setOutlineColor(sf::Color(0, 0, 0));
		}
	}
	
	
		
	
//	shapes[0].setOrigin(25, 25);
//	shapes[0].setFillColor(sf::Color(100, 250, 50));
//	shapes[0].setPosition(getHexPosX(0,0), getHexPosY(0,0));
	
	
	
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
        
        for(std::vector<sf::CircleShape>::size_type i = 0; i != shapes.size(); i++) {
			window.draw(shapes[i]);
		}
        
       // window.draw(shapes[0]);
        
        
        // end the current frame
        window.display();
    }

    return 0;
}
