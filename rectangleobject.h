#ifndef RECTANGLEOBJECT_H
#define RECTANGLEOBJECT_H

#include <bits/stdc++.h>

#include "Object.h"
#include <Box2D/Box2D.h>

class RectangleObject : public Object {
  public:
    RectangleObject(b2BodyType type, float width = 0, float height = 0);
    ~RectangleObject();

    float getHeight() const;
    float getWidth() const;

    void setHeight(float value);
    void setWidth(float value);
    void setTexture(std::string filename);

    b2Fixture *build(b2World *world, const sf::Vector2i &tileSize) override;
    void draw(sf::RenderWindow &window) override;


private:
    float width, height;
    b2PolygonShape *polygonShape;
    sf::Texture *texture = nullptr;

};

#endif // RECTANGLEOBJECT_H
