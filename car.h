#ifndef CAR_H
#define CAR_H

#include <bits/stdc++.h>

#include "Object.h"

#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>

class Car
{
public:
    Car(b2World *world, b2Vec2 position);
    ~Car();

    void draw(sf::RenderWindow &window);

    void moveRight();
    void moveLeft();
    sf::Vector2f getCenter();

private:
    CircleObject *carWheel1, *carWheel2;
    RectangleObject *carBody;

    b2BodyDef  *b2CarBodyDef;
    b2Body *b2CarBody;
    b2Fixture *b2CarFixture;
    b2Fixture *b2CarWheel1Fixture, *b2CarWheel2Fixture;
    b2RevoluteJoint *joint1, *joint2;
};

#endif // CAR_H
