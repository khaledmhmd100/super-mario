#pragma once
#include<SFML/Graphics.hpp>
//number of text
#define Max_main_menu 2
//Write the  header of the function and all the variables you need
class Menuu
{
public:
	//constructor : when you creat an object from this class it implements what's in this constructor
	Menuu(float width, float height);
	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	int GetPressedItem() { return MainMenuSelected; };

	//destructor
	~Menuu();
private:
	int MainMenuSelected;
	sf::Font font;
	//array of main menu text : (start - exit)
	sf::Text mainMenu[Max_main_menu];
};