#pragma once

#include"SFML/Graphics.hpp"
#include<iostream>
#include<sstream> 
#include<string>  

#include "Bullet.h"

class Player {

private:
	sf::CircleShape player;
	sf::RectangleShape enemy;
	int spawnTimer = 80;

public:
	Player();
	void move(sf::CircleShape& player);
	void followMouse(sf::CircleShape& player, sf::RenderWindow& window, sf::Vector2f& aimDirNorm);
	void spawnEnemyAndSetThemInRandomPos(sf::RectangleShape& enemy, std::vector<sf::RectangleShape>& enemies, int& spawnTimer, sf::RenderWindow& window);
	void fire(std::vector<Bullet>& bullets, std::vector<sf::RectangleShape>& enemies, sf::RenderWindow& window);
	void outOfBounds(sf::CircleShape& player);
	void Draw(sf::RenderWindow& window);
	void drawEnemy(const std::vector<sf::RectangleShape>& enemies, sf::RenderWindow& window);


	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;


};
