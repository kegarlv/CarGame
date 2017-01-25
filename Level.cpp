#include "Level.h"

#define DEBUG(x) std::cout << #x << " " << x << std::endl;

Level::Level(std::string lvlName) {
    world = new b2World(b2Vec2(0.0f, 100.0f));

    loader.loadFromFile(lvlName);
    auto tileSize = loader.getTileSize();

    for (auto block : loader.getObjLayers("static")) {
        staticFixtures.push_back(block->build(world, tileSize));
    }

    car = new Car(world, b2Vec2(100,100));
}

Level::~Level() {
    delete world;
    delete car;
}

void Level::draw(sf::RenderWindow &window, sf::View &view) {

    world->Step(1.0f / 60, 1, 1);
    auto pressedKeys = getPressedKeys();

    if (pressedKeys.find(sf::Keyboard::D) != pressedKeys.end()) {
        car->moveRight();
    }

    if (pressedKeys.find(sf::Keyboard::A) != pressedKeys.end()) {
        car->moveLeft();
    }
    if (pressedKeys.find(sf::Keyboard::S) != pressedKeys.end()) {
    }

    view.setCenter(car->getCenter() + sf::Vector2f(200,200));
    window.setView(view);

//    DEBUG(car->getCenter().x);
//    DEBUG(car->getCenter().y);

    loader.draw(window);

    car->draw(window);
    for (auto block : loader.getObjLayers("static")) {
        block->draw(window);
    }
}

std::set<sf::Keyboard::Key> Level::getPressedKeys() {
    std::set<sf::Keyboard::Key> res;

    for (int i = 0; i < sf::Keyboard::KeyCount; i++)
        if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i))
            res.insert((sf::Keyboard::Key)i);
    return res;
}
