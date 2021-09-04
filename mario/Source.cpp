#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include "Menu.h"
#include<iostream>
#include<sstream>
void game();
int page_number; //function which returns the index is recieved in this variable
using namespace sf;
using namespace std;

Vector2f bottomLeft, topRight, topLeft, bottomRight;

class dimention
{
public:
	Vector2f bottomLeft, topRight, topLeft, bottomRight;

	void setPosition(Sprite marios)
	{
		//define points/places where  the sprite can collide: topleft, topright,bottomleft,bottomright 
		float width = marios.getTextureRect().width;
		float height = marios.getTextureRect().height;
		topRight.x = marios.getPosition().x + width;
		topRight.y = marios.getPosition().y;
		bottomLeft.x = marios.getPosition().x;
		bottomLeft.y = marios.getPosition().y + height;
		bottomRight.x = marios.getPosition().x + width;
		bottomRight.y = marios.getPosition().y + height;
		topLeft.x = marios.getPosition().x;
		topLeft.y = marios.getPosition().y;
	}
};
Vector2f ctopLeft[8], ctopRight[8], cbottomLeft[8], cbottomRight[8]; //short  columns
Vector2f c2topLeft[4], c2topRight[4], c2bottomLeft[4], c2bottomRight[4]; //c2 ,c4, c11,c12 long columns columns
Vector2f gtopLeft[11], gtopRight[11]; //for ground



bool colRight()
{
	bool r = 1;

	for (int i = 0; i < 8; i++)
	{
		if (bottomRight.x >= cbottomLeft[i].x + 75 && bottomRight.x <= cbottomLeft[i].x + 80)
		{
			if ((bottomRight.y <= cbottomLeft[i].y + 177 && bottomRight.y >= ctopLeft[i].y + 177)
				|| (topRight.y <= cbottomLeft[i].y + 177 && topRight.y >= ctopLeft[i].y + 177))

			{
				r = 0;
			}

		}
		if (r == 0)
			break;
	}

	for (int i = 0; i < 4; i++)
	{
		// 10  from right
		if (bottomRight.x >= c2bottomLeft[i].x + 45 && bottomRight.x <= c2bottomLeft[i].x + 50) // get closer to the column -> collision
		{
			if ((bottomRight.y <= c2bottomLeft[i].y + 150 && bottomRight.y >= c2topLeft[i].y + 150)
				|| (topRight.y <= c2bottomLeft[i].y + 150 && topRight.y >= c2topLeft[i].y + 150))

			{
				r = 0;
			}

		}
		if (r == 0)
			break;
	}


	return r;
}
bool colleft()
{
	bool r = 1;
	for (int i = 0; i < 8; i++)
	{
		if (bottomLeft.x >= cbottomRight[i].x - 30 && bottomLeft.x <= cbottomRight[i].x)
		{
			if ((bottomLeft.y <= cbottomRight[i].y + 250 && bottomLeft.y >= ctopRight[i].y + 200)
				|| (topLeft.y <= cbottomRight[i].y + 250 && topLeft.y >= ctopRight[i].y + 200))

			{
				r = 0;
			}

		}
		if (r == 0)
			break;

	}

	for (int i = 0; i < 4; i++)
	{
		if (bottomLeft.x >= c2bottomRight[i].x - 315 && bottomLeft.x <= c2bottomRight[i].x - 265)
		{
			if ((bottomLeft.y <= c2bottomRight[i].y + 300 && bottomLeft.y >= c2topRight[i].y + 200)
				|| (topLeft.y <= c2bottomRight[i].y + 300 && topLeft.y >= c2topRight[i].y + 200))

			{
				r = 0;
			}

		}
		if (r == 0)
			break;
	}


	return r;
}
bool colBottom()
{
	bool r = 1;
	for (int i = 0; i < 8; i++)
	{
		if (bottomLeft.y >= ctopRight[i].y + 170)
		{
			if ((bottomLeft.x <= ctopRight[i].x - 30 && bottomLeft.x >= ctopLeft[i].x + 30)
				|| (bottomRight.x <= ctopRight[i].x - 85 && bottomRight.x >= ctopLeft[i].x + 85))

			{
				r = 0;
			}

		}
		if (r == 0)
			break;
	}
	for (int i = 0; i < 4; i++)
	{
		if (bottomLeft.y >= c2topRight[i].y + 134)
		{
			if ((bottomLeft.x <= c2topRight[i].x - 320 && bottomLeft.x >= c2topLeft[i].x + 20)
				|| (bottomRight.x <= c2topRight[i].x - 320 && bottomRight.x >= c2topLeft[i].x + 20))

			{
				r = 0;
			}

		}
		if (r == 0)
			break;
	}


	//Ground 
	for (int i = 0; i < 11; i++)
	{
		if (bottomLeft.y >= gtopRight[i].y + 135)
		{
			if ((bottomLeft.x <= gtopRight[i].x && bottomLeft.x >= gtopLeft[i].x + 50)
				|| (bottomRight.x <= gtopRight[i].x && bottomRight.x >= gtopLeft[i].x + 50))
			{
				r = 0;
			}

		}

		if (r == 0)
			break;
	}

	return r;
}

