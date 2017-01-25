#include "rectangleobject.h"

RectangleObject::RectangleObject(b2BodyType type, float width, float height) {
    this->setShapeType(Object::RECTANGLE);
    this->bodyType = type;
    this->fixtureDef = new b2FixtureDef;
    this->polygonShape = new b2PolygonShape;
    this->width = width;
    this->height = height;

    this->fixtureDef->density = 1.0f;
    this->fixtureDef->friction = 1.0f;
    this->fixtureDef->shape = polygonShape;

    bodyDef.type = type;
}

RectangleObject::~RectangleObject() {
    if (texture != nullptr)
        delete texture;
}

void RectangleObject::setWidth(float value) { width = value; }

b2Fixture *RectangleObject::build(b2World *world, const sf::Vector2i &tileSize) {
    bodyDef.position.Set(rect.left + tileSize.x / 2 * (rect.width / tileSize.x - 1),
                         rect.top + tileSize.y / 2 * (rect.height / tileSize.y - 1));
    body = world->CreateBody(&bodyDef);

    polygonShape->SetAsBox(rect.width / 2, rect.height / 2);
    body->CreateFixture(fixtureDef);

    return body->GetFixtureList();
}

void RectangleObject::draw(sf::RenderWindow &window) {

    if (texture != nullptr) {
        sf::Sprite sprite;
        sprite.setTexture(*texture);
        sprite.setScale(1 / 16.0, 1 / 16.0);
        sprite.setPosition(this->rect.left, this->rect.top);
        window.draw(sprite);
    } else {
        sf::RectangleShape debugRect;
        debugRect.setOutlineThickness(1);
        debugRect.setOutlineColor(sf::Color(255, 0, 0));
        debugRect.setFillColor(sf::Color(0, 0, 0, 0));
        debugRect.setSize(sf::Vector2f(this->rect.width, this->rect.height));
        //    debugRect.setPosition(this->rect.left, this->rect.top);
        debugRect.setPosition(body->GetPosition().x - this->width / 2.0 + 8,
                              body->GetPosition().y - this->height / 2.0 + 8);

        sf::Transform transform;
        sf::Vector2f center = debugRect.getPosition();
        center.x += this->width/2;
        center.y += this->height/2;

        transform.rotate(this->body->GetAngle()*180/3.14, center);
        window.draw(debugRect,transform);
    }
}

void RectangleObject::setTexture(std::string filename) {
    texture = new sf::Texture;
    texture->loadFromFile(filename);
}

float RectangleObject::getWidth() const {
    return width;
}

float RectangleObject::getHeight() const {
    return height;
}

void RectangleObject::setHeight(float value) {
    height = value;
}
