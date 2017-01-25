#include "Object.h"

Object::Object() {}

Object::~Object() {}

void Object::setShapeType(const ShapeType &value) { shapeType = value; }

void Object::setProperty(std::string name, std::string property) { prop[name] = property; }

std::string Object::getType() const { return type; }

void Object::setType(const std::string &value) { type = value; }

void Object::setObjectRect(const sf::Rect<int> &rect) { this->rect = rect; }

void Object::draw(sf::RenderWindow &window) {
    throw Exception("Calling draw on virtual Object");
}

sf::Sprite Object::getSprite() const {
    return sprite;
}

void Object::setSprite(const sf::Sprite &value) {
    sprite = value;
    isSprite = true;
}

b2Vec2 Object::getPosition() const {
    return position;
}

void Object::setPosition(const b2Vec2 &value) {
    position = value;
}

b2FixtureDef *Object::getFixtureDef() {
    return fixtureDef;
}

b2BodyType Object::getBodyType() const {
    return bodyType;
}

b2BodyDef Object::getBodyDef() {
    return bodyDef;
}

b2Body *Object::getBody() const {
    return body;
}

sf::Rect<int> Object::getRect() const { return rect; }

std::string Object::getName() const { return name; }

void Object::setName(const std::string &value) { name = value; }

int Object::getPropertyInt(std::string name) { return atoi(prop[name].c_str()); }

float Object::getPropertyFloat(std::string name) { return strtod(prop[name].c_str(), NULL); }

std::string Object::getPropertyString(std::string name) { return prop[name]; }

Object::ShapeType Object::getShapeType() const { return shapeType; }