int main()
{
	sf::RenderWindow window2(sf::VideoMode(1400, 800), "super mario");
	Menuu menu(1400, 800); //object from class

	sf::Texture Menubackgound;
	sf::Sprite backgroundsprite;

	if (!Menubackgound.loadFromFile("main menu.png"))
		cout << "Could not load backimg.jpg";
	else
	{
		sf::Vector2u TextureSize = Menubackgound.getSize();//get the size of the texture and the window
		sf::Vector2u WindowSize = window2.getSize();

		float ScaleX = (float)WindowSize.x / TextureSize.x;// get the scale of the sprite
		float ScaleY = (float)WindowSize.y / TextureSize.y;

		backgroundsprite.setTexture(Menubackgound);
		backgroundsprite.setScale(ScaleX, ScaleY); //Set scale.  
	}

	while (window2.isOpen())
	{
		sf::Event event;
		while (window2.pollEvent(event))
		{
			switch (event.type)
			{

			case::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.moveUp();
					break;
				case sf::Keyboard::Down:
					menu.moveDown();
					break;
				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						window2.close();
						page_number = 0; //takes the index in page_number
						break;

					case 1:
						window2.close();
						page_number = 1;
						break;
					}
					break;
				}
				break;
			case sf::Event::Closed:
				window2.close();
				page_number = 1;
				break;
			}
		}

		window2.clear();
		window2.draw(backgroundsprite);
		menu.draw(window2);
		window2.display();


	}
	if (page_number == 0)
		game();
	if (page_number == 1)
		window2.close();



	return 0;
}

