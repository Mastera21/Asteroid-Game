#pragma once
#include"SFML/Graphics.hpp"
class Bullet {
public:
	sf::CircleShape shape;
	sf::Vector2f currVelocity;
	float maxSpeed;

	Bullet(float radius = 5.f) : currVelocity(0.f, 0.f), maxSpeed(10.f) {
		this->shape.setRadius(radius);
		this->shape.setFillColor(sf::Color::White);
	}

	void drawBullets(const std::vector<Bullet>& bullets, sf::RenderWindow& window) {
		for (size_t i = 0; i < bullets.size(); i++) {
			window.draw(bullets[i].shape);
		}
	}
};