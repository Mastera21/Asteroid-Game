#include<iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include<math.h>
#include<vector>
#include<cstdlib>
#include<sstream> 
#include<string>  

#include "Bullet.h";
#include "Player.h";

const int W = 1200;
const int H = 680;

bool isPlayerHit(sf::CircleShape& player, std::vector<sf::RectangleShape>& enemies) {
    for (size_t i = 0; i < enemies.size(); i++) {
        if (enemies[i].getGlobalBounds().intersects(player.getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

bool isPlayerOutOfRange(sf::CircleShape& player, sf::RenderWindow& window) {
    auto x = player.getPosition().x;
    auto y = player.getPosition().y;
    auto w = window.getSize().x;
    auto h = window.getSize().y;

    if (x + 1 >= w || x < 0) {
        return true;
    }

    if (y + 1 >= h || y < 0) {
        return true;
    }

    return false;
}

int main() {

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(W, H), "Master21");
    window.setFramerateLimit(60);

    //Player class
    Player playerClass;
    sf::CircleShape player(15.f, 3);
    player.setOrigin(15.f, 15.f);
    player.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    player.setFillColor(sf::Color::Red);

    //Player image
    sf::Texture playerTexture;
    playerTexture.loadFromFile("spaceship.png");
    player.setTexture(&playerTexture);
    player.setTextureRect(sf::IntRect(2, 100, 10, 10));
    
    //Background
    sf::Texture texture;
    texture.loadFromFile("galaxy.jpg");
    sf::Sprite sBackground(texture);
    sf::RenderTexture t;
    t.draw(sBackground);
    sf::Sprite sprite;
    t.create(W, H);
    t.setSmooth(true);
    sprite.setTexture(t.getTexture());
    t.clear();  t.draw(sBackground);

    //Bullet class
    Bullet b1;
    std::vector<Bullet> bullets;

    //Enemys
    sf::RectangleShape enemy(sf::Vector2f(20, 20));
    enemy.setFillColor(sf::Color::Magenta);
    std::vector<sf::RectangleShape>enemies;
    int spawnTimer = 80;

    bool isFire = false;

    sf::Vector2f aimDirNorm;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            isFire = true;
        }

        if (isFire) {
            b1.shape.setPosition(player.getPosition());
            b1.currVelocity = aimDirNorm * b1.maxSpeed;
            //fire once per click
            if (bullets.size() < 1) {
                bullets.push_back(Bullet(b1));
            }
            isFire = false;
        }

        playerClass.move(player);
        playerClass.followMouse(player, window, aimDirNorm);
        playerClass.spawnEnemyAndSetThemInRandomPos(enemy, enemies, spawnTimer, window);
        playerClass.fire(bullets, enemies, window);

        bool gameOver = isPlayerHit(player, enemies);
        if (gameOver) {
            std::cout << "Game Over!" << "\n";
            break;
        }

        //If we go out of range we are returning back from other side
        bool isoutOfRange = isPlayerOutOfRange(player, window);
        if (isoutOfRange) {
            //std::cout << "out of range\n";
            playerClass.outOfBounds(player);
        }
        else {
            //std::cout << "in range\n";
        }

        //Draw things
        window.clear();
        window.draw(sprite);
        playerClass.drawEnemy(enemies, window);
        window.draw(player);
        playerClass.Draw(window);
        b1.drawBullets(bullets, window);
        window.display();
    }

    return 0;
}