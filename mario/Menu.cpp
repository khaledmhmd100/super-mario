#include "Menu.h"
#include <iostream>
using namespace std;

Menuu::Menuu(float width, float height)
{
	if (!font.loadFromFile("pixelfont.ttf"))
	{
		cout << "Couldn't open file\n";
	}

	mainMenu[0].setFont(font);
	mainMenu[0].setString("Start game");
	mainMenu[0].setFillColor(sf::Color::Blue);
	mainMenu[0].setPosition(sf::Vector2f(560.f,  450.f));
	mainMenu[0].setCharacterSize(30);
	mainMenu[0].setStyle(sf::Text::Style::Bold);
	//.....................................................................................

	mainMenu[1].setFont(font);
	mainMenu[1].setString("Exit");
	mainMenu[1].setFillColor(sf::Color::White);
	mainMenu[1].setPosition(sf::Vector2f(650.f,490.f));
	mainMenu[1].setCharacterSize(30);
	mainMenu[1].setStyle(sf::Text::Style::Bold);
	MainMenuSelected = 0;

}
Menuu::~Menuu()
{

}

void  Menuu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 2; i++)
	{
		window.draw(mainMenu[i]);

	}
}
void Menuu::moveDown()
{
	if (MainMenuSelected + 1 <= Max_main_menu)
	{
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
		MainMenuSelected++;
		if (MainMenuSelected == 2)
		{
			MainMenuSelected = 0;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
	}

}
void Menuu::moveUp()
{
	if (MainMenuSelected - 1 >= -1)
	{
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);//change the previous item's color
		MainMenuSelected--;
		if (MainMenuSelected == -1)
		{
			MainMenuSelected = 1;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
	}

}
