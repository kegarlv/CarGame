#ifndef POLYGONOBJECT_H
#define POLYGONOBJECT_H

#include <bits/stdc++.h>

#include "Object.h"

class PolygonObject : public Object
{
public:
    PolygonObject();
    ~PolygonObject();
    void setPoints(std::string pts);

    b2Fixture *build(b2World *world, const sf::Vector2i &tileSize) override;
    void draw(sf::RenderWindow &window) override;

private:
    std::vector<std::pair<float,float> > points;
    b2PolygonShape *polygonShape;

};

#endif // POLYGONOBJECT_H
