// Include important C++ libraries here
// Crosby Myers, Aidan Thowtho
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

Vector2f generateMp(Vector2f a, Vector2f b)
{
	Vector2f mid((a.x + b.x) / 2, (a.y + b.y) / 2);
	return mid;
}

int main()
{
	srand(time(0));
	// Create a video mode object
		VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);
	
	vector<Vector2f> vertices;
	vector<Vector2f> points;

	// Display instructions for the user using the Text class
	Font marioFont;
	// Load font
	if (!marioFont.loadFromFile("TypefaceMario64-ywA93.otf")) {
		cout << "Error loading font from file." << endl;
	}

	// Create Swag Mario texture and sprite
	Texture swagTexture;
	if (!swagTexture.loadFromFile("swag.png"))
	{
		cout << "Error loading png file" << endl;
		return 1;
	}
	Sprite swagMario(swagTexture);

	// Create Rap Mario texture and sprite
	Texture rapTexture;
	if (!rapTexture.loadFromFile("rapMario.png"))
	{
		cout << "Error loading png file" << endl;
		return 1;
	}
	Sprite rapMario(rapTexture);

	// Set text
	Text instructions;
	instructions.setFont(marioFont);
	instructions.setString(" Click the screen 3 times to draw your triangle! \n          Click once more to start the chaos!");
	instructions.setCharacterSize(30); // in pixels, not points!
	instructions.setFillColor(sf::Color::Blue);

	// Create Mario Death Sound
	SoundBuffer marioDeathBuffer;
	if (!marioDeathBuffer.loadFromFile("Waah Sound.wav")) {
		cout << "Error loading sound from file" << endl;
		return 1;
	}

	Sound marioDeathSound;
	marioDeathSound.setBuffer(marioDeathBuffer);
	marioDeathSound.play();
	
	// Create Coin Sound
	SoundBuffer coinBuffer;
	if (!coinBuffer.loadFromFile("Mario Coin Sound.wav")) {
		cout << "Error loading sound from file" << endl;
		return 1;
	}
	
	Sound coinSound;
	coinSound.setBuffer(coinBuffer);
	
	// Create Yahoo Sound
	SoundBuffer yahooBuffer;
	if (!yahooBuffer.loadFromFile("Yahoo Sound.wav")) {
		cout << "Error loading sound from file" << endl;
		return 1;
	}

	Sound yahooSound;
	yahooSound.setBuffer(yahooBuffer);

	// Create Scary Monsters and Nice Sprites Music
	Music ScaryMonsters;
	if (!ScaryMonsters.openFromFile("Skrillex - Scary Monsters And Nice Sprites (Official Audio).wav")) {
		cout << "Error opening music file" << endl;
		return 1;
	}
	ScaryMonsters.setLoop(true);
	
	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
	// Prompt user for input 
		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			    std::cout << "the left button was pressed" << std::endl;
			    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
			    if(vertices.size() < 3)
			    {
					vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					coinSound.play();
			    }
			    else if(points.size() == 0)
			    {
				///fourth click
				///push back to points vector
				
					points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					yahooSound.play();
					ScaryMonsters.play();
			    }
			}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
	
		if(points.size() > 0)
		{
		    ///generate more point(s)
		    ///select random vertex
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.
			for (int i = 0; i < 10; i++)
			{
				Vector2f newPoint = generateMp(vertices[rand() % 3], points[points.size() - 1]);
				points.push_back(newPoint);
			}
			
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		window.draw(instructions);
		swagMario.setPosition(0, 700);
		window.draw(swagMario);
		rapMario.setPosition(1300, 700);
		window.draw(rapMario);
		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(Color::Blue);
		    window.draw(rect);
		}
		for (int i = 0; i < points.size(); i++)
		{
			CircleShape point;
			point.setRadius(2);
			point.setPosition(points[i]);
			point.setFillColor(Color::Red);
			window.draw(point);
		}
		window.display();
	}
}
