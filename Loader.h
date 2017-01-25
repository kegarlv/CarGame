#ifndef SFML_LOADER_H
#define SFML_LOADER_H

#include <bits/stdc++.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <tinyxml.h>

#include "Object.h"


class Loader {

public:

    Loader();
    ~Loader();

    void draw(sf::RenderWindow &window);

    bool loadFromFile(std::string filename);
    Object* getObject(std::string name);
    std::vector<Object *> &getObjects(std::string name);
    std::vector<Object *> &getObjLayers(std::string name);

    const sf::Vector2i &getTileSize() const;
private:
    struct Layer {
        int opacity;
        std::string name;
        std::vector<sf::Sprite> tiles;
    };

    sf::Vector2i tileSize;
    int width, height;
    int firstTileId;
    sf::Rect<float> drawingBonds;
    sf::Texture tilesetImage;
    std::vector<Object*> objects;
    std::map<std::string,std::vector<Object*> > objLayers;
    std::vector<Layer> layers;
};


#endif //SFML_LOADER_H
