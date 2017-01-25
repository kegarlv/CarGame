#include "circleobject.h"

CircleObject::CircleObject(b2BodyType type, float radius = 0) {
    this->setShapeType(CIRCLE);
    this->bodyType = type;
    this->fixtureDef = new b2FixtureDef;
    this->circleShape = new b2CircleShape;
    this->radius = radius;

    bodyDef.type = bodyType;

    circleShape->m_radius = radius;

    fixtureDef->shape = circleShape;
    fixtureDef->density = 1.0f;
    fixtureDef->friction = 1.0f;
}

CircleObject::~CircleObject() {
    delete fixtureDef;
    delete circleShape;
    delete texture;
}

b2Fixture *CircleObject::build(b2World *world, const sf::Vector2i &tileSize) {

    bodyDef.position.Set(rect.left + tileSize.x / 2 * (rect.width / tileSize.x - 1),
                         rect.top + tileSize.y / 2 * (rect.height / tileSize.y - 1));
    body = world->CreateBody(&bodyDef);
    body->CreateFixture(fixtureDef);

    return body->GetFixtureList();
}

void CircleObject::draw(sf::RenderWindow &window) {
    if (texture != nullptr) {
        sf::Sprite sprite;
        sprite.setTexture(*texture);
        sprite.setScale(1 / 16.0, 1 / 16.0);
        sprite.setPosition(this->body->GetPosition().x - 2, this->body->GetPosition().y - 2);
        sf::Transform t;
        window.draw(sprite, t);
    } else {
        sf::CircleShape circle;
        circle.setRadius(this->radius);
        //BUG magic?????
        circle.setPosition(this->body->GetPosition().x - 2, this->body->GetPosition().y - 2);
        circle.setFillColor(sf::Color(0, 255, 0));

        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(this->radius,1));
        rect.setFillColor(sf::Color(0,0,255));
        rect.setPosition(this->body->GetPosition().x - 2 + this->radius, this->body->GetPosition().y - 2 + this->radius);
        rect.setRotation(this->body->GetAngle()*180/3.14);
        window.draw(circle);
        window.draw(rect);
    }
}

float CircleObject::getRadius() const {
    return radius;
}

void CircleObject::setRadius(float value) {
    radius = value;
}

void CircleObject::setTexture(std::string filename) {
    texture = new sf::Texture;
    texture->loadFromFile(filename);
}