void game() {
	Texture background, sky, column, column1, castle, flag;
	Sprite p0, p00, p000, p0000, p00000, p000000, p0000000, p00000000, p000000000, p0000000000, p00000000000, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14;
	Sprite c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, castles, flags;

	View view(Vector2f(0.0f, 0.0f), Vector2f(1400, 800));
	RenderWindow window(VideoMode(1400, 800), "super mario");


	dimention dm;

	//////.....................mario...............................................................
	Texture mario;
	Sprite smario;

	smario.setPosition(Vector2f(600.f, 534));

	mario.loadFromFile("moving mario.png");
	//if (!mario.loadFromFile("mario.png")) {
		//cout << "error loading mario img" << endl;}

	smario.setTexture(mario);
	smario.setTextureRect(IntRect(0, 0, 90, 300));
	int animation_indicator = 0;
	//smario.setScale(Vector2f(0.9, 0.9));
	dm.setPosition(smario);
	bottomRight = dm.bottomRight;
	smario.setOrigin(Vector2f(bottomRight.x / 2 - 310, bottomRight.y / 2 - 415));



	//.............................coins .............................................................
	Texture coin;
	Sprite scoin, scoin1, scoin2, scoin3, scoin4, scoin5, scoin6, scoin7, scoin8, scoin9, scoin10, scoin11, scoin12;
	coin.loadFromFile("textures/coin.png");
	scoin.setTexture(coin);
	scoin.setScale(Vector2f(0.6f, 0.6f));
	scoin.setPosition(Vector2f(2000, 642));
	scoin1.setTexture(coin);
	scoin1.setScale(Vector2f(0.6f, 0.6f));
	scoin1.setPosition(Vector2f(1900, 642));
	scoin2.setTexture(coin);
	scoin2.setScale(Vector2f(0.6f, 0.6f));
	scoin2.setPosition(Vector2f(1800, 642));
	scoin3.setTexture(coin);
	scoin3.setScale(Vector2f(0.6f, 0.6f));
	scoin3.setPosition(Vector2f(8700, 642));
	scoin4.setTexture(coin);
	scoin4.setScale(Vector2f(0.6f, 0.6f));
	scoin4.setPosition(Vector2f(8900, 642));
	scoin5.setTexture(coin);
	scoin5.setScale(Vector2f(0.6f, 0.6f));
	scoin5.setPosition(Vector2f(9100, 642));
	scoin6.setTexture(coin);
	scoin6.setScale(Vector2f(0.6f, 0.6f));
	scoin6.setPosition(Vector2f(14000, 642));
	scoin7.setTexture(coin);
	scoin7.setScale(Vector2f(0.6f, 0.6f));
	scoin7.setPosition(Vector2f(14910, 520));
	scoin8.setTexture(coin);
	scoin8.setScale(Vector2f(0.6f, 0.6f));
	scoin8.setPosition(Vector2f(15100, 520));
	scoin9.setTexture(coin);
	scoin9.setScale(Vector2f(0.6f, 0.6f));
	scoin9.setPosition(Vector2f(13600, 642));
	scoin10.setTexture(coin);
	scoin10.setScale(Vector2f(0.6f, 0.6f));
	scoin10.setPosition(Vector2f(13900, 642));
	scoin11.setTexture(coin);
	scoin11.setScale(Vector2f(0.6f, 0.6f));
	scoin11.setPosition(Vector2f(14200, 642));
	scoin12.setTexture(coin);
	scoin12.setScale(Vector2f(0.6f, 0.6f));
	scoin12.setPosition(Vector2f(14500, 642));
	//........................................enemy.....................................................................

	Texture enemy;
	Sprite senemy;
	enemy.loadFromFile("textures/enemy.png");
	senemy.setTexture(enemy);

	senemy.setPosition(2500, 630);
	senemy.setScale(2.33, 2.33);





	//.........scoreee.............lives.................texts................................
	int score = 0;
	Font font;
	font.loadFromFile("arial.ttf");
	ostringstream ssScore;
	ssScore << "SCORE " << score;
	Text lblScore;
	lblScore.setCharacterSize(30);
	lblScore.setPosition(70, 70);
	lblScore.setFont(font);
	lblScore.setString(ssScore.str());



	int lives = 3;
	ostringstream slive;
	slive << "LIVES " << lives;
	Text live;
	live.setCharacterSize(30);
	live.setPosition(70, 100);
	live.setFont(font);
	live.setString(slive.str());


	Font font1;
	font1.loadFromFile("main_font.ttf");
	Text gameover;
	gameover.setCharacterSize(100);
	gameover.setPosition(350, 300);
	gameover.setFont(font1);
	gameover.setString("GAME OVER");


	//..................................audio................................................................................

	Music playback;


	if (!playback.openFromFile("mario.ogg"))
	{
		cout << "error playing super mario music" << endl;
	}

	playback.play();
	playback.setLoop(true);



	//............................................................................................................
	if (!sky.loadFromFile("textures/sky2.png")) {
		cout << "error in background image" << endl;
	}
	p0.setTexture(sky);
	p0.setScale(Vector2f(0.6, 0.577));
	p0.setPosition(Vector2f(0, -950));
	p00.setTexture(sky);
	p00.setScale(Vector2f(0.6, 0.576));
	p00.setPosition(Vector2f(1520, -950));
	p000.setTexture(sky);
	p000.setScale(Vector2f(0.6, 0.576));
	p000.setPosition(Vector2f(3040, -950));
	p0000.setTexture(sky);
	p0000.setScale(Vector2f(0.6, 0.576));
	p0000.setPosition(Vector2f(4560, -950));
	p00000.setTexture(sky);
	p00000.setScale(Vector2f(0.6, 0.576));
	p00000.setPosition(Vector2f(6080, -950));
	p000000.setTexture(sky);
	p000000.setScale(Vector2f(0.6, 0.576));
	p000000.setPosition(Vector2f(7600, -950));
	p0000000.setTexture(sky);
	p0000000.setScale(Vector2f(0.6, 0.576));
	p0000000.setPosition(Vector2f(9120, -950));
	p00000000.setTexture(sky);
	p00000000.setScale(Vector2f(0.6, 0.576));
	p00000000.setPosition(Vector2f(10640, -950));
	p000000000.setTexture(sky);
	p000000000.setScale(Vector2f(0.6, 0.576));
	p000000000.setPosition(Vector2f(12160, -950));
	p0000000000.setTexture(sky);
	p0000000000.setScale(Vector2f(0.6, 0.576));
	p0000000000.setPosition(Vector2f(13680, -950));
	p00000000000.setTexture(sky);
	p00000000000.setScale(Vector2f(0.6, 0.576));
	p00000000000.setPosition(Vector2f(15200, -950));



	if (!background.loadFromFile("textures/blocks.png")) {
		cout << "error in background image" << endl;
	}
	p1.setTexture(background);
	p1.setPosition(Vector2f(0, 700));
	p2.setTexture(background);
	p2.setPosition(Vector2f(1520, 700));
	p3.setTexture(background);
	p3.setPosition(Vector2f(3040, 700));
	p4.setTexture(background);
	p4.setPosition(Vector2f(4560, 700));
	p5.setTexture(background);
	p5.setPosition(Vector2f(6250, 700));
	p6.setTexture(background);
	p6.setPosition(Vector2f(7900, 700));
	p7.setTexture(background);
	p7.setPosition(Vector2f(9420, 700));
	p8.setTexture(background);
	p8.setPosition(Vector2f(10940, 700));
	p9.setTexture(background);
	p9.setPosition(Vector2f(12620, 700));
	p10.setTexture(background);
	p10.setPosition(Vector2f(14140, 700));
	p11.setTexture(background);
	p11.setScale(Vector2f(0.71, 1));
	p11.setPosition(Vector2f(15660, 700));


	if (!column.loadFromFile("textures/column1.png")) {
		cout << "error in background image" << endl;
	}
	c1.setTexture(column);
	c1.setPosition(Vector2f(2200, 540));
	c3.setTexture(column);
	c3.setPosition(Vector2f(3800, 540));
	c5.setTexture(column);
	c5.setPosition(Vector2f(5400, 540));
	c6.setTexture(column);
	c6.setPosition(Vector2f(12575, 540));
	c7.setTexture(column);
	c7.setPosition(Vector2f(14850, 540));

	c8.setTexture(column);
	c8.setPosition(Vector2f(10400, 540));

	c9.setTexture(column);
	c9.setPosition(Vector2f(8300, 540));


	c10.setTexture(column);
	c10.setPosition(Vector2f(15030, 540));




	if (!column1.loadFromFile("textures/column2.png")) {
		cout << "error in background image" << endl;
	}
	c2.setTexture(column1);  //-> to staart with this sprite 
	c2.setPosition(Vector2f(3000, 496));
	c2.setScale(Vector2f(0.3, 0.3));
	c4.setTexture(column1);
	c4.setPosition(Vector2f(4500, 496));
	c4.setScale(Vector2f(0.3, 0.3));


	c11.setTexture(column1);
	c11.setPosition(Vector2f(6800, 496));
	c11.setScale(Vector2f(0.3, 0.3));
	c12.setTexture(column1);
	c12.setPosition(Vector2f(12355, 496));
	c12.setScale(Vector2f(0.3, 0.3));





	if (!castle.loadFromFile("textures/castle.png")) {
		cout << "error in background image" << endl;
	}
	castles.setTexture(castle);
	castles.setPosition(Vector2f(15860, 440));
	castles.setScale(Vector2f(0.22, 0.22));

	if (!flag.loadFromFile("textures/flag.png")) {
		cout << "error in background image" << endl;
	}

	flags.setTexture(flag);
	flags.setPosition(Vector2f(15500, 446));
	flags.setScale(Vector2f(0.3, 0.3));

	//..........................................................................

	bool draw = true;
	bool draw1 = true;
	bool draw2 = true;
	bool draw3 = true;
	bool draw4 = true;
	bool draw5 = true;
	bool draw6 = true;
	bool draw7 = true;
	bool draw8 = true;
	bool draw9 = true;
	bool draw10 = true;
	bool draw11 = true;
	bool draw12 = true;


	bool enemymove = 1;
	bool isjumping = false;

	Clock timer;
	bool win = 0;
	Music gameovers;

	if (!gameovers.openFromFile("gameover.ogg"))
	{
		cout << "error playing gameover music" << endl;
	}

	Music endgame;

	if (!endgame.openFromFile("endgame.ogg"))
	{
		cout << "error playing endgame music" << endl;
	}
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{

			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyReleased:
				isjumping = false;
			}


		}

		//mario moves
		if (Keyboard::isKeyPressed(Keyboard::A) && colleft() && smario.getPosition().x >= 600 && win == 0 && lives >= 0) {

			smario.move(-2.f, 0.f);
			animation_indicator++;
			smario.setScale(-1.0, 1);
			lblScore.move(-2, 0);
			live.move(-2, 0);
			if (smario.getGlobalBounds().intersects(scoin.getGlobalBounds()))
			{

				score++;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin1.getGlobalBounds()))
			{

				score++;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin1.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin2.getGlobalBounds()))
			{

				score++;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin2.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin3.getGlobalBounds()))
			{

				score++;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin3.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin4.getGlobalBounds()))
			{

				score++;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin4.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin5.getGlobalBounds()))
			{

				score++;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin5.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin6.getGlobalBounds()))
			{

				score++;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin6.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin7.getGlobalBounds()))
			{

				score++;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin7.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin8.getGlobalBounds()))
			{

				score++;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin8.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin9.getGlobalBounds()))
			{

				score++;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin9.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin10.getGlobalBounds()))
			{

				score++;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin10.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin11.getGlobalBounds()))
			{

				score++;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin11.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin12.getGlobalBounds()))
			{

				score++;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin12.setPosition(-100, -100);

			}

		}


		if (Keyboard::isKeyPressed(Keyboard::D) && colRight() && smario.getPosition().x < 15940 && win == 0 && lives>0)
		{
			smario.move(2.f, 0.f);
			animation_indicator++;
			smario.setScale(1.0, 1.0);
			lblScore.move(2, 0);
			live.move(2, 0);
			if (smario.getGlobalBounds().intersects(scoin.getGlobalBounds()))
			{
				score += 100;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin.setPosition(-100, -100);

			}
			if (smario.getGlobalBounds().intersects(scoin1.getGlobalBounds()))
			{

				score += 100;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin1.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin2.getGlobalBounds()))
			{

				score += 100;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin2.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin3.getGlobalBounds()))
			{
				score += 100;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin3.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin4.getGlobalBounds()))
			{
				score += 100;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin4.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin5.getGlobalBounds()))
			{
				score += 100;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin5.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin6.getGlobalBounds()))
			{
				score += 100;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin6.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin7.getGlobalBounds()))
			{
				score += 100;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin7.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin8.getGlobalBounds()))
			{
				score += 100;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin8.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin9.getGlobalBounds()))
			{
				score += 100;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin9.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin10.getGlobalBounds()))
			{
				score += 100;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin10.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin11.getGlobalBounds()))
			{
				score += 100;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin11.setPosition(-100, -100);
			}
			if (smario.getGlobalBounds().intersects(scoin12.getGlobalBounds()))
			{
				score += 100;
				ssScore.str("");
				ssScore << "SCORE " << score;
				lblScore.setString(ssScore.str());
				scoin12.setPosition(-100, -100);
			}
		}

		//gravity.........................................................................................
		const int groundheight = 850;

		const float gravityspeed = 3;
		const float movespeed = 3;
		if (Keyboard::isKeyPressed(Keyboard::Space) && win == 0 && lives >= 0 && smario.getPosition().y)
		{
			smario.setTextureRect(IntRect(animation_indicator * 80, 0, 75, 300));
			smario.move(0.0f, -movespeed);
			isjumping = true;

		}
		if (smario.getPosition().y <= groundheight && colBottom() && isjumping == false)
		{
			smario.move(0, gravityspeed);

		}

		else if (smario.getPosition().y >= groundheight - 300) {
			if (lives > 0)
				lives--;


			smario.setPosition(Vector2f(600.f, 534));
			lblScore.setPosition(Vector2f(70.f, 70));
			live.setPosition(Vector2f(70.f, 100));



			slive.str("");
			slive << "LIVES " << lives;
			live.setString(slive.str());

		}

		if (lives == 0) {
			timer.restart();

			//....end 1st fucken audio....
			playback.stop();
			//..................text gameover............

			gameovers.play();
			lives = -1;

		}


		else if (smario.getPosition().x >= 15935 && win == 0)
		{
			timer.restart();

			//.....end 1st audio.....
			playback.stop();
			endgame.play();

			win = 1;
		}
		if (timer.getElapsedTime().asSeconds() >= 5 && win == 1)
		{

			window.close();
			main();
		}

		if (timer.getElapsedTime().asSeconds() >= 5 && lives == -1)
		{

			window.close();
			main();
		}
		if (senemy.getPosition().x)
		{
			senemy.move(0.3, 0);
		}
		if (smario.getGlobalBounds().intersects(senemy.getGlobalBounds()))
		{
			if (lives > 0)
				lives--;


			smario.setPosition(Vector2f(600.f, 534));
			lblScore.setPosition(Vector2f(70.f, 70));
			live.setPosition(Vector2f(70.f, 100));



			slive.str("");
			slive << "LIVES " << lives;
			live.setString(slive.str());
		}

		//updatee..........................................................................................
		animation_indicator %= 4;
		smario.setTextureRect(IntRect(animation_indicator * 80, 0, 75, 300));
		view.setCenter(smario.getPosition().x + 100, smario.getPosition().y - 120);








		//...................collision.................

		dm.setPosition(smario);
		topLeft = dm.topLeft;
		topRight = dm.topRight;
		bottomLeft = dm.bottomLeft;
		bottomRight = dm.bottomRight;

		//short columns
		dm.setPosition(c1);
		ctopLeft[0] = dm.topLeft;
		ctopRight[0] = dm.topRight;
		cbottomLeft[0] = dm.bottomLeft;
		cbottomRight[0] = dm.bottomRight;

		dm.setPosition(c3);
		ctopLeft[1] = dm.topLeft;
		ctopRight[1] = dm.topRight;
		cbottomLeft[1] = dm.bottomLeft;
		cbottomRight[1] = dm.bottomRight;

		dm.setPosition(c5);
		ctopLeft[2] = dm.topLeft;
		ctopRight[2] = dm.topRight;
		cbottomLeft[2] = dm.bottomLeft;
		cbottomRight[2] = dm.bottomRight;

		dm.setPosition(c6);
		ctopLeft[3] = dm.topLeft;
		ctopRight[3] = dm.topRight;
		cbottomLeft[3] = dm.bottomLeft;
		cbottomRight[3] = dm.bottomRight;

		dm.setPosition(c7);
		ctopLeft[4] = dm.topLeft;
		ctopRight[4] = dm.topRight;
		cbottomLeft[4] = dm.bottomLeft;
		cbottomRight[4] = dm.bottomRight;

		dm.setPosition(c8);
		ctopLeft[5] = dm.topLeft;
		ctopRight[5] = dm.topRight;
		cbottomLeft[5] = dm.bottomLeft;
		cbottomRight[5] = dm.bottomRight;

		dm.setPosition(c9);
		ctopLeft[6] = dm.topLeft;
		ctopRight[6] = dm.topRight;
		cbottomLeft[6] = dm.bottomLeft;
		cbottomRight[6] = dm.bottomRight;

		dm.setPosition(c10);
		ctopLeft[7] = dm.topLeft;
		ctopRight[7] = dm.topRight;
		cbottomLeft[7] = dm.bottomLeft;
		cbottomRight[7] = dm.bottomRight;



		//long columns
		dm.setPosition(c2);
		c2topLeft[0] = dm.topLeft;
		c2topRight[0] = dm.topRight;
		c2bottomLeft[0] = dm.bottomLeft;
		c2bottomRight[0] = dm.bottomRight;

		dm.setPosition(c4);
		c2topLeft[1] = dm.topLeft;
		c2topRight[1] = dm.topRight;
		c2bottomLeft[1] = dm.bottomLeft;
		c2bottomRight[1] = dm.bottomRight;


		dm.setPosition(c11);
		c2topLeft[2] = dm.topLeft;
		c2topRight[2] = dm.topRight;
		c2bottomLeft[2] = dm.bottomLeft;
		c2bottomRight[2] = dm.bottomRight;

		dm.setPosition(c12);
		c2topLeft[3] = dm.topLeft;
		c2topRight[3] = dm.topRight;
		c2bottomLeft[3] = dm.bottomLeft;
		c2bottomRight[3] = dm.bottomRight;



		//Ground
		dm.setPosition(p1);
		gtopRight[0] = dm.topRight;
		gtopLeft[0] = dm.topLeft;


		dm.setPosition(p2);
		gtopRight[1] = dm.topRight;
		gtopLeft[1] = dm.topLeft;



		dm.setPosition(p3);
		gtopRight[2] = dm.topRight;
		gtopLeft[2] = dm.topLeft;


		dm.setPosition(p4);
		gtopRight[3] = dm.topRight;
		gtopLeft[3] = dm.topLeft;


		dm.setPosition(p5);
		gtopRight[4] = dm.topRight;
		gtopLeft[4] = dm.topLeft;
		;

		dm.setPosition(p6);
		gtopRight[5] = dm.topRight;
		gtopLeft[5] = dm.topLeft;



		dm.setPosition(p7);
		gtopRight[6] = dm.topRight;
		gtopLeft[6] = dm.topLeft;

		dm.setPosition(p8);
		gtopRight[7] = dm.topRight;
		gtopLeft[7] = dm.topLeft;

		dm.setPosition(p9);
		gtopRight[8] = dm.topRight;
		gtopLeft[8] = dm.topLeft;


		dm.setPosition(p10);
		gtopRight[9] = dm.topRight;
		gtopLeft[9] = dm.topLeft;


		dm.setPosition(p11);
		gtopRight[10] = dm.topRight;
		gtopLeft[10] = dm.topLeft;

		window.setView(view);


		window.clear();
		//draw::::::::::::::::::::::::::::::::::::::
		window.draw(p0);
		window.draw(p00);
		window.draw(p000);
		window.draw(p0000);
		window.draw(p00000);
		window.draw(p000000);
		window.draw(p0000000);
		window.draw(p00000000);
		window.draw(p000000000);
		window.draw(p0000000000);
		window.draw(p00000000000);

		window.draw(p1);
		window.draw(p2);
		window.draw(p3);
		window.draw(p4);
		window.draw(p5);
		window.draw(p6);
		window.draw(p7);
		window.draw(p8);
		window.draw(p9);
		window.draw(p10);
		window.draw(p11);
		window.draw(p12);
		window.draw(p13);
		window.draw(p14);


		window.draw(c1);
		window.draw(c2);
		window.draw(c3);
		window.draw(c4);
		window.draw(c5);
		window.draw(c6);
		window.draw(c7);
		window.draw(c8);
		window.draw(c9);
		window.draw(c10);
		window.draw(c11);
		window.draw(c12);
		window.draw(castles);
		window.draw(flags);


		window.draw(senemy);




		//if (draw == true)

		window.draw(scoin);



		window.draw(scoin1);
		//if (draw2 == true)
		window.draw(scoin2);
		//if (draw3 == true)
		window.draw(scoin3);
		//if (draw4 == true)
		window.draw(scoin4);
		//if (draw5 == true)
		window.draw(scoin5);
		//if (draw6 == true)
		window.draw(scoin6);
		//if (draw7 == true)
		window.draw(scoin7);
		//if (draw8 == true)
		window.draw(scoin8);
		//if (draw9 == true)
		window.draw(scoin9);
		//if (draw10 == true)
		window.draw(scoin10);
		//if (draw11 == true)
		window.draw(scoin11);
		//if (draw12 == true)
		window.draw(scoin12);
		window.draw(lblScore);

		window.draw(live);
		if (lives <= 0)
			window.draw(gameover);


		window.draw(smario);




		window.display();

	}

}