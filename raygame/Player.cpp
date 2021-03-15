#include "Player.h"
#include "Game.h"
#include "Scene.h"
#include "raylib.h"
#include <iostream>
#include "Bullet.h"

Player::Player(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float maxForce) : Character(x, y, collisionRadius, spriteFilePath, maxSpeed, maxForce)
{
}

void Player::update(float deltatime)
{
    //Gets the player's input to determine which direction the actor will move on each axis 
    int xDirection = -Game::getKeyDown(KEY_A) + Game::getKeyDown(KEY_D);
    int yDirection = -Game::getKeyDown(KEY_W) + Game::getKeyDown(KEY_S);
    
    setAcceleration(MathLibrary::Vector2(xDirection, yDirection));

    if (getVelocity().getMagnitude() > 0)
        lookAt(getWorldPosition() + getVelocity().getNormalized());

    if (Game::getKeyPressed(KEY_SPACE))
        Game::getCurrentScene()->addActor(new Bullet(
            getWorldPosition().x, getWorldPosition().y, 2, "Images/bullet.png", 5, getForward() * 5));

    //Checks if the player goes outside the bounds of the screen.
    //If so the enemy is teleported to the other side
    if (getWorldPosition().x > Game::getScreenWidth() / 32)
        setWorldPostion(MathLibrary::Vector2(0, getWorldPosition().y));

    if (getWorldPosition().x < 0)
        setWorldPostion(MathLibrary::Vector2(Game::getScreenWidth() / 32, getWorldPosition().y));

    if (getWorldPosition().y > Game::getScreenWidth() / 32)
        setWorldPostion(MathLibrary::Vector2(getWorldPosition().x, 0));

    if (getWorldPosition().y < 0)
        setWorldPostion(MathLibrary::Vector2(getWorldPosition().x, Game::getScreenHeight() / 32));

    Actor::update(deltatime);

    if (getHealth() <= 0)
        Game::destroy(this);
}

void Player::debug()
{

    std::cout << "X: " << getVelocity().x << std::endl << "Y: "<< getVelocity().y << std::endl;
}
