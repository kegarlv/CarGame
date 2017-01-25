#ifndef SFML_LEVEL_H
#define SFML_LEVEL_H

#include <bits/stdc++.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Box2D/Box2D.h>

#include "Loader.h"
#include "Object.h"
#include "car.h"


class Level {
    b2World* world;

    Loader loader;

    b2Body *playerBody = nullptr;

    Object* player;

    std::vector<sf::RectangleShape> debugBoxes;
    std::vector<sf::ConvexShape> debugConvex;
    std::vector<b2Fixture*> staticFixtures;
    std::vector<b2Fixture*> coinFixtures;

    Car *car;

public:
    Level(std::string lvlName);
    ~Level();
    void draw(sf::RenderWindow &window, sf::View &view);

    std::set<sf::Keyboard::Key>  getPressedKeys();
};


#endif //SFML_LEVEL_H
