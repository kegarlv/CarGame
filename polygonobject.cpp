#include "polygonobject.h"

PolygonObject::PolygonObject() {
    this->setShapeType(Object::POLYGON);
    this->fixtureDef = new b2FixtureDef;
    fixtureDef->density = 1.0f;
    fixtureDef->friction = 0.8f;

}

PolygonObject::~PolygonObject() {
    delete polygonShape;
}

void PolygonObject::setPoints(std::string pts) {
    std::stringstream ss(pts);
    float x, y;
    char tmp;
    while (ss >> x >> tmp >> y)
        points.push_back({x, y});
}

b2Fixture *PolygonObject::build(b2World *world, const sf::Vector2i &tileSize) {

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(rect.left - tileSize.x / 2,
                         rect.top - tileSize.y / 2);
    body = world->CreateBody(&bodyDef);

    b2Vec2 vertices[points.size()];
    for (int i = 0; i < points.size(); i++)
        vertices[i].Set(points[i].first, points[i].second);

    polygonShape = new b2PolygonShape;
    polygonShape->Set(vertices, points.size());
    fixtureDef->shape = polygonShape;

    body->CreateFixture(fixtureDef);

    return body->GetFixtureList();
}

void PolygonObject::draw(sf::RenderWindow &window) {
    sf::ConvexShape debugShape;

    debugShape.setPointCount(points.size());

    for (int i = 0; i < points.size(); i++) {
        debugShape.setPoint(i, sf::Vector2f(points[i].first, points[i].second));
    }

    debugShape.setOutlineThickness(1);
    debugShape.setOutlineColor(sf::Color(255, 0, 0));
    debugShape.setFillColor(sf::Color(0, 0, 0, 0));
    debugShape.setPosition(this->rect.left, this->rect.top);

    window.draw(debugShape);
}
