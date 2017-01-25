#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include <bits/stdc++.h>

#include "Object.h"

#include "Box2D/Box2D.h"

class CircleObject : public Object
{
public:
    CircleObject(b2BodyType type, float radius);
    ~CircleObject();

    b2Fixture *build(b2World *world, const sf::Vector2i &tileSize) override;
    void draw(sf::RenderWindow &window) override;

    float getRadius() const;
    void setRadius(float value);

    void setTexture(std::__cxx11::string filename);

private:
    float radius;
    b2CircleShape *circleShape;
    sf::Texture *texture = nullptr;

};

#endif // CIRCLEOBJECT_H
