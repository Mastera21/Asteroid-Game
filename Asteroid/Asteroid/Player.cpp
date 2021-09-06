#include"SFML/Graphics.hpp"

#include "Player.h";

const int W = 1200;
const int H = 680;

Player::Player() {}

void Player::move(sf::CircleShape& player) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {//up
        player.move(sf::Vector2f(0, -8));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {//donw
        player.move(sf::Vector2f(0, 8));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {//left
        player.move(sf::Vector2f(-8, 0));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {//right
        player.move(sf::Vector2f(8, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {//up right
        player.move(sf::Vector2f(5, 5));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {//up left
        player.move(sf::Vector2f(-5, 5));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {//down left
        player.move(sf::Vector2f(-5, -5));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {//down right
        player.move(sf::Vector2f(5, -5));
    }
}

void Player::followMouse(sf::CircleShape& player, sf::RenderWindow& window, sf::Vector2f& aimDirNorm) {
    sf::Vector2f curPos = player.getPosition();
    sf::Vector2f position = sf::Vector2f(sf::Mouse::getPosition(window));

    const float PI = 3.14159265;

    aimDir = position - curPos;
    auto tt = sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
    aimDirNorm = aimDir / (float)tt;
    float rotation = atan2(aimDirNorm.y, aimDirNorm.x) * 180 / PI;

    player.setRotation(rotation + 90);
}

void Player::spawnEnemyAndSetThemInRandomPos(sf::RectangleShape& enemy, std::vector<sf::RectangleShape>& enemies, int& spawnTimer, sf::RenderWindow& window) {
    if (spawnTimer < 80) {
        spawnTimer++;
    }

    //Enemies are spawning at random pos
    //if (spawnTimer >= 50 /*&& enemies.size() < 10*/) {
    //    //get enemy in random pos
    //    enemy.setPosition(sf::Vector2f(rand() % window.getSize().x, rand() % window.getSize().y));
    //    //spawn enemy
    //    enemies.push_back(sf::RectangleShape(enemy));
    //    spawnTimer = 0;
    //}

    //Enemies are spawning a the top of the screen
    if (spawnTimer >= 80) {
        //get enemy in random pos
        enemy.setPosition(rand() % (int)(window.getSize().x - enemy.getSize().x), 0);
        //spawn enemy
        enemies.push_back(sf::RectangleShape(enemy));
        spawnTimer = 0;
    }

    for (size_t i = 0; i < enemies.size(); i++) {
        enemies[i].move(rand() % 5, 5);
    }
}

void Player::fire(std::vector<Bullet>& bullets, std::vector<sf::RectangleShape>& enemies, sf::RenderWindow& window) {
    for (size_t i = 0; i < bullets.size(); i++) {
        bullets[i].shape.move(bullets[i].currVelocity);

        //if is out of range
        if (bullets[i].shape.getPosition().x < 0 ||
            bullets[i].shape.getPosition().y < 0 ||
            bullets[i].shape.getPosition().x > window.getSize().x ||
            bullets[i].shape.getPosition().y > window.getSize().y) {
            bullets.erase(bullets.begin() + i);
            
        }
        else {
            //enemy collision
            for (size_t j = 0; j < enemies.size(); j++) {
                if (bullets[i].shape.getGlobalBounds().intersects(enemies[j].getGlobalBounds())) {
                    bullets.erase(bullets.begin() + i);
                    enemies.erase(enemies.begin() + j);
                    break;
                }
            }
        }
    }

    for (size_t i = 0; i < enemies.size(); i++) {
        //If the enemy is out of range we are removing them
        if (enemies[i].getPosition().x < 0 ||
            enemies[i].getPosition().y < 0 ||
            enemies[i].getPosition().x > window.getSize().x ||
            enemies[i].getPosition().y > window.getSize().y) {
            enemies.erase(enemies.begin() + i);
        }
    }
}

void Player::outOfBounds(sf::CircleShape& player) {
    if (player.getPosition().x > W) {//Left
        player.move(sf::Vector2f(-W, 0));
    }
    else if (player.getPosition().x < 0) {//Right
        player.move(sf::Vector2f(W, 0));
    }

    if (player.getPosition().y > H) {//Down
        player.move(sf::Vector2f(0, -H));
    }
    else if (player.getPosition().y < 0) {//Up
        player.move(sf::Vector2f(0, H));
    }
}

void Player::drawEnemy(const std::vector<sf::RectangleShape>& enemies, sf::RenderWindow& window) {
    for (size_t i = 0; i < enemies.size(); i++) {
        window.draw(enemies[i]);
    }
}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(player);
}
