#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

int main()
{
	const int tabSize = 4;
	int licznik = 0;
	int liczZebTul = 0;
	int* wsk = &liczZebTul;
	sf::Time t1 = sf::microseconds(10000);
	sf::Clock clock;
	sf::Time elapsed1 = clock.getElapsedTime();
	

	const float maxY = 9.8f;																	//g grawitacji
	const sf::Vector2f gravity(0.f, 5.f);														//nie wiem
	sf::Vector2f velocity(2.f, 5.f);																//nie wiem


	sf::RenderWindow window(sf::VideoMode(1280, 1024,32), "Bieda Gra");	
	window.setFramerateLimit(60); //inicjalizacja okna
	sf::View view;
	
																								//inicjalicacja widoku
	sf::Font font;
	if (!font.loadFromFile("fonts/Amatic-bold.ttf"))
	{
		// error...
		return EXIT_FAILURE;
		
	}

	sf::Texture texture[tabSize];																		//inicjalizacja tekstury "bohatera"
	if ((!texture[0].loadFromFile("textures/ja.jpg")) || (!texture[1].loadFromFile("textures/ja2.jpg")) || (!texture[2].loadFromFile("textures/ja_swieta.jpg"))
		|| (!texture[3].loadFromFile("textures/tulipan.png")))														//warunek
		return EXIT_FAILURE;
	sf::Sprite sprite(texture[0]);																					//inicjalizacja bohatyra
	

	sf::RectangleShape floor(sf::Vector2f(10000.f, 40.f));
	floor.setPosition(0.f, 1000.f);
	floor.setFillColor(sf::Color(10, 180, 30));

	

	sf::Sprite tulip;
	tulip.setTexture(texture[3]);
	tulip.setPosition(550.f, 600.f);

	sf::Sprite blocks[17];

	sf::Text text;
	text.setFont(font);
	text.setString("JAKIS NAPIS");
	text.setCharacterSize(120);
	text.setColor(sf::Color::Blue);
	text.setPosition(700.f, 800.f);



	sf::Text licz;
	licz.setFont(font);
	licz.setCharacterSize(150);
	licz.setColor(sf::Color::Blue);
	

	for (licznik; licznik < 17; licznik++){
		blocks[licznik] = tulip;
		}
	for (int y = 1; y < 17; y++) {
		blocks[y].setPosition(blocks[y - 1].getPosition().x + 70.f, blocks[y - 1].getPosition().y);
		
	}

	while (window.isOpen())
	{
		
		
		////////////////////////////////////////////////////////////////////////////////          zbieranie tulipanow
		for (int i = 0; i < 17; i++) {
			if (sprite.getGlobalBounds().intersects(blocks[i].getGlobalBounds()))
			{
				blocks[i].setPosition(blocks[i].getPosition().x, (blocks[i].getPosition().y - 100.f));
				blocks[i].setRotation(-90.f);
				liczZebTul++;
				licz.setString(std::to_string(liczZebTul));
			}
			licz.setString(std::to_string(liczZebTul));
		}
		
		licz.setPosition(sprite.getPosition().x - 100, sprite.getPosition().y - 100);
		//pseudograwitacja
		if (sprite.getGlobalBounds().intersects(floor.getGlobalBounds())) {
		}
		else {
			sprite.move(velocity);
			if (velocity.y < maxY) velocity += gravity;
		}
		
		/////////////////////////////////////////////////////////////////
		//scrolling
		if (sprite.getPosition().x > 1200) {
			view.setCenter(sprite.getPosition());
			sf::Vector2f cam(1280.f, 1024.f);
			view.setSize(cam);
			window.setView(view);
			
			
		}

		///////////////////////////////////////////////////////////////
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// left key is pressed: move our character
			sprite.move(-10, 0);	
			sprite.setTexture(texture[1]);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			// left key is pressed: move our character
			sprite.move(10, 0);
			sprite.setTexture(texture[0]);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			// left key is pressed: move our character
			sprite.move(0, -20);
			sprite.setTexture(texture[2]);
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			
				if (sprite.getGlobalBounds().intersects(blocks[0].getGlobalBounds()))
				{
					//blocks[i].setPosition(blocks[i].getPosition().x, (blocks[i].getPosition().y - 100.f));
					//blocks[i].setRotation(-90.f);
					liczZebTul++;

				}
			
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				sprite.setScale(.5f,.5f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			{
				sprite.setScale(1.f, 1.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
			
			//obmyslic strzal	
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}
		

		window.clear();
		window.draw(floor);
		window.draw(sprite);
		//window.draw(text);
		window.draw(licz);
		//window.draw(blocks[0]);
		for (int j = 0; j < 17; j++)
		window.draw(blocks[j]);
		window.display();
	}
	

	return 0;
}